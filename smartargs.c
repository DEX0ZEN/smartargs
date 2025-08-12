#include "smartargs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

/* Global variables for positional arguments */
char **args = NULL;
int arg_count = 0;

/* Internal helper functions */
static Option* find_long_option(Option *options, int count, const char *name) {
    for (int i = 0; i < count; i++) {
        if (options[i].long_name && strcmp(options[i].long_name, name) == 0) {
            return &options[i];
        }
    }
    return NULL;
}

static Option* find_short_option(Option *options, int count, char name) {
    for (int i = 0; i < count; i++) {
        if (options[i].short_name == name) {
            return &options[i];
        }
    }
    return NULL;
}

static int set_value(Option *opt, const char *value, ParseResult *result) {
    switch (opt->type) {
        case OPT_FLAG:
            *(int*)opt->value = 1;
            return 0;
            
        case OPT_INT: {
            if (!value) {
                result->error = "Integer option requires a value";
                return -1;
            }
            char *end;
            errno = 0;
            long val = strtol(value, &end, 10);
            if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
                result->error = "Integer value out of range";
                return -1;
            }
            if (*end != '\0') {
                result->error = "Invalid integer value";
                return -1;
            }
            *(int*)opt->value = (int)val;
            return 0;
        }
        
        case OPT_DOUBLE: {
            if (!value) {
                result->error = "Double option requires a value";
                return -1;
            }
            char *end;
            errno = 0;
            double val = strtod(value, &end);
            if (errno == ERANGE) {
                result->error = "Double value out of range";
                return -1;
            }
            if (*end != '\0') {
                result->error = "Invalid double value";
                return -1;
            }
            *(double*)opt->value = val;
            return 0;
        }
        
        case OPT_STRING:
            if (!value) {
                result->error = "String option requires a value";
                return -1;
            }
            *(const char**)opt->value = value;
            return 0;
            
        default:
            result->error = "Unknown option type";
            return -1;
    }
}

static int add_positional(ParseResult *result, const char *arg) {
    char **new_args = realloc(result->args, sizeof(char*) * (result->arg_count + 1));
    if (!new_args) {
        result->error = "Memory allocation failed";
        return -1;
    }
    result->args = new_args;
    result->args[result->arg_count] = (char*)arg;
    result->arg_count++;
    return 0;
}

int cli_parse(int argc, char *argv[], Option *options, int option_count, ParseResult *result) {
    if (!argv || !options || !result || argc < 0 || option_count < 0) {
        if (result) result->error = "Invalid arguments";
        return -1;
    }
    
    /* Initialize result */
    memset(result, 0, sizeof(ParseResult));
    
    for (int i = 1; i < argc; i++) {
        char *arg = argv[i];
        
        if (!arg) {
            result->error = "NULL argument encountered";
            return -1;
        }
        
        /* Handle -- (end of options) */
        if (strcmp(arg, "--") == 0) {
            for (int j = i + 1; j < argc; j++) {
                if (add_positional(result, argv[j]) != 0) {
                    return -1;
                }
            }
            break;
        }
        
        /* Long option --name or --name=value */
        if (arg[0] == '-' && arg[1] == '-' && arg[2] != '\0') {
            char *name = arg + 2;
            char *value = strchr(name, '=');
            
            if (value) {
                *value = '\0';  /* Split at = */
                value++;
            }
            
            Option *opt = find_long_option(options, option_count, name);
            if (!opt) {
                result->error = "Unknown option";
                return -1;
            }
            
            if (opt->type == OPT_FLAG) {
                if (value) {
                    result->error = "Flag option does not accept a value";
                    return -1;
                }
                *(int*)opt->value = 1;
            } else {
                if (!value) {
                    if (i + 1 >= argc) {
                        result->error = "Option requires a value";
                        return -1;
                    }
                    value = argv[++i];
                }
                if (set_value(opt, value, result) != 0) {
                    return -1;
                }
            }
        }
        /* Short option -x */
        else if (arg[0] == '-' && arg[1] != '\0' && arg[1] != '-') {
            char name = arg[1];
            
            Option *opt = find_short_option(options, option_count, name);
            if (!opt) {
                result->error = "Unknown option";
                return -1;
            }
            
            if (opt->type == OPT_FLAG) {
                *(int*)opt->value = 1;
            } else {
                if (i + 1 >= argc) {
                    result->error = "Option requires a value";
                    return -1;
                }
                if (set_value(opt, argv[++i], result) != 0) {
                    return -1;
                }
            }
        }
        /* Positional argument */
        else {
            if (add_positional(result, arg) != 0) {
                return -1;
            }
        }
    }
    
    /* Check required options (but skip if help was requested) */
    int help_requested = 0;
    for (int i = 0; i < option_count; i++) {
        if (options[i].type == OPT_FLAG && 
            ((options[i].long_name && strcmp(options[i].long_name, "help") == 0) ||
             options[i].short_name == 'h')) {
            if (*(int*)options[i].value != 0) {
                help_requested = 1;
                break;
            }
        }
    }
    
    if (!help_requested) {
        for (int i = 0; i < option_count; i++) {
            if (options[i].required) {
                int is_set = 0;
                
                switch (options[i].type) {
                    case OPT_FLAG:
                        is_set = *(int*)options[i].value != 0;
                        break;
                    case OPT_STRING:
                        is_set = *(const char**)options[i].value != NULL;
                        break;
                    case OPT_INT:
                    case OPT_DOUBLE:
                        /* Assume numeric options are set if we got here */
                        is_set = 1;
                        break;
                }
                
                if (!is_set) {
                    result->error = "Required option missing";
                    return -1;
                }
            }
        }
    }
    
    return 0;
}

void cli_usage(const char *program_name, Option *options, int option_count, const char *description) {
    printf("Usage: %s [options] [arguments]\n", program_name ? program_name : "program");
    
    if (description) {
        printf("\n%s\n", description);
    }
    
    if (option_count > 0) {
        printf("\nOptions:\n");
        
        for (int i = 0; i < option_count; i++) {
            printf("  ");
            
            /* Short option */
            if (options[i].short_name) {
                printf("-%c", options[i].short_name);
                if (options[i].long_name) {
                    printf(", ");
                }
            } else {
                printf("    ");
            }
            
            /* Long option */
            if (options[i].long_name) {
                printf("--%s", options[i].long_name);
                
                /* Add type hint for non-flags */
                switch (options[i].type) {
                    case OPT_INT:
                        printf(" <num>");
                        break;
                    case OPT_DOUBLE:
                        printf(" <float>");
                        break;
                    case OPT_STRING:
                        printf(" <string>");
                        break;
                    case OPT_FLAG:
                        break;
                }
            }
            
            /* Required marker */
            if (options[i].required) {
                printf(" (required)");
            }
            
            /* Help text */
            if (options[i].help) {
                printf("\n      %s", options[i].help);
            }
            
            printf("\n");
        }
    }
}

void cli_free(ParseResult *result) {
    if (result && result->args) {
        free(result->args);
        result->args = NULL;
        result->arg_count = 0;
    }
}
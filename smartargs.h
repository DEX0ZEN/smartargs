#ifndef SMARTARGS_H
#define SMARTARGS_H

/*
 * SmartArgs - Ultra-Smart Command-Line Argument Parser for C
 * The easiest CLI parser in the world - just declare what you need!
 * 
 * Usage: Just use CONFIGURE() macro with your options
 * 
 * Version: 3.0.0 - SmartArgs Edition
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* Option types for internal use */
typedef enum {
    OPT_FLAG,    /* Boolean flag */
    OPT_INT,     /* Integer value */
    OPT_STRING,  /* String value */
    OPT_DOUBLE   /* Double value */
} OptionType;

/* Internal option definition */
typedef struct {
    const char *long_name;
    char short_name;
    OptionType type;
    void *value;
    const char *help;
    int required;
} Option;

/* Parse result for internal use */
typedef struct {
    char **args;
    int arg_count;
    const char *error;
} ParseResult;

/* Internal functions - users don't need to call these directly */
int cli_parse(int argc, char *argv[], Option *options, int option_count, ParseResult *result);
void cli_usage(const char *program_name, Option *options, int option_count, const char *description);
void cli_free(ParseResult *result);

/*
 * SMARTARGS API - Just declare what you need!
 * 
 * Use CONFIGURE() to automatically parse all command line arguments.
 * Your variables are automatically updated with parsed values.
 */

/* Smart option definition macros */
#define FLAG(var, short_opt, long_opt, help_text) \
    {long_opt, short_opt, OPT_FLAG, &var, help_text, 0}

#define FLAG_REQUIRED(var, short_opt, long_opt, help_text) \
    {long_opt, short_opt, OPT_FLAG, &var, help_text, 1}

#define INT(var, short_opt, long_opt, help_text) \
    {long_opt, short_opt, OPT_INT, &var, help_text, 0}

#define INT_REQUIRED(var, short_opt, long_opt, help_text) \
    {long_opt, short_opt, OPT_INT, &var, help_text, 1}

#define STRING(var, short_opt, long_opt, help_text) \
    {long_opt, short_opt, OPT_STRING, &var, help_text, 0}

#define STRING_REQUIRED(var, short_opt, long_opt, help_text) \
    {long_opt, short_opt, OPT_STRING, &var, help_text, 1}

#define DOUBLE(var, short_opt, long_opt, help_text) \
    {long_opt, short_opt, OPT_DOUBLE, &var, help_text, 0}

#define DOUBLE_REQUIRED(var, short_opt, long_opt, help_text) \
    {long_opt, short_opt, OPT_DOUBLE, &var, help_text, 1}

/* The magic macro that does everything automatically */
#define ARGS(argc, argv, description, ...) \
    do { \
        Option _smartargs_options[] = { __VA_ARGS__ }; \
        int _smartargs_option_count = sizeof(_smartargs_options) / sizeof(_smartargs_options[0]); \
        ParseResult _smartargs_result; \
        \
        if (cli_parse(argc, argv, _smartargs_options, _smartargs_option_count, &_smartargs_result) != 0) { \
            fprintf(stderr, "Error: %s\n", _smartargs_result.error); \
            cli_usage(argv[0], _smartargs_options, _smartargs_option_count, description); \
            cli_free(&_smartargs_result); \
            exit(1); \
        } \
        \
        /* Store positional arguments in global variables */ \
        args = _smartargs_result.args; \
        arg_count = _smartargs_result.arg_count; \
        \
        /* Don't free here - user can access args */ \
    } while(0)

/* Global variables for accessing positional arguments */
extern char **args;
extern int arg_count;

/* Smart help macro - automatically shows help if --help is used */
#define HELP(help_var) \
    FLAG(help_var, 'h', "help", "Show this help message")

/* Complete parsing with automatic help handling - The main SmartArgs macro */
#define CONFIGURE(argc, argv, description, help_var, ...) \
    do { \
        Option _smartargs_options[] = { \
            HELP(help_var), \
            __VA_ARGS__ \
        }; \
        int _smartargs_option_count = sizeof(_smartargs_options) / sizeof(_smartargs_options[0]); \
        ParseResult _smartargs_result; \
        \
        if (cli_parse(argc, argv, _smartargs_options, _smartargs_option_count, &_smartargs_result) != 0) { \
            fprintf(stderr, "Error: %s\n", _smartargs_result.error); \
            cli_usage(argv[0], _smartargs_options, _smartargs_option_count, description); \
            cli_free(&_smartargs_result); \
            exit(1); \
        } \
        \
        if (help_var) { \
            cli_usage(argv[0], _smartargs_options, _smartargs_option_count, description); \
            cli_free(&_smartargs_result); \
            exit(0); \
        } \
        \
        args = _smartargs_result.args; \
        arg_count = _smartargs_result.arg_count; \
    } while(0)

/* Cleanup macro */
#define CLEANUP() \
    do { \
        if (args) { \
            ParseResult _temp = {args, arg_count, NULL}; \
            cli_free(&_temp); \
            args = NULL; \
            arg_count = 0; \
        } \
    } while(0)

#ifdef __cplusplus
}
#endif

#endif /* SMARTARGS_H */
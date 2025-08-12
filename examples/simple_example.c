/*
 * SmartArgs Simple Example
 * Shows how easy the new API is to use!
 */

#include <stdio.h>
#include "smartargs.h"

int main(int argc, char *argv[]) {
    // 1. Declare your variables
    int verbose = 0;
    int help = 0;
    int threads = 4;
    const char *input_file = NULL;
    const char *output_dir = NULL;
    
    // 2. Configure everything automatically with one macro!
    CONFIGURE(argc, argv, "Simple file processor with SmartArgs", help,
        FLAG(verbose, 'v', "verbose", "Enable verbose output"),
        INT(threads, 't', "threads", "Number of processing threads"),
        STRING_REQUIRED(input_file, 'i', "input", "Input file path"),
        STRING(output_dir, 'o', "output", "Output directory")
    );
    
    // 3. Use your variables - they're automatically filled!
    printf("SmartArgs Simple Example\n");
    printf("========================\n");
    printf("  Input file: %s\n", input_file);
    printf("  Output dir: %s\n", output_dir ? output_dir : "current directory");
    printf("  Threads: %d\n", threads);
    printf("  Verbose: %s\n", verbose ? "enabled" : "disabled");
    
    // 4. Process any extra files
    if (arg_count > 0) {
        printf("  Extra files:\n");
        for (int i = 0; i < arg_count; i++) {
            printf("    - %s\n", args[i]);
        }
    }
    
    printf("\nConfiguration complete! Ready to process files.\n");
    
    // 5. Clean up (optional but recommended)
    CLEANUP();
    
    return 0;
}

/*
 * Usage examples:
 * ./simple_example --help
 * ./simple_example --input data.txt
 * ./simple_example -v --input data.txt --threads 8 --output results/
 * ./simple_example --input data.txt file1.txt file2.txt file3.txt
 */
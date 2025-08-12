/*
 * SmartArgs Basic Functionality Test
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "smartargs.h"

// Test helper to simulate command line arguments
static char* test_argv[] = {
    "test_program",
    "--verbose",
    "--threads", "8",
    "--input", "test.txt",
    "extra1",
    "extra2"
};
static int test_argc = sizeof(test_argv) / sizeof(test_argv[0]);

int main() {
    printf("Running SmartArgs Basic Test...\n");
    
    // Test variables
    int verbose = 0;
    int help = 0;
    int threads = 4;
    const char *input = NULL;
    
    // Use ARGS macro for testing (no help handling)
    ARGS(test_argc, test_argv, "Test program",
        FLAG(verbose, 'v', "verbose", "Enable verbose"),
        INT(threads, 't', "threads", "Number of threads"),
        STRING(input, 'i', "input", "Input file")
    );
    
    // Verify parsing worked correctly
    assert(verbose == 1);
    assert(threads == 8);
    assert(input != NULL);
    assert(strcmp(input, "test.txt") == 0);
    assert(arg_count == 2);
    assert(strcmp(args[0], "extra1") == 0);
    assert(strcmp(args[1], "extra2") == 0);
    
    printf("✅ All basic tests passed!\n");
    printf("  Verbose: %d\n", verbose);
    printf("  Threads: %d\n", threads);
    printf("  Input: %s\n", input);
    printf("  Extra args: %d\n", arg_count);
    
    CLEANUP();
    return 0;
}
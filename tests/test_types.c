/*
 * SmartArgs Data Types Test
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "smartargs.h"

// Test all data types
static char* test_argv[] = {
    "test_program",
    "--flag",
    "--number", "42",
    "--ratio", "3.14159",
    "--name", "SmartArgs"
};
static int test_argc = sizeof(test_argv) / sizeof(test_argv[0]);

int main() {
    printf("Running SmartArgs Data Types Test...\n");
    
    // Test variables for all supported types
    int flag = 0;
    int help = 0;
    int number = 0;
    double ratio = 0.0;
    const char *name = NULL;
    
    // Test all data types
    ARGS(test_argc, test_argv, "Data types test",
        FLAG(flag, 'f', "flag", "Boolean flag"),
        INT(number, 'n', "number", "Integer number"),
        DOUBLE(ratio, 'r', "ratio", "Floating point ratio"),
        STRING(name, 's', "name", "String name")
    );
    
    // Verify all types parsed correctly
    assert(flag == 1);
    assert(number == 42);
    assert(fabs(ratio - 3.14159) < 0.00001);
    assert(name != NULL);
    assert(strcmp(name, "SmartArgs") == 0);
    
    printf("✅ All data type tests passed!\n");
    printf("  Flag: %d\n", flag);
    printf("  Number: %d\n", number);
    printf("  Ratio: %.5f\n", ratio);
    printf("  Name: %s\n", name);
    
    CLEANUP();
    return 0;
}
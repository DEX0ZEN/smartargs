/*
 * SmartArgs Error Handling Test
 * Note: This test validates error conditions by checking that
 * parsing fails as expected for invalid inputs.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "smartargs.h"

// Test error cases by directly calling the internal API
int test_invalid_integer() {
    char* argv[] = {"test", "--number", "abc"};
    int argc = 3;
    
    int number = 0;
    int help = 0;
    
    Option options[] = {
        {"help", 'h', OPT_FLAG, &help, "Help", 0},
        {"number", 'n', OPT_INT, &number, "Number", 0}
    };
    
    ParseResult result;
    int ret = cli_parse(argc, argv, options, 2, &result);
    
    if (ret != 0) {
        printf("✅ Invalid integer correctly rejected: %s\n", result.error);
        cli_free(&result);
        return 1; // Success - error was caught
    }
    
    cli_free(&result);
    return 0; // Failure - should have been an error
}

int test_invalid_double() {
    char* argv[] = {"test", "--ratio", "not_a_number"};
    int argc = 3;
    
    double ratio = 0.0;
    int help = 0;
    
    Option options[] = {
        {"help", 'h', OPT_FLAG, &help, "Help", 0},
        {"ratio", 'r', OPT_DOUBLE, &ratio, "Ratio", 0}
    };
    
    ParseResult result;
    int ret = cli_parse(argc, argv, options, 2, &result);
    
    if (ret != 0) {
        printf("✅ Invalid double correctly rejected: %s\n", result.error);
        cli_free(&result);
        return 1; // Success - error was caught
    }
    
    cli_free(&result);
    return 0; // Failure - should have been an error
}

int test_unknown_option() {
    char* argv[] = {"test", "--unknown-option"};
    int argc = 2;
    
    int help = 0;
    
    Option options[] = {
        {"help", 'h', OPT_FLAG, &help, "Help", 0}
    };
    
    ParseResult result;
    int ret = cli_parse(argc, argv, options, 1, &result);
    
    if (ret != 0) {
        printf("✅ Unknown option correctly rejected: %s\n", result.error);
        cli_free(&result);
        return 1; // Success - error was caught
    }
    
    cli_free(&result);
    return 0; // Failure - should have been an error
}

int main() {
    printf("Running SmartArgs Error Handling Tests...\n");
    
    int passed = 0;
    int total = 3;
    
    printf("\nTest 1: Invalid integer input\n");
    if (test_invalid_integer()) passed++;
    
    printf("\nTest 2: Invalid double input\n");
    if (test_invalid_double()) passed++;
    
    printf("\nTest 3: Unknown option\n");
    if (test_unknown_option()) passed++;
    
    printf("\n");
    if (passed == total) {
        printf("✅ All %d error handling tests passed!\n", total);
        return 0;
    } else {
        printf("❌ %d/%d error handling tests failed!\n", total - passed, total);
        return 1;
    }
}
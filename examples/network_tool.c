/*
 * SmartArgs Network Tool Example
 * Real-world example of a network utility
 */

#include <stdio.h>
#include "smartargs.h"

int main(int argc, char *argv[]) {
    // Network tool configuration
    int help = 0;
    int verbose = 0;
    int follow_redirects = 0;
    int insecure = 0;
    int max_time = 30;
    int connect_timeout = 10;
    int retries = 3;
    double retry_delay = 1.0;
    const char *method = "GET";
    const char *user_agent = "SmartArgs-NetworkTool/1.0";
    const char *output_file = NULL;
    const char *header = NULL;
    const char *data = NULL;
    
    CONFIGURE(argc, argv, "SmartArgs Network Tool - HTTP client with smart configuration", help,
        FLAG(verbose, 'v', "verbose", "Enable verbose output"),
        FLAG(follow_redirects, 'L', "location", "Follow redirects"),
        FLAG(insecure, 'k', "insecure", "Allow insecure SSL connections"),
        INT(max_time, 'm', "max-time", "Maximum time for the transfer"),
        INT(connect_timeout, 'c', "connect-timeout", "Maximum time for connection"),
        INT(retries, 'r', "retry", "Number of retry attempts"),
        DOUBLE(retry_delay, 'd', "retry-delay", "Delay between retries in seconds"),
        STRING(method, 'X', "request", "HTTP request method"),
        STRING(user_agent, 'A', "user-agent", "User agent string"),
        STRING(output_file, 'o', "output", "Write output to file"),
        STRING(header, 'H', "header", "Add custom header"),
        STRING(data, 'D', "data", "HTTP POST data")
    );
    
    printf("SmartArgs Network Tool\n");
    printf("======================\n");
    
    // Validate configuration
    if (arg_count == 0) {
        printf("Error: No URLs specified\n");
        printf("Usage: %s [options] <url1> [url2] ...\n", argv[0]);
        CLEANUP();
        return 1;
    }
    
    // Display configuration
    printf("Configuration:\n");
    printf("  Method: %s\n", method);
    printf("  User Agent: %s\n", user_agent);
    printf("  Max Time: %d seconds\n", max_time);
    printf("  Connect Timeout: %d seconds\n", connect_timeout);
    printf("  Retries: %d\n", retries);
    printf("  Retry Delay: %.1f seconds\n", retry_delay);
    printf("  Follow Redirects: %s\n", follow_redirects ? "yes" : "no");
    printf("  Insecure SSL: %s\n", insecure ? "yes" : "no");
    printf("  Verbose: %s\n", verbose ? "yes" : "no");
    
    if (output_file) {
        printf("  Output File: %s\n", output_file);
    }
    
    if (header) {
        printf("  Custom Header: %s\n", header);
    }
    
    if (data) {
        printf("  POST Data: %s\n", data);
    }
    
    printf("\n");
    
    // Process URLs
    printf("Processing URLs:\n");
    for (int i = 0; i < arg_count; i++) {
        printf("  %d. %s\n", i + 1, args[i]);
        
        if (verbose) {
            printf("     -> Connecting with %d second timeout...\n", connect_timeout);
            printf("     -> Using method: %s\n", method);
            printf("     -> Max transfer time: %d seconds\n", max_time);
        }
        
        // Simulate network operation
        printf("     -> [SIMULATED] Request completed successfully\n");
    }
    
    printf("\nAll requests completed!\n");
    
    if (verbose) {
        printf("\nVerbose Summary:\n");
        printf("  Total URLs processed: %d\n", arg_count);
        printf("  Configuration options used: %d\n", argc - arg_count - 1);
        printf("  SmartArgs made configuration effortless!\n");
    }
    
    CLEANUP();
    return 0;
}

/*
 * Usage examples:
 * ./network_tool --help
 * ./network_tool https://httpbin.org/get
 * ./network_tool -v --method POST --data "hello=world" https://httpbin.org/post
 * ./network_tool -L --max-time 60 --retry 5 https://example.com https://google.com
 * ./network_tool -k --insecure --header "Authorization: Bearer token" https://api.example.com/data
 */
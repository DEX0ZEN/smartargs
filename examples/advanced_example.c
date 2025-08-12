/*
 * SmartArgs Advanced Example
 * Shows all data types and advanced features
 */

#include <stdio.h>
#include "smartargs.h"

int main(int argc, char *argv[]) {
    // Configuration variables with defaults
    int verbose = 0;
    int help = 0;
    int threads = 4;
    int port = 8080;
    int timeout = 30;
    int ssl = 0;
    double threshold = 0.5;
    double retry_backoff = 1.5;
    const char *host = "localhost";
    const char *method = "GET";
    const char *config_file = NULL;
    const char *log_level = "info";
    
    // SmartArgs magic - one macro handles everything!
    CONFIGURE(argc, argv, "Advanced SmartArgs demonstration with all features", help,
        FLAG(verbose, 'v', "verbose", "Enable verbose logging"),
        FLAG(ssl, 's', "ssl", "Use SSL/TLS encryption"),
        INT(threads, 't', "threads", "Number of processing threads"),
        INT(port, 'p', "port", "Server port number"),
        INT(timeout, 'T', "timeout", "Connection timeout in seconds"),
        DOUBLE(threshold, 'r', "threshold", "Processing threshold (0.0-1.0)"),
        DOUBLE(retry_backoff, 'b', "backoff", "Retry backoff multiplier"),
        STRING(host, 'H', "host", "Server hostname or IP address"),
        STRING(method, 'm', "method", "HTTP method (GET, POST, PUT, DELETE)"),
        STRING(log_level, 'l', "log-level", "Log level (debug, info, warn, error)"),
        STRING_REQUIRED(config_file, 'c', "config", "Configuration file path")
    );
    
    // All variables are automatically populated!
    printf("🚀 SmartArgs Advanced Configuration\n");
    printf("=====================================\n");
    printf("  Network Settings:\n");
    printf("    Host: %s:%d\n", host, port);
    printf("    Method: %s\n", method);
    printf("    SSL: %s\n", ssl ? "enabled" : "disabled");
    printf("    Timeout: %d seconds\n", timeout);
    printf("  \n");
    printf("  Processing Settings:\n");
    printf("    Threads: %d\n", threads);
    printf("    Threshold: %.2f\n", threshold);
    printf("    Retry backoff: %.1fx\n", retry_backoff);
    printf("  \n");
    printf("  System Settings:\n");
    printf("    Config file: %s\n", config_file);
    printf("    Log level: %s\n", log_level);
    printf("    Verbose: %s\n", verbose ? "enabled" : "disabled");
    
    // Validate configuration
    if (threshold < 0.0 || threshold > 1.0) {
        printf("  ⚠️  Warning: Threshold should be between 0.0 and 1.0\n");
    }
    
    if (port < 1 || port > 65535) {
        printf("  ⚠️  Warning: Port should be between 1 and 65535\n");
    }
    
    // Process additional URLs/files
    if (arg_count > 0) {
        printf("  \n");
        printf("  Additional Resources:\n");
        for (int i = 0; i < arg_count; i++) {
            printf("    %d. %s\n", i + 1, args[i]);
        }
    }
    
    // Simulate some work based on configuration
    if (verbose) {
        printf("  \n");
        printf("📊 Verbose Mode - Detailed Information:\n");
        printf("    Total arguments processed: %d\n", argc - 1);
        printf("    Protocol: HTTP%s\n", ssl ? "S" : "");
        printf("    Full endpoint: %s://%s:%d\n", ssl ? "https" : "http", host, port);
        printf("    Expected response time: %d seconds\n", timeout);
    }
    
    printf("  \n");
    printf("✅ Configuration complete! SmartArgs made it effortless.\n");
    
    // Clean up
    CLEANUP();
    
    return 0;
}

/*
 * Usage examples:
 * ./advanced_example --help
 * ./advanced_example --config app.conf
 * ./advanced_example --config app.conf --host api.example.com --port 443 --ssl
 * ./advanced_example -c app.conf -H localhost -p 8080 -v --method POST --threads 8
 * ./advanced_example --config app.conf --threshold 0.8 --backoff 2.0 url1 url2 url3
 */
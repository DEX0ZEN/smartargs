# SmartArgs - Ultra-Smart Command-Line Argument Parser for C

**The easiest CLI parser in the world!** Just declare what you need - SmartArgs handles everything automatically. No boilerplate, no complex setup, no manual error handling.

## What Makes SmartArgs Ultra-Smart?

-  **Zero Boilerplate** - One macro does everything
-  **Instant Setup** - Just declare variables and options  
-  **Automatic Error Handling** - Built-in validation and messages
-  **Smart Help** - Automatic --help generation
-  **Memory Safe** - Automatic cleanup with no leaks
-  **Lightweight** - Under 400 lines, no dependencies
-  **Professional** - Production-ready with comprehensive features

## 🚀 Ultra-Simple Usage

### 1. Build SmartArgs
```bash
git clone https://github.com/LazySeldi/smartargs.git
cd smartargs
mkdir build && cd build && cmake .. && make
```
To install it just do:
```bash
sudo make install
```

### 2. Write Your App (Just 3 Lines!)

Create `myapp.c`:
```c
#include <stdio.h>
#include "smartargs.h"

int main(int argc, char *argv[]) {
    // 1. Declare your variables
    int verbose = 0, help = 0, threads = 4;
    const char *input_file = NULL, *output_dir = NULL;
    
    // 2. Configure everything automatically!
    CONFIGURE(argc, argv, "My awesome file processor", help,
        FLAG(verbose, 'v', "verbose", "Enable verbose output"),
        INT(threads, 't', "threads", "Number of processing threads"),
        STRING_REQUIRED(input_file, 'i', "input", "Input file path"),
        STRING(output_dir, 'o', "output", "Output directory")
    );
    
    // 3. Use your variables - they're automatically filled!
    printf("Processing %s with %d threads\n", input_file, threads);
    if (verbose) printf("Verbose mode enabled\n");
    if (output_dir) printf("Output: %s\n", output_dir);
    
    // Handle extra files (automatic)
    for (int i = 0; i < arg_count; i++) {
        printf("Extra file: %s\n", args[i]);
    }
    
    CLEANUP(); // Optional cleanup
    return 0;
}
```

### 3. Compile and Run
```bash
gcc -o myapp myapp.c -L../build/lib -lsmartargs
./myapp --help
./myapp -v --input data.txt --threads 8 file1.txt file2.txt
```



No Option arrays, no ParseResult handling, no manual error checking - everything is automatic!

## Automatic Error Handling

The library handles all errors automatically:

```bash
# Missing required option
./myapp                           # Error: Required option missing: --input

# Invalid values  
./myapp --threads abc             # Error: Invalid integer value
./myapp --threshold 99.9          # Error: Invalid double value

# Unknown options
./myapp --invalid-option          # Error: Unknown option: --invalid-option
```

## CMake Projects

For using Smartargs in a CMake Project you just have to use 
```cmake
find_package(SmartArgs REQUIRED)
```
in your CMake Project.
Only works if you installed it with sudo make install.

## Error Handling

The library provides clear, specific error messages:

- **"Unknown option"** - Invalid option name
- **"Option requires a value"** - Missing value for non-flag option  
- **"Invalid integer value"** - Bad number format for integer option
- **"Invalid double value"** - Bad number format for double option
- **"Integer value out of range"** - Number too large/small for int
- **"Double value out of range"** - Number out of double range
- **"Required option missing"** - Required option not provided
- **"Memory allocation failed"** - Out of memory

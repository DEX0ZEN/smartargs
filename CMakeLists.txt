cmake_minimum_required(VERSION 3.10)
project(SmartArgs VERSION 3.0.0 LANGUAGES C)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Compiler flags
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_C_FLAGS "-Wall -Wextra")
set(CMAKE_C_FLAGS_DEBUG "-g -DDEBUG")
set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG")

# Configure organized build directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Create organized output directories
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Library source files
set(SMARTARGS_SOURCES
    smartargs.c
)

set(SMARTARGS_HEADERS
    smartargs.h
)

# Create shared library
add_library(smartargs SHARED ${SMARTARGS_SOURCES})
set_target_properties(smartargs PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 3
    PUBLIC_HEADER "${SMARTARGS_HEADERS}"
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

# Create static library
add_library(smartargs_static STATIC ${SMARTARGS_SOURCES})
set_target_properties(smartargs_static PROPERTIES
    OUTPUT_NAME smartargs
    PUBLIC_HEADER "${SMARTARGS_HEADERS}"
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

# Include directories
target_include_directories(smartargs PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_include_directories(smartargs_static PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

# Examples (optional)
option(BUILD_EXAMPLES "Build example programs" ON)
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Tests (optional)
option(BUILD_TESTS "Build test programs" ON)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Set install prefix to /usr for system installation
set(CMAKE_INSTALL_PREFIX "/usr" CACHE PATH "Install path prefix" FORCE)

# Installation
include(GNUInstallDirs)

install(TARGETS smartargs smartargs_static
    EXPORT SmartArgsTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install CMake config files
install(EXPORT SmartArgsTargets
    FILE SmartArgsTargets.cmake
    NAMESPACE SmartArgs::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SmartArgs
)

# Create config file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    SmartArgsConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/SmartArgsConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/SmartArgsConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SmartArgs
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/SmartArgsConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/SmartArgsConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SmartArgs
)

# Export targets for use in build tree
export(EXPORT SmartArgsTargets
    FILE ${CMAKE_CURRENT_BINARY_DIR}/SmartArgsTargets.cmake
    NAMESPACE SmartArgs::
)

# Add uninstall target
if(NOT TARGET uninstall)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
        IMMEDIATE @ONLY)

    add_custom_target(uninstall
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()

# Package creation
set(CPACK_PACKAGE_NAME "SmartArgs")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Ultra-Smart Command-Line Argument Parser for C")
set(CPACK_PACKAGE_VENDOR "SmartArgs Project")
set(CPACK_PACKAGE_CONTACT "contact@smartargs.dev")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

include(CPack)

# Custom targets for organized building
add_custom_target(info
    COMMAND ${CMAKE_COMMAND} -E echo "SmartArgs Library v${PROJECT_VERSION}"
    COMMAND ${CMAKE_COMMAND} -E echo "================================="
    COMMAND ${CMAKE_COMMAND} -E echo "Build directory: ${CMAKE_BINARY_DIR}"
    COMMAND ${CMAKE_COMMAND} -E echo "Libraries: ${CMAKE_BINARY_DIR}/lib/"
    COMMAND ${CMAKE_COMMAND} -E echo "Executables: ${CMAKE_BINARY_DIR}/bin/"
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "Available targets:"
    COMMAND ${CMAKE_COMMAND} -E echo "  make           - Build libraries"
    COMMAND ${CMAKE_COMMAND} -E echo "  make examples  - Build examples"
    COMMAND ${CMAKE_COMMAND} -E echo "  make tests     - Build tests"
    COMMAND ${CMAKE_COMMAND} -E echo "  make test      - Run tests"
    COMMAND ${CMAKE_COMMAND} -E echo "  make install   - Install system-wide"
    COMMAND ${CMAKE_COMMAND} -E echo "  make uninstall - Remove installed files"
    COMMAND ${CMAKE_COMMAND} -E echo "  make info      - Show this information"
)

# Display configuration
message(STATUS "SmartArgs ${PROJECT_VERSION}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C flags: ${CMAKE_C_FLAGS}")
message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Build examples: ${BUILD_EXAMPLES}")
message(STATUS "Build tests: ${BUILD_TESTS}")
message(STATUS "Organized output directories:")
message(STATUS "  Libraries: ${CMAKE_BINARY_DIR}/lib/")
message(STATUS "  Executables: ${CMAKE_BINARY_DIR}/bin/")

# Tests for SmartArgs

# Set output directory for tests
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests)

# Basic functionality test
add_executable(test_basic test_basic.c)
target_link_libraries(test_basic smartargs)
target_include_directories(test_basic PRIVATE ${CMAKE_SOURCE_DIR})
set_target_properties(test_basic PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests
)
add_test(NAME BasicTest COMMAND ${CMAKE_BINARY_DIR}/bin/tests/test_basic)

# Error handling test
add_executable(test_errors test_errors.c)
target_link_libraries(test_errors smartargs)
target_include_directories(test_errors PRIVATE ${CMAKE_SOURCE_DIR})
set_target_properties(test_errors PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests
)
add_test(NAME ErrorTest COMMAND ${CMAKE_BINARY_DIR}/bin/tests/test_errors)

# All data types test
add_executable(test_types test_types.c)
target_link_libraries(test_types smartargs)
target_include_directories(test_types PRIVATE ${CMAKE_SOURCE_DIR})
set_target_properties(test_types PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests
)
add_test(NAME TypesTest COMMAND ${CMAKE_BINARY_DIR}/bin/tests/test_types)

# Custom target to run all tests with organized output
add_custom_target(run_tests
    DEPENDS test_basic test_types test_errors
    COMMAND ${CMAKE_COMMAND} -E echo "Running SmartArgs Test Suite..."
    COMMAND ${CMAKE_COMMAND} -E echo "================================"
    COMMAND ${CMAKE_BINARY_DIR}/bin/tests/test_basic
    COMMAND ${CMAKE_BINARY_DIR}/bin/tests/test_types  
    COMMAND ${CMAKE_BINARY_DIR}/bin/tests/test_errors
    COMMAND ${CMAKE_COMMAND} -E echo "All tests completed!"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
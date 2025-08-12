# Examples for SmartArgs

# Set output directory for examples
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/examples)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin/examples)

# Simple example
add_executable(simple_example simple_example.c)
target_link_libraries(simple_example smartargs)
target_include_directories(simple_example PRIVATE ${CMAKE_SOURCE_DIR})
set_target_properties(simple_example PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/examples
)

# Advanced example  
add_executable(advanced_example advanced_example.c)
target_link_libraries(advanced_example smartargs)
target_include_directories(advanced_example PRIVATE ${CMAKE_SOURCE_DIR})
set_target_properties(advanced_example PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/examples
)

# Network tool example
add_executable(network_tool network_tool.c)
target_link_libraries(network_tool smartargs)
target_include_directories(network_tool PRIVATE ${CMAKE_SOURCE_DIR})
set_target_properties(network_tool PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/examples
)

# Custom target to run example demos
add_custom_target(demo
    DEPENDS simple_example advanced_example network_tool
    COMMAND ${CMAKE_COMMAND} -E echo "=== SmartArgs Simple Example ==="
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/simple_example --help
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "=== SmartArgs Advanced Example ==="  
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/advanced_example --help
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "=== SmartArgs Network Tool ==="
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/network_tool --help
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Install examples (optional)
install(TARGETS simple_example advanced_example network_tool
    DESTINATION ${CMAKE_INSTALL_BINDIR}/smartargs-examples
)
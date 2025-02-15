# Specify the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(MyProject VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable
add_executable(${PROJECT_NAME} main.cpp "literals.h" "types.h" "automatic_type_deduction.h" "casts.h" "unified_initialization.h" "const_constexpr_volatile.h" "move_semantics_perfect_forwarding.h" "memory_magagment.h" "functions.h" "classes_and_objects.h")

# Optionally, set the output directory for the binary
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
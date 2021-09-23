# Manadtory setting for minimal CMake requirement:
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Math_Proof)

# Build the library:
add_library(expression Math_Proof/expression.hpp Math_Proof/expression.cpp)
target_include_directories(expression PUBLIC Math_Proof)

add_library(statement Math_Proof/statement.hpp Math_Proof/statement.cpp)
target_include_directories(statement PUBLIC Math_Proof)
target_link_libraries(statement expression)

add_library(logic Math_Proof/Content/logic.hpp Math_Proof/Content/logic.cpp)
target_include_directories(logic PUBLIC Math_Proof/Content)
target_link_libraries(logic statement)

# Add the executable:
add_executable(Math_Proof Math_Proof/main.cpp)
target_link_libraries(Math_Proof logic)
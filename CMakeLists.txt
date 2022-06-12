# Manadtory setting for minimal CMake requirement:
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Math_Proof)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Build the library:
add_library(expression src/expression.hpp src/expression.cpp)
target_include_directories(expression PUBLIC src)

add_library(statement src/statement.hpp src/statement.cpp)
target_include_directories(statement PUBLIC src)

target_link_libraries(expression statement)
target_link_libraries(statement expression)

add_library(logic src/Content/logic.hpp src/Content/logic.cpp)
target_include_directories(logic PUBLIC src/Content)
target_link_libraries(logic statement)

add_library(set src/Content/set.hpp src/Content/set.cpp)
target_include_directories(set PUBLIC src/Content)
target_link_libraries(set statement)

# Add the executable:
add_executable(main src/main.cpp)
target_link_libraries(main logic)
target_link_libraries(main set)
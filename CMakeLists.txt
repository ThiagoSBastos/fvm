cmake_minimum_required(VERSION 3.16)
project(FVM)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_COMPILER clang++)

add_subdirectory(lib/matrix)

add_executable(main src/main.cpp)

target_link_libraries(main PRIVATE matrix)

enable_testing()
add_subdirectory(lib/matrix/tests)

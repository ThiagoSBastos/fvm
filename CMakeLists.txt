cmake_minimum_required(VERSION 3.16)
project(FVM)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()

add_executable(main src/main.cpp)

add_subdirectory(lib/common)
add_subdirectory(lib/matrix)

target_link_libraries(main PRIVATE matrix common)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

FetchContent_MakeAvailable(googletest)

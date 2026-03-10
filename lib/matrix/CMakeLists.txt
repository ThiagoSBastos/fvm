add_library(matrix INTERFACE)

target_link_libraries(matrix
    INTERFACE common
)

target_include_directories(matrix
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(tests)

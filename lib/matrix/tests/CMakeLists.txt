add_executable(matrix_tests testmatrix.cpp)

target_link_libraries(matrix_tests
PRIVATE
matrix
)

add_test(NAME matrix_tests COMMAND matrix_tests)

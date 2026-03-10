add_executable(matrix_tests testmatrix.cpp)

target_link_libraries(matrix_tests
    PRIVATE
        matrix
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(matrix_tests)

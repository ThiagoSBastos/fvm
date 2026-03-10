#include "matrix.hpp"

#include <algorithm>
#include <array>
#include <gtest/gtest.h>

constexpr double tol = 1.0E-12;

TEST(MatrixCSR, Test1) {
  matrix::compressed_sparse_row<double> matrix(
      matrix::NNz{4U}, matrix::NRows{4U}, matrix::NColumns{4U});
  std::ranges::copy(std::array<std::size_t, 4>{0, 1, 2, 1},
                    matrix.col_index().begin());
  std::ranges::copy(std::array<std::size_t, 5>{0, 1, 2, 3, 4},
                    matrix.row_index().begin());
  std::ranges::copy(std::array<double, 4>{5.0, 8.0, 3.0, 6.0},
                    matrix.data().begin());

  auto dense_res = matrix.to_dense();

  ASSERT_EQ(dense_res.size(), 4);
  for (const auto &row_vec : dense_res) {
    ASSERT_EQ(row_vec.size(), 4);
  }

  // clang-format off
    EXPECT_NEAR(dense_res[0][0], 5.0, tol); EXPECT_NEAR(dense_res[0][1], 0.0, tol); EXPECT_NEAR(dense_res[0][2], 0.0, tol); EXPECT_NEAR(dense_res[0][3], 0.0, tol);
    EXPECT_NEAR(dense_res[1][0], 0.0, tol); EXPECT_NEAR(dense_res[1][1], 8.0, tol); EXPECT_NEAR(dense_res[1][2], 0.0, tol); EXPECT_NEAR(dense_res[1][3], 0.0, tol);
    EXPECT_NEAR(dense_res[2][0], 0.0, tol); EXPECT_NEAR(dense_res[2][1], 0.0, tol); EXPECT_NEAR(dense_res[2][2], 3.0, tol); EXPECT_NEAR(dense_res[2][3], 0.0, tol);
    EXPECT_NEAR(dense_res[3][0], 0.0, tol); EXPECT_NEAR(dense_res[3][1], 6.0, tol); EXPECT_NEAR(dense_res[3][2], 0.0, tol); EXPECT_NEAR(dense_res[3][3], 0.0, tol);
  // clang-format on
}

TEST(MatrixCSR, Test2) {
  matrix::compressed_sparse_row<double> matrix(
      matrix::NNz{8U}, matrix::NRows{4U}, matrix::NColumns{6U});
  std::ranges::copy(std::array<std::size_t, 8>{0, 1, 1, 3, 2, 3, 4, 5},
                    matrix.col_index().begin());
  std::ranges::copy(std::array<std::size_t, 5>{0, 2, 4, 7, 8},
                    matrix.row_index().begin());
  std::ranges::copy(
      std::array<double, 8>{10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0},
      matrix.data().begin());

  auto dense_res = matrix.to_dense();

  ASSERT_EQ(dense_res.size(), 4);
  for (const auto &row_vec : dense_res) {
    ASSERT_EQ(row_vec.size(), 6);
  }

  // clang-format off
    EXPECT_NEAR(dense_res[0][0], 10.0, tol); EXPECT_NEAR(dense_res[0][1], 20.0, tol); EXPECT_NEAR(dense_res[0][2], 0.0, tol); EXPECT_NEAR(dense_res[0][3], 0.0, tol); EXPECT_NEAR(dense_res[0][4], 0.0, tol); EXPECT_NEAR(dense_res[0][5], 0.0, tol);
    EXPECT_NEAR(dense_res[1][0], 0.0, tol); EXPECT_NEAR(dense_res[1][1], 30.0, tol); EXPECT_NEAR(dense_res[1][2], 0.0, tol); EXPECT_NEAR(dense_res[1][3], 40.0, tol); EXPECT_NEAR(dense_res[1][4], 0.0, tol); EXPECT_NEAR(dense_res[1][5], 0.0, tol);
    EXPECT_NEAR(dense_res[2][0], 0.0, tol); EXPECT_NEAR(dense_res[2][1], 0.0, tol); EXPECT_NEAR(dense_res[2][2], 50.0, tol); EXPECT_NEAR(dense_res[2][3], 60.0, tol); EXPECT_NEAR(dense_res[2][4], 70.0, tol); EXPECT_NEAR(dense_res[2][5], 0.0, tol);
    EXPECT_NEAR(dense_res[3][0], 0.0, tol); EXPECT_NEAR(dense_res[3][1], 0.0, tol); EXPECT_NEAR(dense_res[3][2], 0.0, tol); EXPECT_NEAR(dense_res[3][3], 0.0, tol); EXPECT_NEAR(dense_res[3][4], 0.0, tol); EXPECT_NEAR(dense_res[3][5], 80.0, tol);
  // clang-format on
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

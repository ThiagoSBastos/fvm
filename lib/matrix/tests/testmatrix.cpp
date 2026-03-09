#include "matrix.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>

namespace {
constexpr double tol = 1.0E-12;
const auto is_approx = [](double val, double expected) -> bool {
  return std::abs(val - expected) <= tol;
};
} // namespace

void test1() {
  compressed_sparse_row<double, std::size_t> matrix(4U, 4U, 4);
  std::ranges::copy(std::array<std::size_t, 4>{0, 1, 2, 1},
                    matrix.col_index().begin());
  std::ranges::copy(std::array<std::size_t, 5>{0, 1, 2, 3, 4},
                    matrix.row_index().begin());
  std::ranges::copy(std::array<double, 5>{5.0, 8.0, 3.0, 6.0},
                    matrix.data().begin());

  auto dense_res = matrix.to_dense();

  assert(dense_res.size() == 4);
  for (const auto row_vec : dense_res) {
    assert(row_vec.size() == 4);
  }

  // clang-format off
  assert(is_approx(dense_res[0][0], 5.0) && is_approx(dense_res[0][1], 0.0) && is_approx(dense_res[0][2], 0.0) && is_approx(dense_res[0][3], 0.0)); 
  assert(is_approx(dense_res[1][0], 0.0) && is_approx(dense_res[1][1], 8.0) && is_approx(dense_res[1][2], 0.0) && is_approx(dense_res[1][3], 0.0));
  assert(is_approx(dense_res[2][0], 0.0) && is_approx(dense_res[2][1], 0.0) && is_approx(dense_res[2][2], 3.0) && is_approx(dense_res[2][3], 0.0)); 
  assert(is_approx(dense_res[3][0], 0.0) && is_approx(dense_res[3][1], 6.0) && is_approx(dense_res[3][2], 0.0) && is_approx(dense_res[3][3], 0.0));
  // clang-format on
}

void test2() {
  compressed_sparse_row<double, std::size_t> matrix(8U, 4U, 6);
  std::ranges::copy(std::array<std::size_t, 8>{0, 1, 1, 3, 2, 3, 4, 5},
                    matrix.col_index().begin());
  std::ranges::copy(std::array<std::size_t, 5>{0, 2, 4, 7, 8},
                    matrix.row_index().begin());
  std::ranges::copy(
      std::array<double, 8>{10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0},
      matrix.data().begin());

  auto dense_res = matrix.to_dense();

  assert(dense_res.size() == 4);
  for (const auto row_vec : dense_res) {
    assert(row_vec.size() == 6);
  }
  // clang-format off
  assert(is_approx(dense_res[0][0], 10.0) && is_approx(dense_res[0][1], 20.0) && is_approx(dense_res[0][2],  0.0) && is_approx(dense_res[0][3],  0.0) && is_approx(dense_res[0][4],  0.0) && is_approx(dense_res[0][5],  0.0)); 
  assert(is_approx(dense_res[1][0],  0.0) && is_approx(dense_res[1][1], 30.0) && is_approx(dense_res[1][2],  0.0) && is_approx(dense_res[1][3], 40.0) && is_approx(dense_res[1][4],  0.0) && is_approx(dense_res[1][5],  0.0)); 
  assert(is_approx(dense_res[2][0],  0.0) && is_approx(dense_res[2][1],  0.0) && is_approx(dense_res[2][2], 50.0) && is_approx(dense_res[2][3], 60.0) && is_approx(dense_res[2][4], 70.0) && is_approx(dense_res[2][5],  0.0)); 
  assert(is_approx(dense_res[3][0],  0.0) && is_approx(dense_res[3][1],  0.0) && is_approx(dense_res[3][2],  0.0) && is_approx(dense_res[3][3],  0.0) && is_approx(dense_res[3][4],  0.0) && is_approx(dense_res[3][5], 80.0));
  // clang-format on
}

int main() {
  test1();
  test2();
  return 0;
}

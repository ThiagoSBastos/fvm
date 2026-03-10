#pragma once

#include "strong_type.hpp"

#include <concepts>
#include <numeric>
#include <ranges>
#include <span>
#include <vector>

namespace matrix {
using NRows = strong_type<std::size_t, struct NRowsTag>;
using NColumns = strong_type<std::size_t, struct NColumnsTag>;
using NNz = strong_type<std::size_t, struct NNzTag>;

template <class DataT>
  requires std::floating_point<DataT>
class compressed_sparse_row {
  std::vector<std::size_t> m_col_index;
  std::vector<std::size_t> m_row_index;
  std::vector<DataT> m_data;
  std::size_t m_ncolumns;

public:
  std::vector<std::vector<DataT>> to_dense() const {
    const std::size_t number_of_rows = this->nrows();
    std::vector<std::vector<DataT>> result(number_of_rows,
                                           std::vector<DataT>(m_ncolumns));

    auto row = [&](std::size_t i) {
      return std::views::iota(m_row_index[i], m_row_index[i + 1]) |
             std::views::transform([this](std::size_t j) {
               return std::pair{m_col_index[j], m_data[j]};
             });
    };

    for (auto i : std::ranges::iota_view{0U, number_of_rows}) {
      for (auto [col, val] : row(i)) {
        result[i][col] = val;
      }
    }

    return result;
  }

  std::span<std::size_t> col_index() noexcept { return m_col_index; }

  std::span<std::size_t> row_index() noexcept { return m_row_index; }

  std::span<DataT> data() noexcept { return m_data; }

  constexpr std::size_t ncolumns() const noexcept { return m_ncolumns; }

  constexpr std::size_t nrows() const noexcept {
    return m_row_index.size() - 1U;
  }

  explicit constexpr compressed_sparse_row(NNz nnz, NRows nrows,
                                           NColumns ncolumns)
      : m_col_index(std::vector<std::size_t>(nnz.get())),
        m_data(std::vector<DataT>(nnz.get())),
        m_row_index(std::vector<std::size_t>(nrows.get() + 1)),
        m_ncolumns(ncolumns.get()) {}
};

template <class DataT>
  requires std::floating_point<DataT>
constexpr std::vector<DataT> multiply(compressed_sparse_row<DataT> mat,
                                      std::span<DataT> vec) {
  // precondition
  static_assert(vec.size() == mat.ncolumns());
  constexpr auto nrows = mat.nrows();
  std::vector<DataT> result(nrows);

  for (auto i : std::ranges::iota_view{0U, nrows}) {
    auto sub_mat = mat.data() | std::views::drop(mat.row_index(i)) |
                   std::views::take(mat.row_index(i + 1));
    auto col_vec = vec | std::views::drop(mat.row_index(i)) |
                   std::views::take(mat.row_index(i + 1));

    result[i] = std::inner_product(sub_mat, col_vec, 0.0);
  }

  // post condition
  static_assert(result.size() == mat.row_index().size() - 1);
  return result;
}
} // namespace matrix

#pragma once

#include <concepts>
#include <ranges>
#include <span>
#include <tuple>
#include <vector>

template <class DataT, class SizeT>
  requires std::floating_point<DataT> && std::integral<SizeT>
class compressed_sparse_row {
  std::vector<SizeT> m_col_index;
  std::vector<SizeT> m_row_index;
  std::vector<DataT> m_data;
  SizeT m_ncolumns;

public:
  constexpr std::vector<std::vector<DataT>> to_dense() const {
    SizeT nrows = m_row_index.size() - 1U;
    std::vector<std::vector<DataT>> result(nrows,
                                           std::vector<DataT>(m_ncolumns));

    for (auto i : std::ranges::iota_view{0U, nrows}) {
      const auto row_start = m_row_index[i];
      const auto row_end = m_row_index[i + 1];
      for (auto j : std::ranges::iota_view{row_start, row_end}) {
        result[i][m_col_index[j]] = m_data[j];
      }
    }

    return result;
  }

  constexpr std::span<SizeT> col_index() { return m_col_index; }

  constexpr std::span<SizeT> row_index() { return m_row_index; }

  constexpr std::span<DataT> data() { return m_data; }

  explicit constexpr compressed_sparse_row<DataT>(SizeT nnz, SizeT nrows,
                                                  SizeT ncolumns)
      : m_col_index(std::vector<SizeT>(nnz)), m_data(std::vector<DataT>(nnz)),
        m_row_index(std::vector<SizeT>(nrows + 1)), m_ncolumns(ncolumns) {}
};

template <class DataT, class SizeT>
  requires std::floating_point<DataT> && std::integral<SizeT>
constexpr std::vector<DataT> multiply(compressed_sparse_row<DataT, SizeT> mat,
                                      std::span<DataT> vec) {
  // precondition
  static_assert(vec.size() == mat.row_index().size() - 1);
  std::vector<DataT> result;
  return result;
}

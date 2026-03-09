#pragma once

#include <concepts>

template <class T>
  requires std::floating_point<T>
struct Vec3 {
  T x;
  T y;
  T z;
};

#pragma once

#include <iosfwd>

template <class Derived> struct printable {
  friend std::ostream &operator<<(std::ostream &os, Derived const &d) {
    os << d.get();
    return os;
  }
};

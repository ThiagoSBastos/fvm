#pragma once

#include <ostream>
#include <utility>

template <class T, class Tag, template <typename> class... Skills>
class strong_type : public Skills<strong_type<T, Tag, Skills...>>... {
public:
  using value_type = T;
  explicit constexpr strong_type(T const &value) : val(value) {}
  void swap(strong_type &other) { std::swap(val, other.val); }
  constexpr T &get() noexcept { return val; }
  constexpr T const &get() const noexcept { return val; }

private:
  value_type val;
};

template <typename T, typename Tag, template <typename> class... Skills>
std::ostream &operator<<(std::ostream &os,
                         strong_type<T, Tag, Skills...> const &nt) {
  os << nt.get();
  return os;
}

template <typename T, typename Tag, template <typename> class... Skills>
void swap(strong_type<T, Tag, Skills...> &a,
          strong_type<T, Tag, Skills...> &b) {
  a.swap(b);
}

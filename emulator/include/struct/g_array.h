#pragma once

#include "g_defs.h"
#include <array>
#include <vector>

namespace gluon {

namespace containers {

  template <class ContainerType>
  class stl_array {
  private:
    using Self = stl_array<ContainerType>;
    ContainerType data_;
  public:
    using iterator = typename ContainerType::iterator;
    using value_type = typename ContainerType::value_type;

    size_t size() const { return data_.size(); }

    value_type &operator [] (size_t i) {
      G_ASSERT(i < size());
      return data_[i];
    }
    const value_type &operator [] (size_t i) const {
      G_ASSERT(i < size());
      return data_[i];
    }

    // Storage access
    value_type *data() { return data_.data(); }
    const value_type *data() const { return data_.data(); }

    value_type &front() { return data_.front(); }
    const value_type &front() const { return data_.front(); }

    value_type &back() { return data_.back(); }
    const value_type &back() const { return data_.back(); }

    iterator begin() { return data_.begin(); }
    iterator end() { return data_.end(); }

    void reserve(size_t sz) { data_.reserve(sz); }

    void push_back(const value_type &x) { data_.push_back(x); }
  };

} // ns containers

// A fixed array
template <typename Val, size_t Sz>
using Array = containers::stl_array<std::array<Val, Sz>>;

// A growable vector
template <typename Val>
using Vector = containers::stl_array<std::vector<Val>>;

template <class Mapping, typename Callable>
void for_each(Mapping &m, Callable fn) {
  while (m.have()) {
    fn(m.value());
    m.advance();
  }
}

} // ns gluon
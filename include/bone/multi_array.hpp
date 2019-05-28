#pragma once

#include <initializer_list>
#include <vector>
#include <array>

namespace bone {

template <typename T, std::size_t N>
class multi_array {
public:
  template <typename... Args>
  multi_array(Args... args) : data_(new T[(... + args)]), own(true), sizes_{std::size_t(args)...} {}
  ~multi_array() {
    if(own)
      delete[] data_;
  }

  template <typename... Args>
  T& operator()(std::size_t dim, Args... args) {
    return operator()(dim)(args...);
  }
  template<bool b = (N>1)>
  std::enable_if_t<b, multi_array<T,N-1>> operator()(std::size_t dim) {
    return {data_+dim*sizes_[1], sizes_};
  }
  template<bool b = N==1>
  std::enable_if_t<b, T&> operator()(std::size_t dim) {
    return data_[dim];
  }
  auto operator[](std::size_t dim) {
    return operator()(dim);
  }

  template <typename... Args>
  T operator()(std::size_t dim, Args... args) const {
    return operator()(dim)(args...);
  }
  template<bool b = (N>1)>
  std::enable_if_t<b, multi_array<T,N-1> const> operator()(std::size_t dim) const {
    return {data_+dim*sizes_[1], sizes_};
  }
  template<bool b = N==1>
  std::enable_if_t<b, T> operator()(std::size_t dim) const {
    return data_[dim];
  }
  auto operator[](std::size_t dim) const {
    return operator()(dim);
  }

  std::size_t size() {
    return sizes_[0];
  }

private:
  friend class multi_array<T, N+1>;

  multi_array(T* data, std::array<std::size_t, N+1> const& sizes) : data_(data), own(false) {
    std::copy(sizes.begin()+1, sizes.end(), sizes_.begin());
  }

  T* data_;
  bool own;
  std::array<std::size_t, N> sizes_;
};

}
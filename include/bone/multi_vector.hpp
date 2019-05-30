#pragma once

#include <initializer_list>
#include <vector>
#include <array>
#include <functional>
#include <numeric>
#include <iostream>
namespace bone {

template <typename T, std::size_t N>
class frag {
public:
  frag(T* data, std::size_t* sizes) : data(data), sizes(sizes) {}

  template <typename... Args>
  auto operator()(std::size_t i, Args... args) {
    return frag<T, N-1>(data + i*sizes[1], sizes+1)(args...);
  }
  auto operator()(std::size_t i) {
    return frag<T, N-1>(data + i*sizes[1], sizes+1);
  }
  auto operator[](std::size_t i) {
    return operator()(i);
  }

  std::size_t size() {
    return sizes[0] / sizes[1];
  }

private:
  T* data;
  std::size_t* sizes;
};

template <typename T>
class frag<T, 0> {
public:
  frag(T* data, std::size_t*) : data(*data) {}
  operator T&() { return data; }
  operator T const&() const { return data; }
  template <typename U>
  auto operator=(U&& rhs) {
    return data = std::forward<U>(rhs);
  }
private:
  T& data;
};

template <typename T, std::size_t N>
class multi_vector : public frag<T, N> {
public:
  template <typename... Args>
  explicit multi_vector(Args... args) : multi_vector(std::vector<T>((... * args)), {std::size_t(args)...})
  {
    static_assert(sizeof...(args) == N);
  }

private:
  multi_vector(std::vector<T> d, std::vector<std::size_t> s)
    : frag<T,N>(d.data(), s.data())
    , data(std::move(d))
    , sizes(std::move(s))
  {
    sizes[N] = 1;
    for(int i=N-1; i>=0; --i) {
      sizes[i] *= sizes[i+1];
    }
  }

  std::vector<T> data;
  std::vector<std::size_t> sizes;
};

}

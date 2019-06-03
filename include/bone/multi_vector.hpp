#pragma once

#include <initializer_list>
#include <vector>
#include <array>
#include <functional>
#include <numeric>
//#include <iostream>
#include <stdexcept>

namespace bone {

template <typename T, std::size_t N>
class frag {
public:
  frag(T* data, std::size_t* sizes) : data(data), sizes(sizes) {}

  template <typename... Args>
  std::conditional_t<sizeof...(Args) == N, T&, frag<T,N-sizeof...(Args)>>
  operator()(Args... args) {
    return getFrag(std::forward<Args>(args)...).get();
  }
  std::conditional_t<N==1, T&, frag<T,N-1>>
  operator[](std::size_t i) {
    return getFrag(i).get();
  }

  std::size_t size() {
    return sizes[0] / sizes[1];
  }

public:
  template <typename... Args>
  auto getFrag(std::size_t i, Args... args) {
    return frag<T, N-1>(data + i*sizes[1], sizes+1).getFrag(std::forward<Args>(args)...);
  }
  auto getFrag(std::size_t i) {
    return frag<T, N-1>(data + i*sizes[1], sizes+1);
  }
  frag& get() { return *this; }
  
private:
  T* data;
  std::size_t* sizes;
};

template <typename T>
class frag<T, 0> {
public:
  frag(T* data, std::size_t*) : data(*data) {}
  T& get() { return data; }
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

#pragma once

#include <initializer_list>
#include <vector>
#include <array>
#include <functional>
#include <numeric>
#include <stdexcept>
#include <algorithm>

namespace bone {

template <typename T, std::size_t N>
class frag {
public:
  frag& operator=(frag const& rhs) {
    if(&rhs == this) return *this;
    if(std::equal(sizes, sizes+N, rhs.sizes)) {
      std::copy(rhs.data, rhs.data+*sizes, data);
    }
    else {
      throw std::out_of_range("assigning arrays of different length");
    }
    return *this;
  }

  frag& operator=(std::initializer_list<T> const& rhs) {
    if(rhs.size() == *sizes) {
      std::copy(rhs.begin(), rhs.end(), data);
    }
    else {
      throw std::out_of_range("assigning arrays of different length");
    }
    return *this;
  }

  bool operator==(frag const& rhs) const {
    return std::equal(sizes, sizes+N, rhs.sizes) && std::equal(data, data+sizes[0], rhs.data);
  }
  bool operator!=(frag const& rhs) const {
    return !(*this == rhs);
  }

  std::size_t size() {
    return sizes[0] / sizes[1];
  }

  std::size_t flat_size() {
    return sizes[0];
  }

  T* flat_data() {
    return data;
  };

protected:
  frag(T* data, std::size_t* sizes) : data(data), sizes(sizes) {}
  
public:
  template <typename... Args>
  decltype(auto) operator()(std::size_t i, Args&&... args) {
    return operator[](i)(std::forward<Args>(args)...);
  }
  decltype(auto) operator()(std::size_t i) {
    return operator[](i);
  }
  decltype(auto) operator[](std::size_t i) {
    return lookup(i);
  }

private:
  class iterator_base {
    typedef std::random_access_iterator_tag         iterator_category;
    typedef std::ptrdiff_t                          difference_type;

  public:
    iterator_base(T* data, std::size_t* sizes) : data(data), sizes(sizes) {}

    bool operator==(iterator_base const& rhs) { return data == rhs.data && sizes == rhs.sizes; }
    bool operator!=(iterator_base const& rhs) { return !operator==(rhs); }
    iterator_base& operator++() { data += sizes[1]; return *this; }
    
  protected:
    T* data;
    std::size_t* sizes;
  };

  template<std::size_t M, int I42=0>
  class iteratorN final : public iterator_base {
  public:
    typedef frag<T, N-1> value_type;
    typedef value_type*  pointer;
    typedef frag<T, N-1> reference;

    using iterator_base::iterator_base;
    frag<T,N> operator*() { return {this->data, this->sizes}; }
  };

  template<int I42>
  class iteratorN<1, I42> final : public iterator_base {
  public:
    typedef T            value_type;
    typedef value_type*  pointer;
    typedef value_type&  reference;

    using iterator_base::iterator_base;
    T& operator*() { return *this->data; }
  };

public:
  using iterator = iteratorN<N>;

  iterator begin() { return iterator(data, sizes); }
  iterator end() { return iterator(data + sizes[0], sizes); }
  
private:
  T* data;
  std::size_t* sizes;
  
  template <typename U, std::size_t M>
  friend class frag;
  
  template<std::size_t M=N>
  std::enable_if_t<(M>1), frag<T,N-1>> lookup(std::size_t i) {
    return frag<T, N-1>(data + i*sizes[1], sizes+1);
  }
  template<std::size_t M=N>
  std::enable_if_t<M==1, T&> lookup(std::size_t i) {
    return data[i];
  }
};

template <typename T, std::size_t N>
class multi_array : public frag<T, N> {
public:
  template <typename... Args>
  explicit multi_array(Args... args) : multi_array(std::vector<T>((... * args)), {std::size_t(args)...})
  {
    static_assert(sizeof...(args) == N);
  }

private:
  multi_array(std::vector<T> d, std::vector<std::size_t> s)
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

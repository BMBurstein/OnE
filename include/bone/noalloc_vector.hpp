#pragma once

#include <vector>

namespace bone {

template <typename T, std::size_t SIZE>
class noalloc_vector : private std::vector<T> {
public:
  noalloc_vector() {
    std::vector<T>::reserve(SIZE);
  }

  noalloc_vector& operator=( const noalloc_vector& other ){
    static_cast<std::vector<T>&>(*this) = static_cast<std::vector<T>&>(*other);
  }
  noalloc_vector& operator=( noalloc_vector&& other ){
    static_cast<std::vector<T>&>(*this) = std::move(static_cast<std::vector<T>&>(*other));
  }
  noalloc_vector& operator=(std::initializer_list<T> ilist) {
    assign(ilist);
    return *this;
  }

  void swap(noalloc_vector& other) noexcept {
    std::vector<T>::swap(other);
  }

  // not implemented:
  //   get_allocator()
  //   reserve()
  //   shrink_to_fit()

  // pass through:
  using std::vector<T>::at;
  using std::vector<T>::operator[];
  using std::vector<T>::front;
  using std::vector<T>::back;
  using std::vector<T>::data;
  using std::vector<T>::begin;
  using std::vector<T>::cbegin;
  using std::vector<T>::end;
  using std::vector<T>::cend;
  using std::vector<T>::rbegin;
  using std::vector<T>::rend;
  using std::vector<T>::crbegin;
  using std::vector<T>::crend;
  using std::vector<T>::empty;
  using std::vector<T>::size;
  using std::vector<T>::capacity;
  using std::vector<T>::clear;
  using std::vector<T>::erase;
  using std::vector<T>::pop_back;
  typename std::vector<T>::size_type max_size() const noexcept { return capacity(); }

  // return value has been changed to bool to reflect success or failure:
  //   emplace
  //   emplace_back
  //   push_back
  //   insert
  //   resize
  //   assign
  #define GROW_FUNC_BODY(cond,func)\
    if(cond) {\
      std::vector<T>::func;\
      return true;\
    }\
    else\
      return false
  #define GROW_1_FUNC(name)\
  template<class... Args>\
  bool name(Args&&... args) {\
    GROW_FUNC_BODY(size() < capacity(), name(std::forward<Args>(args)...));\
  }

  GROW_1_FUNC(emplace)
  GROW_1_FUNC(emplace_back)
  GROW_1_FUNC(push_back)
  
  bool insert(typename std::vector<T>::const_iterator pos, const T& value) {
    GROW_FUNC_BODY(size() < capacity(), insert(pos, value));
  }
  bool insert(typename std::vector<T>::const_iterator pos, T&& value) {
    GROW_FUNC_BODY(size() < capacity(), insert(pos, std::move(value)));
  }
  bool insert(typename std::vector<T>::const_iterator pos, typename std::vector<T>::size_type count, const T& value) {
    GROW_FUNC_BODY(size() + count <= capacity(), insert(pos, count, std::move(value)));
  }
  template <class ForwardIt>
  bool insert(typename std::vector<T>::const_iterator pos, ForwardIt first, ForwardIt last) {
    GROW_FUNC_BODY(size() + std::distance(first, last) <= capacity(), insert(pos, std::move(first), std::move(last)));
  }
  bool insert(typename std::vector<T>::const_iterator pos, std::initializer_list<T> ilist) {
    GROW_FUNC_BODY(size() + ilist.size() <= capacity(), insert(pos, std::move(ilist)));
  }

  bool resize(typename std::vector<T>::size_type count) {
    GROW_FUNC_BODY(count <= capacity(), resize(count));
  }
  bool resize(typename std::vector<T>::size_type count, const typename std::vector<T>::value_type& value) {
    GROW_FUNC_BODY(count <= capacity(), resize(count, value));
  }

  void assign(typename std::vector<T>::size_type count, const T& value) {
    GROW_FUNC_BODY(count <= capacity(), assign(count, value));
  }
  template <class ForwardIt>
  void assign(ForwardIt first, ForwardIt last) {
    GROW_FUNC_BODY(std::distance(first, last) <= capacity(), assign(std::move(first), std::move(last)));
  }
  void assign(std::initializer_list<T> ilist) {
    GROW_FUNC_BODY(ilist.size() <= capacity(), assign(std::move(ilist)));
  }
  
  #undef GROW_1_FUNC
  #undef GROW_FUNC_BODY
};

template <typename T, std::size_t SIZE>
void swap(noalloc_vector<T, SIZE>& lhs, noalloc_vector<T, SIZE>& rhs) noexcept {
  lhs.swap(rhs);
}

}

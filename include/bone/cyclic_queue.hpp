#pragma once

#include <array>
#include <utility>
#include <type_traits>

namespace bone {

template <typename T, std::size_t SIZE>
class cyclic_queue {
public:
  cyclic_queue() : head_(0), tail_(0), size_(0) { }
  
  bool push(const T& val) {
    return emplace(val);
  }
  
  bool push(T&& val) {
    return emplace(std::move(val));
  }
  
  bool pop() {
    if(size_ == 0)
      return false;
    reinterpret_cast<T&>(data[head_]).~T();
    ++head_;
    head_ %= SIZE;
    --size_;
    return true;
  }

  T& front() {
    return reinterpret_cast<T&>(data[head_]);
  }
  
  T const& front() const {
    return reinterpret_cast<T const&>(data[head_]);
  }
  
  std::size_t size() const {
    return size_;
  }
  
  bool empty() const {
    return size_ == 0;
  }
  
  template< class... Args >
  bool emplace(Args&&... args) {
    if(size_ == SIZE)
      return false;
    new (&data[tail_]) T(std::forward<Args>(args)...);
    ++tail_;
    tail_ %= SIZE;
    ++size_;
    return true;
  }

private:
  std::array<typename std::aligned_storage<sizeof(T), alignof(T)>::type, SIZE> data;
  std::size_t head_;
  std::size_t tail_;
  std::size_t size_;
};

}

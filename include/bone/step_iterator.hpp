#include <iterator>
#include <algorithm>

namespace bone {

template <class Iter>
class step_iterator
{
public:
  typedef Iter                                                   iterator_type;
  typedef typename std::iterator_traits<Iter>::iterator_category iterator_category;
  typedef typename std::iterator_traits<Iter>::value_type        value_type;
  typedef typename std::iterator_traits<Iter>::difference_type   difference_type;
  typedef typename std::iterator_traits<Iter>::reference         reference;
  typedef typename std::iterator_traits<Iter>::pointer           pointer;

  step_iterator()
    : current(),
      step(),
      fromEnd()
  {}

  step_iterator(Iter begin, Iter const& end, difference_type step)
    : current(std::move(begin)),
    step(std::move(step)),
    fromEnd(std::distance(begin, end))
  {}

  step_iterator(Iter begin, difference_type step, std::size_t size)
    : current(std::move(begin)),
    step(std::move(step)),
    fromEnd(size)
  {}

  Iter base() const { return current; }

  reference operator*() const { return *current; }

  pointer  operator->() const { return current.operator->(); }

  step_iterator& operator++() {
    auto dist = std::min(step, fromEnd);
    std::advance(current, dist);
    fromEnd -= step;
    return *this;
  }

  step_iterator& operator--() {
    fromEnd += step;
    auto dist = -std::min(step, fromEnd);
    std::advance(current, dist);
    return *this;
  }

  step_iterator& operator+=(difference_type n) {
    auto dist = std::min(step * n, fromEnd);
    std::advance(current, dist);
    fromEnd -= step * n;
    return *this;
  }

  step_iterator& operator-=(difference_type n) {
    fromEnd += step * n;
    auto dist = -std::min(step * n, fromEnd);
    std::advance(current, dist);
    return *this;
  }

  step_iterator  operator++(int) { step_iterator tmp(*this); ++*this; return tmp; }

  step_iterator  operator--(int) { step_iterator tmp(*this); --*this; return tmp; }

  step_iterator  operator+ (difference_type n) const { step_iterator tmp(*this); tmp += n; return tmp; }

  step_iterator  operator- (difference_type n) const { step_iterator tmp(*this); tmp -= n; return tmp; }

  reference      operator[](difference_type n) const { return *(*this + n); }

  friend
  step_iterator operator+(difference_type n, step_iterator const& it) { return it + n; }

  difference_type operator-(step_iterator const& rhs) {
    return (current - rhs.current) / step;
  }

protected:
  Iter current;
  difference_type step;
  difference_type fromEnd;
};

template <class _Iter1, class _Iter2>
inline
bool operator==(const step_iterator<_Iter1>& lhs, const step_iterator<_Iter2>& rhs) {
  return lhs.base() == rhs.base();
}

template <class _Iter1, class _Iter2>
inline
bool operator<(const step_iterator<_Iter1>& lhs, const step_iterator<_Iter2>& rhs) {
  return lhs.base() < rhs.base();
}

template <class _Iter1, class _Iter2>
inline
bool operator!=(const step_iterator<_Iter1>& lhs, const step_iterator<_Iter2>& rhs) {
  return lhs.base() != rhs.base();
}

template <class _Iter1, class _Iter2>
inline
bool operator>(const step_iterator<_Iter1>& lhs, const step_iterator<_Iter2>& rhs) {
  return lhs.base() > rhs.base();
}

template <class _Iter1, class _Iter2>
inline
bool operator>=(const step_iterator<_Iter1>& lhs, const step_iterator<_Iter2>& rhs) {
  return lhs.base() >= rhs.base();
}

template <class _Iter1, class _Iter2>
inline
bool operator<=(const step_iterator<_Iter1>& lhs, const step_iterator<_Iter2>& rhs) {
  return lhs.base() <= rhs.base();
}

template <class Iter>
inline
step_iterator<Iter> make_step_iterator(Iter&& it, Iter&& end, typename step_iterator<Iter>::difference_type step) {
  return step_iterator<Iter>(std::forward<Iter>(it), std::forward<Iter>(end), step);
}

template <class Iter>
inline
step_iterator<Iter> make_step_iterator(Iter&& it, typename step_iterator<Iter>::difference_type step, std::size_t size) {
  return step_iterator<Iter>(std::forward<Iter>(it), step, size);
}

template <class Iter>
inline
step_iterator<Iter> make_step_iterator(Iter&& it) {
  return step_iterator<Iter>(std::forward<Iter>(it), 0, 0);
}

}
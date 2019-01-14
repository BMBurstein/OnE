#pragma once

#include <queue>

namespace bone {
  template<typename T,
           typename _Compare  = std::less<T>,
           template<typename> class _Container = std::vector>
  class stable_pq {
  private:
    std::size_t _cnt;

    struct stable_item {
      std::size_t idx;
      T itm;

      template<typename... _Args>
      stable_item(std::size_t i, _Args&&... __args)
      : idx(i),
        itm(std::forward<_Args>(__args)...)
      {}
    };

    struct StableCompare {
      _Compare comp;
      constexpr bool operator()(stable_item const& l, stable_item const& r) const {
        if(comp(l.itm, r.itm)) return true;
        if(comp(r.itm, l.itm)) return false;
        return l.idx > r.idx;
      }
    };

    typedef std::priority_queue<stable_item, _Container<stable_item>, StableCompare> _pq_t;

    _pq_t _pq;

  public:
    typedef typename _pq_t::value_type      value_type;
    typedef typename _pq_t::reference       reference;
    typedef typename _pq_t::const_reference const_reference;
    typedef typename _pq_t::size_type       size_type;
    typedef typename _pq_t::container_type  container_type;
    typedef          _Compare               value_compare;

    bool empty() const { return _pq.empty(); }

    std::size_t size() const { return _pq.size(); }

    void push(T const& v) {
      _pq.emplace(++_cnt, v);
    }
    void push(T&& v) {
      _pq.emplace(++_cnt, std::move(v));
    }

    template<typename... _Args>
    void emplace(_Args&&... __args) {
      _pq.emplace(++_cnt, std::forward<_Args>(__args)...);
    }

    void pop() {
      _pq.pop();
    }

    T const& top() const {
      return _pq.top().itm;
    }
  };
}

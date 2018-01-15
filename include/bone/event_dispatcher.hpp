#pragma once

#include <vector>
#include <functional>
#include <utility>
#include <type_traits>
#include <algorithm>

namespace bone {

template <class... Args>
class event_dispatcher {
private:
  using func_t = std::function<bool(Args...)>;

public:
  using handle_t = std::size_t;

  bool operator()(Args... args) const {
    for (auto& f : funcs) {
      if (!f(args...))
        return false;
    }
    return true;
  }

  template <class F>
  std::enable_if_t<std::is_invocable_r_v<bool, F, Args...>, handle_t>
  add(F&& f) {
    funcs.emplace_back(std::forward<F>(f));
    return funcs.size() - 1;
  }

  template <class F>
  std::enable_if_t<!std::is_invocable_r_v<bool, F, Args...> && std::is_invocable_v<F, Args...>, handle_t>
  add(F&& f) {
    return add([f_ = std::forward<F>(f)](Args... args){std::invoke(f_, std::forward<Args>(args)...); return true; });
  }

  void remove(handle_t const& h) {
    funcs[h] = [](Args...) {return true; };
  }

private:
  std::vector<func_t> funcs;
};

}

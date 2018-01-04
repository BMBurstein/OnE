#pragma once

#include <vector>
#include <functional>
#include <utility>
#include <type_traits>
#include <algorithm>

namespace bone {

template <class... Args>
class event_dispatcher {
public:
  using func_t = std::function<bool(Args...)>;

  bool operator()(Args... args) const {
    for (auto& f : funcs) {
      if (!f(args...))
        return false;
    }
    return true;
  }

  template <class F>
  std::enable_if_t<std::is_invocable_r_v<bool, F, Args...>>
  add(F&& f) {
    funcs.emplace_back(std::forward<F>(f));
  }

  template <class F>
  std::enable_if_t<!std::is_invocable_r_v<bool, F, Args...> && std::is_invocable_v<F, Args...>>
  add(F&& f) {
    funcs.emplace_back([f_ = std::forward<F>(f)](Args... args) {std::invoke(std::move(f_), std::move(args)...); return true; });
  }

private:
  std::vector<func_t> funcs;
};

}

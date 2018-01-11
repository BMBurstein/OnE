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
    funcs.emplace_back(MyFunc<F>{std::forward<F>(f)});
  }

  template <class F>
  std::enable_if_t<std::is_invocable_r_v<bool, F, Args...>, bool>
  remove(F&& f) {
    auto it = std::find_if(funcs.rbegin(), funcs.rend(), [&f](auto func) {
      auto p = func.template target<std::decay_t<F>>();
      return p ? std::equal_to<>()(*p, f) : false;
    });
    if (it != funcs.rend()) {
      funcs.erase(it.base() - 1);
      return true;
    }
    return false;
  }

  template <class F>
  std::enable_if_t<!std::is_invocable_r_v<bool, F, Args...> && std::is_invocable_v<F, Args...>, bool>
  remove(F&& f) {
    return remove(MyFunc<F>{std::forward<F>(f)});
  }

private:
  std::vector<func_t> funcs;

  template <class iF>
  struct MyFunc {
    MyFunc(iF f) : func(std::move(f)) {}
    bool operator()(Args... args) {
      std::invoke(func, std::forward<Args>(args)...);
      return true;
    }

    bool operator==(MyFunc const& rhs) { return std::equal_to<iF>()(func, rhs.func); }

    iF func;
  };
};

}

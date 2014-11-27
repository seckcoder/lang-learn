#include <map>

template <typename R, typename... Args>
std::function<R (Args...)> memoize (R (*fn) (Args...)) {
  std::map<std::tuple<Args...>,R> table;
  return [fn, table] (Args... args) mutable -> R {
    auto argt = std::make_tuple (args...);
    auto res = table.find (argt);
    if (res == table.end ()) {
      auto result = fn(args...);
      table[argt] = result;
      return result;
    } else {
      return res->second;
    }
  };
}

#ifndef _UTIL_HPP
#define _UTIL_HPP

#include <tuple>

#define variadic_to_tuple(T_typename, argname) std::tuple<T_typename...>(std::forward<T_typename>(argname)...)

// function type
template <typename T>
struct function_traits;

template <typename R, typename... Args>
struct function_traits<R(Args...)> {
    using return_type = R;
    using arguments   = std::tuple<Args...>;
    static constexpr std::size_t arity = sizeof...(Args);
};

template <typename R, typename... Args>
struct function_traits<R(*)(Args...)> : function_traits<R(Args...)> {};

#endif

#ifndef _UTIl_HPP
#define _UTIl_HPP

#define variadic_to_tuple(T_typename, argname) std::tuple<T_typename...>(std::forward<T_typename>(argname)...)
#include "uthread.hpp"
#include <tuple>

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

// misc
template <typename Fn, typename ...Args>
struct ThreadInfo {
   Fn callback;
   std::tuple< std::decay_t<Args>... > args;

   ThreadInfo(Fn&& fn, Args&&... args) : callback(fn), args( std::make_tuple(std::forward<Args>(args)...) ) {}
};

template <typename Fn, typename ...Args>
thread_return_t compliant_fn(thread_arg_t ptr) {
   auto info = static_cast< ThreadInfo<Fn, Args...>* >(ptr);
   std::apply(info->callback, std::move(info->args));
   delete info;
   return REGULAR_WRAPPER_RETURN;
}

#endif

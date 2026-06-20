#ifndef _INFO_HPP
#define _INFO_HPP

#include "_util.hpp"
#include "uthread.hpp"

// misc
template <typename Fn, typename ...Args>
struct ThreadInfo {
   Fn callback;
   std::tuple< std::decay_t<Args>... > args;

   ThreadInfo(Fn&& fn, Args&&... args) : callback(fn), args( std::make_tuple(std::forward<Args>(args)...) ) {}
};

template <typename Fn, typename ...Args>
thread_return_t base_wrapper(thread_arg_t ptr) {
   auto info = static_cast< ThreadInfo<Fn, Args...>* >(ptr);
   std::apply(info->callback, std::move(info->args));
   delete info;

   BASE_WRAPPER_RETURN;
}

#endif

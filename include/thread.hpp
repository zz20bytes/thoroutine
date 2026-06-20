#ifndef THREAD_HPP
#define THREAD_HPP

#include "_util.hpp"
#include "_info.hpp"
#include "uthread.hpp"

class MThread {
   underlying_thread_t _underlying;

   public:
      template <typename Fn, typename ...Args>
      MThread(Fn fn, Args&&... args) {
         using decay_fn = typename std::decay_t<Fn>;

         auto info = new ThreadInfo< decay_fn, Args&&... >(
            decay_fn(std::forward<Fn>(fn)),
            std::forward<Args>(args)...
         );

         uthread_create(&_underlying, base_wrapper< decay_fn, Args&&... >, info);
      }

      void detach() {
         uthread_detach(&_underlying);
      }

      void join() {
         uthread_join(&_underlying);
      }
};

#endif

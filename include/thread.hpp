#ifndef THREAD_HPP
#define THREAD_HPP

#include "_util.hpp"
#include "uthread.hpp"

class MThread {
   underlying_thread_t _underlying;

   public:
      template <typename Fn, typename ...Args>
      MThread(Fn fn, Args&&... args) {
         using decay_fn = typename std::decay_t<Fn>;

         auto info = new ThreadInfo< decay_fn, Args&&... >(
            std::decay_t<Fn>(std::forward<Fn>(fn)),
            std::forward<Args>(args)...
         );

         uthread_create(&_underlying, &compliant_fn< std::decay_t<Fn>, Args&&... >, info);
      }

      void detach() {
         uthread_detach(&_underlying);
      }

      void join() {
         uthread_join(&_underlying);
      }
};

#endif

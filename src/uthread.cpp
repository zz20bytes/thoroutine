#include "uthread.hpp"

#ifdef __linux__
   void uthread_create(underlying_thread_t* thread, void*(*fn)(void*), void* arg)
   {
      pthread_create(thread, nullptr, fn, arg);
   }

   void uthread_detach(underlying_thread_t* thread)
   {
      pthread_detach(*thread);
   }

   void uthread_join(underlying_thread_t* thread)
   {
      pthread_join(*thread, nullptr);
   }
#elif _WIN32
   void uthread_create(underlying_thread_t* thread, void*(*fn)(void*), void* arg)
   {
   }

   void uthread_detach(underlying_thread_t* thread)
   {
   }

   void uthread_join(underlying_thread_t* thread)
   {
   }
#endif

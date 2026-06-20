#include "uthread.hpp"

/*TODO:
 * make sure to deal with thread creation failure
 * add way to get thread id
*/

#ifdef __linux__
   void uthread_create(underlying_thread_t* thread, THREAD_FPOINTER_T(fn), thread_arg_t arg)
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
   void uthread_create(underlying_thread_t* thread, THREAD_FPOINTER_T(fn), thread_arg_t arg)
   {
      *thread = CreateThread(
         NULL,    // default security attributes
         0,       // default stack size
         fn,      // thread function
         arg,     // argument to thread function
         0,       // default creation flags
         NULL     // return pointer for thread identifier 
      );
   }

   void uthread_detach(underlying_thread_t* thread)
   {
      CloseHandle(*thread);
   }

   void uthread_join(underlying_thread_t* thread)
   {
      WaitForSingleObject(*thread, INFINITE);
      CloseHandle(*thread);
   }
#endif

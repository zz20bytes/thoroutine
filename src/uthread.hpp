#ifndef UTHREAD_HPP
#define UTHREAD_HPP

#ifdef __linux__
   #include <pthread.h>
   #define THREAD_FPOINTER_T(ptr_name) void* (*ptr_name)(void*)
   #define BASE_WRAPPER_RETURN return nullptr

   using underlying_thread_t = pthread_t;
   using thread_return_t = void*;
   using thread_arg_t = void*;
#elif _WIN32
   #include <windows.h>
   #define THREAD_FPOINTER_T(ptr_name) DWORD (WINAPI *ptr_name)(LPVOID)
   #define BASE_WRAPPER_RETURN return 0

   using underlying_thread_t = HANDLE;
   using thread_return_t = DWORD;
   using thread_arg_t = LPVOID;
#endif

void uthread_create(underlying_thread_t* thread, THREAD_FPOINTER_T(fn), thread_arg_t arg);
void uthread_detach(underlying_thread_t* thread);
void uthread_join(underlying_thread_t* thread);

#endif

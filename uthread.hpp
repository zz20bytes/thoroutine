#ifndef UTHREAD_HPP
#define UTHREAD_HPP

#ifdef __linux__
   #include <pthread.h>
   using underlying_thread_t = pthread_t;
#elif _WIN32
   #include <windows.h>
   using underlying_thread_t = HANDLE;
#endif

void uthread_create(underlying_thread_t* thread, void*(*fn)(void*), void* arg);
void uthread_detach(underlying_thread_t* thread);
void uthread_join(underlying_thread_t* thread);

#endif

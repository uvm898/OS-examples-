//
// Created by os on 9/15/22.
//

#ifndef PROJEKAT_SYSCALL_CPP_HPP
#define PROJEKAT_SYSCALL_CPP_HPP

#include "syscall_c.h"
#include "../lib/hw.h"


void* operator new(size_t);
void  operator delete(void*);


class Thread{
public:
    Thread (void (*body)(void*), void* arg);
    virtual ~Thread();

    int start();
    void join();
    static void dispatch();
    static int sleep(time_t){return 0;}

protected:
    Thread();
    virtual void run();


private:
    static void wrapper(void* t){ if(t) ((Thread*)t)->run(); }
    thread_t myHandle;
};

//class Semaphore {
//public:
//    Semaphore (unsigned init = 1);
//    virtual ~Semaphore ();
//    int wait ();
//    int signal ();
//private:
//    sem_t myHandle;
//};
//
//class PeriodicThread : public Thread {
//protected:
//    PeriodicThread (time_t period);
//    virtual void periodicActivation () {}
//};
//class Console {
//public:
//    static char getc ();
//    static void putc (char);
//};



#endif //PROJEKAT_SYSCALL_CPP_HPP

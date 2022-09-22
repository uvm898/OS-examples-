//
// Created by os on 9/15/22.
//

#include "../h/syscall_cpp.hpp"
#include "../h/MemoryAllocator.hpp"
#include "../h/syscall_c.h"
#include "../h/_thread.hpp"


void *operator new(size_t n){
    return mem_alloc(n);
}

void operator delete(void *p) {
    mem_free(p);
}

Thread::~Thread() { delete myHandle; }

void Thread::dispatch() { thread_dispatch(); }

void Thread::run() {}

Thread::Thread() {
    myHandle = nullptr;
}

void Thread::join() { thread_join(this->myHandle);}

Thread::Thread(void (*body)(void *), void *arg) {}

int Thread::start() {
        if(myHandle) return myHandle->getId();
        else return thread_create(&myHandle, &wrapper, this);
}







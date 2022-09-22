//
// Created by os on 9/15/22.
//

#include "../h/_thread.hpp"
#include "../h/MemoryAllocator.hpp"
#include "../h/riscv.hpp"

_thread *_thread::running;
_thread *_thread::mainThread;


void *operator new[](size_t n) {
    return MemoryAllocator::allocateMemory(n);
}

void operator delete[](void *p) noexcept {
    MemoryAllocator::freeMemory(p);
}


int _thread::kexit() {
    if (running == mainThread) return -1;
    _thread *newThr = Scheduler::get();
    if(newThr) {
        _thread* old=running;
        old->setFinished(true);
        _thread::contextSwitch(&old->context, &newThr->context);
        MemoryAllocator::freeMemory(old->stack); //da li ce se ikad vratiti ovde
    }
    return 0;
}

void _thread::dispatch()
{
    _thread *old = running;
    if (old!= nullptr && !old->isFinished())
        Scheduler::put(old);


    running = Scheduler::get();
    _thread::contextSwitch(&old->context, &running->context);
}

void _thread::thread_wrapper()
{
    Riscv::popSppSpie();
    running->body(running->getArg());
    running->setFinished(true);
    thread_dispatch();
}

_thread *_thread::kcreate_thread(_thread::Body body, void *arg, void *stackSpace)
{
    return new _thread(body,arg,stackSpace);
}


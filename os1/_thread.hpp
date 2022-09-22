//
// Created by os on 9/15/22.
//

#ifndef PROJEKAT__THREAD_HPP
#define PROJEKAT__THREAD_HPP

#include "../lib/hw.h"
#include "MemoryAllocator.hpp"
#include "scheduler.hpp"
#include "syscall_c.h"

static uint num_of_threads = 1;

void *operator new[](size_t n);

void operator delete[](void *p) noexcept;

class _thread {
public:

    ~_thread() { delete[] stack; }

    using Body = void (*)(void*);



    Body const getBody() const {
        return body;
    }

    void setBody(Body const) {
        _thread::body = body;
    }

    uint64 getId() const {
        return id;
    }

    void setId(uint64 id) {
        _thread::id = id;
    }

    void *getArg() const {
        return arg;
    }

    void setArg(void *arg) {
        _thread::arg = arg;
    }

    bool isFinished() const {
        return finished;
    }

    void setFinished(bool finished) {
        _thread::finished = finished;
    }

    static int kexit();

    static void dispatch();

    static _thread* kcreate_thread(Body body,void* arg, void * stackSpace);

    static _thread *running;
    static _thread *mainThread;



private:

    friend class Riscv;

    explicit _thread(Body body, void* arg, void* stackSpace) :
            body(body),
            arg(arg),
            finished(false),
            id(num_of_threads)
    {
        if(body!= nullptr) stack= new uint64[DEFAULT_STACK_SIZE];
        else stack= nullptr;

        context={body != nullptr ? (uint64) &thread_wrapper : 0,
                 stack != nullptr ? (uint64) &stack[DEFAULT_STACK_SIZE] : 0
        };
        num_of_threads++;
        if (body != nullptr) { Scheduler::put(this); }
    }

    struct Context {
        uint64 ra;
        uint64 sp;
    };

    Body body;
    void * arg;
    bool finished;
    uint64 id;
    uint64* stack;
    Context context;




    static void contextSwitch(Context* oldC,Context* newC);

    static void thread_wrapper();



};


#endif //PROJEKAT__THREAD_HPP

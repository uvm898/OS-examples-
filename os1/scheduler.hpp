//
// Created by os on 9/15/22.
//

#ifndef PROJEKAT_SCHEDULER_HPP
#define PROJEKAT_SCHEDULER_HPP
#include "list.hpp"

class _thread;

class Scheduler
{
private:
    static List<_thread> readyCoroutineQueue;

public:
    static _thread *get();

    static void put(_thread *ccb);

};

#endif //PROJEKAT_SCHEDULER_HPP

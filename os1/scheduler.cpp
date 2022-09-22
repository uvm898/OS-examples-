//
// Created by os on 9/15/22.
//

#include "../h/scheduler.hpp"


List<_thread> Scheduler::readyCoroutineQueue;

_thread *Scheduler::get()
{
    return readyCoroutineQueue.removeFirst();
}

void Scheduler::put(_thread *ccb)
{
    readyCoroutineQueue.addLast(ccb);
}
//
// Created by UVM
//
#include "../lib/console.h"
#include "../h/MemoryAllocator.hpp"
#include "../h/riscv.hpp"
#include "../h/syscall_c.h"
#include "../h/_thread.hpp"
#include "../h/syscall_cpp.hpp"


extern void userMain();

int main(){
    //initialize memory
    MemoryAllocator::initializeAddressSpace();
// dodaj prekidnu rutinu
    Riscv::w_stvec((uint64)&Riscv::supervisorTrap);
  //  printString("ovde sam");
   // Riscv::ms_sstatus(Riscv::SSTATUS_SIE);
   _thread::running=_thread::mainThread=_thread::kcreate_thread(nullptr, nullptr, nullptr);
   // printString("ovde sam");
    set_user_mode();
    //printString("ovde sam");

   userMain();
    return 0;
}


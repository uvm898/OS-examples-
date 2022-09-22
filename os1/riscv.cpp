//
// Created by os on 9/14/22.
//


#include "../h/riscv.hpp"
#include "../lib/console.h"

#include "../h/codes.h"
#include "../h/MemoryAllocator.hpp"
#include "../h/_thread.hpp"


void Riscv::popSppSpie()
{
    __asm__ volatile ("csrw sepc, ra");
    __asm__ volatile ("sret");
}




void Riscv::handleSupervisorTrap() {

    uint64 volatile scause = r_scause();

    uint64 arguments[5];
    __asm__ volatile ("mv %0, a0" : "=r" (arguments[0]));
    __asm__ volatile ("mv %0, a1" : "=r" (arguments[1]));
    __asm__ volatile ("mv %0, a2" : "=r" (arguments[2]));
    __asm__ volatile ("mv %0, a3" : "=r" (arguments[3]));
    __asm__ volatile ("mv %0, a4" : "=r" (arguments[4]));

   if(scause==0x8000000000000001UL){
       //timer

       __asm __volatile("csrc sip, 0x02");

   }else if(scause==0x08 || scause==0x09){

       if(arguments[0]==MEM_ALLOC){
           size_t volatile sz = arguments[1];
          void * ret= MemoryAllocator::allocateMemory(sz);
           __asm__ volatile ("mv a0, %0" : :"r"(ret));
       }else if(arguments[0]==MEM_FREE){
           void *  volatile addr=(void*)arguments[1];
           arguments[0]= (uint64) MemoryAllocator::freeMemory(addr);
           __asm__ volatile ("mv a0, %0" : :"r"(arguments[0]));
       }
       else if(arguments[0]==A){

           __putc('\n');
       }else if(arguments[0]==THREAD_CREATE){
           //arg[1] tipa _thread**

           _thread* volatile ret_val=_thread::kcreate_thread((void(*)(void*))arguments[2],(void*)arguments[3],(void*)arguments[4]);
           thread_t* volatile temp=(thread_t*)arguments[1];
           *temp=ret_val;
           arguments[0]=(ret_val!=0)?0:-1;
           __asm__ volatile ("mv a1, %0" : :"r"(ret_val));
           __asm__ volatile ("mv a0, %0" : :"r"(arguments[0]));
       }
       else if(arguments[0]==THREAD_EXIT){
            uint64 ret= _thread::kexit();
           __asm__ volatile ("mv a0, %0" : :"r"(ret));
       }
       else if(arguments[0]==THREAD_DISPATCH){
            uint64  volatile sepc, sstatus;
            sepc=r_sepc();
            sstatus=r_sstatus();
            _thread::dispatch();
            w_sstatus(sstatus);
            w_sepc(sepc);

       }
       else if(arguments[0]==GETC){
         uint64 volatile ret=(uint64)__getc();
//         thread_dispatch(); --isto kao dole
           __asm__ volatile ("mv a0, %0" : :"r"(ret));

         //  console_handler();
       }
       else if(arguments[0]==PUTC){
           __putc(arguments[1]);
          // thread_dispatch(); U i ono drugo LOCK U PRINTINGU DODATI { thrad_dispatch();}
         //  console_handler();
       }else if(arguments[0]==SET_U_MODE){
           __asm__ volatile ("csrc sstatus, %[mask]" : : [mask] "r"(1UL << 8));
       }else if(arguments[0]==GET_PID){
           thread_dispatch();
           uint64 volatile ret = (uint64)_thread::running->getId();
           __asm__ volatile ("mv a0, %0" : :"r"(ret));
       }
       else if(arguments[0]==THREAD_JOIN){
           thread_t t = (thread_t)arguments[1];
           while(!t->isFinished())
               thread_dispatch();
       }
       uint64  volatile sepc = r_sepc();
       w_sepc(sepc+4);
       __asm __volatile("csrc sip, 0x02");
   }
 console_handler();
}

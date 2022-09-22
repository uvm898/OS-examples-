//
// Created by os on 9/14/22.
//

#include "../h/syscall_c.h"
#include "../h/codes.h"
#include "../lib/console.h"


void call(uint64 OPCODE){

    __asm__ volatile ("mv a0, %0" : : "r" (OPCODE));
    __asm__ volatile ("ecall");
}

uint64 return_value(){
    uint64 volatile ret_value;
    __asm__ volatile ("mv %0, a0":"=r"(ret_value));
    return  ret_value;
}

void *mem_alloc(size_t size) {
    __asm__ volatile("mv a1, %0": : "r"(size));
    call(MEM_ALLOC);
    uint64 volatile ret;
    __asm__ volatile ("mv %0, a0" : "=r" (ret));
    return (void*)ret;
}

int mem_free(void *addr) {
    __asm__ volatile("mv a1,%0": : "r"(addr));
    call(MEM_FREE);
    uint64 volatile ret;
    __asm__ volatile ("mv %0, a0" : "=r" (ret));
    return (int)return_value();
}
//int thread_create(thread_t* handle, void (*start_routine)(void*), void* arg);
int thread_create(thread_t* handle, void (*start_routine)(void*), void* arg){
    void* stackSpace=mem_alloc(DEFAULT_STACK_SIZE);
    __asm__ volatile("mv a1,%0": : "r"(&handle));
    __asm__ volatile("mv a2,%0": : "r"(start_routine));
    __asm__ volatile("mv a3,%0": : "r"(arg));
    __asm__ volatile("mv a4,%0": : "r"(stackSpace));
    call(THREAD_CREATE);
    uint64 volatile ret;
    _thread *  volatile ret1;
    __asm__ volatile ("mv %0, a0" : "=r" (ret1));
    __asm__ volatile ("mv %0, a0" : "=r" (ret));
    return (int)ret;

}

int thread_exit(){
    call(THREAD_EXIT);
    uint64 volatile ret;
    __asm__ volatile ("mv %0, a0" : "=r" (ret));
    return (int)ret;
}

void thread_join(thread_t t){
    __asm__ volatile("mv a1,%0": : "r"(t));
    call(THREAD_JOIN);
}

void thread_dispatch(){
    call(THREAD_DISPATCH);
}

char getc(){
    call(GETC);
    uint64 volatile ret;
    __asm__ volatile ("mv %0, a0" : "=r" (ret));
    return (char)ret;
}

void putc(char c){
    __asm__ volatile("mv a1,%0": : "r"(c));
    call(PUTC);
}

int a(int val){
    __asm__ volatile("mv a1, %0": : "r"(val));
    call(A);
    return (int)return_value();
}


void set_user_mode() {
    call(SET_U_MODE);
}

int get_pid(){
    call(GET_PID);
    uint64 volatile ret;
    __asm__ volatile ("mv %0, a0" : "=r" (ret));
    return (int)ret;
}

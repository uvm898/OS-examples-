//
// Created by os on 9/14/22.
//

#ifndef PROJEKAT_SYSCALL_C_H
#define PROJEKAT_SYSCALL_C_H



#include"../lib/hw.h"

class _thread;
typedef _thread* thread_t;

class _sem;
typedef _sem* sem_t;

const int EOF = -1;

void * mem_alloc (size_t size);
int mem_free (void* addr);
int thread_create(thread_t* handle, void (*start_routine)(void*), void* arg);
int thread_exit();
void thread_dispatch();
void putc(char c);
char getc();
int a(int val);
void set_user_mode();
int get_pid();
void thread_join(thread_t);



#endif //PROJEKAT_SYSCALL_C_H

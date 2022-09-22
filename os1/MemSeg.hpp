//
// Created by os on 9/14/22.
//

#ifndef PROJEKAT_MEMSEG_HPP
#define PROJEKAT_MEMSEG_HPP

#include "../lib/hw.h"

typedef struct MemSeg{
    MemSeg* next;
    MemSeg* prev;
    size_t size;
}MemSeg;

void put_in_list(MemSeg**, MemSeg*);
void pop_from_list(MemSeg**, MemSeg*);
//added node merge with neighbours
void merge(MemSeg*);

#endif //PROJEKAT_MEMSEG_HPP

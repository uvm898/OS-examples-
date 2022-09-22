//
// Created by os on 9/14/22.
//



#ifndef PROJEKAT_MEMORYALLOCATOR_HPP
#define PROJEKAT_MEMORYALLOCATOR_HPP

#include "../lib/hw.h"
#include "../h/MemSeg.hpp"

class MemoryAllocator{
public:

    static void* allocateMemory(size_t);

    static int freeMemory(void *);

    static void initializeAddressSpace();

private:

    static MemSeg * freeSpace;
    static MemSeg * addressedSpace;
    static uint64 free_space;
    static uint64 addressed_space;

};




#endif //PROJEKAT_MEMORYALLOCATOR_HPP

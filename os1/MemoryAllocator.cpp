//
// Created by os on 9/14/22.
//

#include "../h/MemoryAllocator.hpp"
#include "../lib/hw.h"



MemSeg *MemoryAllocator::freeSpace = 0;//processes deallocated this amount of space
MemSeg *MemoryAllocator::addressedSpace = 0;//processes allocated this amount of space
uint64 MemoryAllocator::free_space = 0;
uint64 MemoryAllocator::addressed_space = 0;


void* MemoryAllocator::allocateMemory(size_t sz) {


    size_t  new_size = (sz % MEM_BLOCK_SIZE == 0) ? sz : (sz / MEM_BLOCK_SIZE + 1) * MEM_BLOCK_SIZE;



    MemSeg *curr = freeSpace;

    while (curr != 0 && curr->size < new_size)curr = curr->next;

    if (curr) {

        if (curr->size == new_size) {
            pop_from_list(&freeSpace, curr);
            put_in_list(&addressedSpace, curr);
            return (void *) ((char *) (curr) + MEM_BLOCK_SIZE);
        }

        if (curr->size > new_size) {
            pop_from_list(&freeSpace, curr);

            if ((curr->size - new_size - MEM_BLOCK_SIZE) > 0) {
                MemSeg *newSeg = (MemSeg *) ((char *) (curr) + MEM_BLOCK_SIZE + new_size);
                newSeg->size = curr->size - new_size - MEM_BLOCK_SIZE;
                newSeg->next = newSeg->prev = nullptr;
                put_in_list(&freeSpace, newSeg);
            }

            curr->size = new_size;
            put_in_list(&addressedSpace, curr);
            return (void *) ((char *) curr + MEM_BLOCK_SIZE);
        }

    }

    return nullptr;

}

int MemoryAllocator::freeMemory(void *addr) {

    if (!addr)return -1;

    MemSeg *curr = (MemSeg *) ((char *) (addr) - MEM_BLOCK_SIZE);



    pop_from_list(&addressedSpace, curr);
    put_in_list(&freeSpace, curr);
    merge(curr);


    return 0;
}

void MemoryAllocator::initializeAddressSpace() {

    freeSpace = (MemSeg *) HEAP_START_ADDR;

    freeSpace->next = nullptr;
    freeSpace->prev = nullptr;
    freeSpace->size = (size_t) ((char *) HEAP_END_ADDR - (char *) HEAP_START_ADDR - MEM_BLOCK_SIZE);

}

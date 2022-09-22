//
// Created by os on 9/14/22.
//

#include "../h/MemSeg.hpp"
#include "../lib/hw.h"

void put_in_list(MemSeg** head, MemSeg* node){

    if(!node)return;

    if(!(*head)){
        *head=node;
        node->next= nullptr;
        node->prev= nullptr;
        return;
    }

    if(node<(*head)){
        node->next=*head;
        (*head)->prev=node;
        node->prev= nullptr;
        *head=node;
        return;
    }

    MemSeg * curr=*head;
    for(;curr->next!= nullptr;curr=curr->next){
        if(node<curr){
            node->next=curr;
            node->prev=curr->prev;

            curr->prev->next=node;
            curr->prev=node;

            return;
        }
    }

    if(node<curr){
        node->next=curr;
        node->prev=curr->prev;

        curr->prev->next=node;
        curr->prev=node;

        return;
    }
    else{
        node->prev=curr;
        curr->next=node;
        node->next= nullptr;
    }
}

void merge(MemSeg* node){
    if(!node)
        return;

    MemSeg * prev = node->prev;
    MemSeg * next= node->next;
    if((prev!= nullptr) && (char*)prev + prev->size == (char*)node){
        prev->size+=node->size;

        if((node->next)!= nullptr && (char*)prev + prev->size == (char*)(node->next)){
            prev->size+=node->next->size;
            prev->next=node->next->next;
            if(prev->next)prev->next->prev=prev;
        }

    }
    else{

        if((next!= nullptr) && (char*)node+node->size==(char*)next){
            node->size+=next->size;
            node->next=next->next;
            if(next->next)next->next->prev=node;
        }
    }
}

void pop_from_list(MemSeg** head, MemSeg* node){
    if(!node || !head || !(*head))
        return;

    MemSeg * listHead = *head;

    if(listHead==node){
        *head=node->next;
        if(node->next)node->next->prev= nullptr;

    }
    else{
        node->prev->next=node->next;
        if(node->next)node->next->prev=node->prev;
    }

    node->prev=node->next= nullptr;
}



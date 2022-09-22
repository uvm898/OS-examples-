//
// Created by os on 9/8/22.
//
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(int argc,char* argv[]){
    int new_algo_policy = atoi(argv[1]);
    change_sched_policy(new_algo_policy);
    exit(0);
}
//
//  bridging.c
//  GraalTest
//
//  Created by Cedric Gatay on 25/10/2019.
//  Copyright © 2019 Code-Troopers. All rights reserved.
//

#include <stdio.h>
#include "graal_isolate.h"
#include "hellofx.hellofx.h"

graal_create_isolate_params_t isolate_params;
graal_isolate_t* isolate;
graal_isolatethread_t* thread;

int azeqsd_graal_method(int a, int b){
    int ret;
    
    ret = graal_create_isolate(&isolate_params, &isolate, &thread);
    if (ret != 0){
        fprintf(stderr, "graal_create_isolate: %d\n", ret);
        return 1;
    }
    int val = SampleCall__add__a3f8314ffff39c86fbca8fceb58f40cf28050ee7(thread, a, b);
    
    ret = graal_tear_down_isolate(thread);
    
    if (ret != 0){
        fprintf(stderr, "graal_tear_down_isolate: %d\n", ret);
        return 1;
    }
    return val;
}

int start_method(){
    int ret;
    
    ret = graal_create_isolate(&isolate_params, &isolate, &thread);
    if (ret != 0){
        fprintf(stderr, "graal_create_isolate: %d\n", ret);
        return 1;
    }
    SampleCall__start__89bf82071c0ea72ae6b9ca8e698e30770700e653(thread);
    
    ret = graal_tear_down_isolate(thread);

    if (ret != 0){
        fprintf(stderr, "graal_tear_down_isolate: %d\n", ret);
        return 1;
    }
    return 0;
}


int stop_method(){
    int ret;
    
    ret = graal_create_isolate(&isolate_params, &isolate, &thread);
    if (ret != 0){
        fprintf(stderr, "graal_create_isolate: %d\n", ret);
        return 1;
    }
    
    SampleCall__stop__f8eb9aba3ae3f98b5d07368204cd00a4879a765d(thread);
    
    ret = graal_tear_down_isolate(thread);

    if (ret != 0){
        fprintf(stderr, "graal_tear_down_isolate: %d\n", ret);
        return 1;
    }
    return 0;
}

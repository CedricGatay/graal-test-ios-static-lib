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
int azeqsd_graal_method(void){
    int ret;
    graal_create_isolate_params_t isolate_params;
    graal_isolate_t* isolate;
    graal_isolatethread_t* thread;
    
    ret = graal_create_isolate(&isolate_params, &isolate, &thread);
    if (ret != 0){
        fprintf(stderr, "graal_create_isolate: %d\n", ret);
        return 1;
    }
    int val = SampleCall__add__a3f8314ffff39c86fbca8fceb58f40cf28050ee7(thread, 1, 20);
    
    ret = graal_tear_down_isolate(thread);
    
    if (ret != 0){
        fprintf(stderr, "graal_tear_down_isolate: %d\n", ret);
        return 1;
    }
    return val;
}

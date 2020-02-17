//
//  bridging.c
//  GraalTest
//
//  Created by Cedric Gatay on 25/10/2019.
//  Copyright © 2019 Code-Troopers. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "bridging.h"

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
    int val = 0 ;//SampleCall__add__a3f8314ffff39c86fbca8fceb58f40cf28050ee7(thread, a, b);
    
    ret = graal_tear_down_isolate(thread);
    
    if (ret != 0){
        fprintf(stderr, "graal_tear_down_isolate: %d\n", ret);
        return 1;
    }
    return val;
}

int bridge_send_message(Message_Send_Struct* message){
    int ret;
    
    if (thread == NULL){
        ret = graal_create_isolate(&isolate_params, &isolate, &thread);
        if (ret != 0){
            fprintf(stderr, "graal_create_isolate: %d\n", ret);
            return 1;
        }
    }
    
    send_message(thread, message);
    //SampleCall__start__89bf82071c0ea72ae6b9ca8e698e30770700e653(&thread);
    
    // tearing down make app crash, as actor are still running but the isolate thread is * dead *
   // ret = graal_tear_down_isolate(thread);

    if (ret != 0){
        fprintf(stderr, "graal_tear_down_isolate: %d\n", ret);
        return 1;
    }
    return 0;
}


int stop_method(){
    int ret;
    
/*    ret = graal_create_isolate(&isolate_params, &isolate, &thread);
    if (ret != 0){
        fprintf(stderr, "graal_create_isolate: %d\n", ret);
        return 1;
    }*/
    
    //SampleCall__stop__f8eb9aba3ae3f98b5d07368204cd00a4879a765d(thread);
    
    // do not tear down too quickly, actors need to die properly.
    // ret = graal_tear_down_isolate(thread);

    if (ret != 0){
        fprintf(stderr, "graal_tear_down_isolate: %d\n", ret);
        return 1;
    }
    return 0;
}

my_cb_t global_callback;


void c_print(void *thread, char* cstr) {
    printf("C: %s\n", cstr);
    if (global_callback != NULL){
        global_callback(cstr);
    }
}

/**
 * Uses the callback provided as an argument.  Creates an APIStruct, prints it out,
 * invokes the callback giving it the APIStruct, and, if checkOnReturn != 0, prints
 * the structure again to see if it has been modified by the callback.
 */
int CUseCallback( my_cb_t cb, int checkOnReturn )
{
    puts( "Entered C code, printing newly created structure:");
    cb( &"youpi" );
    if (checkOnReturn)
    {
        puts( "Now we are back in C code, see if the callback changed the structure...");
    }
    return 0;
}

void run_graal(){
    const char * args[] = {"myapp" };
    run_main(1, args);
}

void run_framework(my_cb_t cb, int argc, char** argv){
    global_callback = cb;
    graal_isolatethread_t *thread = NULL;
    if (graal_create_isolate(NULL, NULL, &thread) != 0) {
      fprintf(stderr, "error on isolate creation or attach\n");
      //return 1;
    }
    
    SampleCall__run__eclair__99f9f442468de56c5a3c1e5a775225280906eb25(thread, argc, argv);
    if (graal_tear_down_isolate(thread) != 0) {
       fprintf(stderr, "shutdown error\n");
      // return 1;
     }
}

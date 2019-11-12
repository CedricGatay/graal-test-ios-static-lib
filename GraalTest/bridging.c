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
#include "hellofx.main.h"

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

int start_method(){
    int ret;
    
    if (thread == NULL){
        ret = graal_create_isolate(&isolate_params, &isolate, &thread);
        if (ret != 0){
            fprintf(stderr, "graal_create_isolate: %d\n", ret);
            return 1;
        }
    }
    //SampleCall__start__89bf82071c0ea72ae6b9ca8e698e30770700e653(thread);
    
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
    global_callback(cstr);
}


day_of_the_week_t day_of_the_week_add(day_of_the_week_t day, int offset) {
    return (day + offset) % (SUNDAY + 1);
}



void fill(my_data* data) {
    int i;
    data->f_primitive = 42;
    for (i = 0; i < DATA_ARRAY_LENGTH; i++) {
      data->f_array[i] = i * 2;
    }

    data->f_cstr = "Hello World";
    data->f_print_function = &c_print;
}

void dump(void *thread, my_data* data) {
    int i;
    printf("**** In C ****\n");
    printf("primitive: %d\n", data->f_primitive);
    printf("length: %d\n", DATA_ARRAY_LENGTH);
    for (i = 0; i < DATA_ARRAY_LENGTH; i++) {
        printf("%d ", data->f_array[i]);
    }
    printf("\n");

    /* Call a function pointer. When set to a Java function, this transparently calls a Java function. */
    data->f_print_function(thread, data->f_cstr);
}

du_t* makeUnion(unsigned char type) {
    du_t* result;
    printf("**** In C ****\n");
    switch(type) {
    case 1:
        result = (du_t*) malloc(sizeof(d1_t));
        result->d1.int_value = 55;
        result->d1.int_pointer = &result->d1.int_value;
        break;
    case 2:
        result = (du_t*) malloc(sizeof(d2_t));
        result->d2.long_value = 5555555555555555L;
        result->d2.long_pointer = &result->d2.long_value;
        break;
    }
    result->h.type = type;
    result->h.name[0] = 'd';
    result->h.name[0] = '0' + type;
    result->h.name[2] = '\0';
    return result;
}

long long getUB1(sudata_t *sudata) {
    return sudata->f_ub1;
}

typedef void (*java_release_data_fn_t)(void *thread, my_data* data);


int two_way(my_cb_t callback) {
  global_callback = callback;
  my_data data;
  java_release_data_fn_t java_release_data;
  day_of_the_week_t day;
  subdata_t *subdata;
  du_t *du1, *du2;
  sudata_t *sudata;
  long long u1, u2, u3, u4;

  graal_isolatethread_t *thread = NULL;
  if (graal_create_isolate(NULL, NULL, &thread) != 0) {
    fprintf(stderr, "error on isolate creation or attach\n");
    return 1;
  }

  fill(&data);

  /* Call a Java function directly. */
  java_entry_point(thread, &data);

  dump(thread, &data);

  /* Call a Java function indirectly by looking it up dynamically. */
#ifndef _WIN64
#ifndef RTLD_DEFAULT
#define RTLD_DEFAULT 0
#endif
  java_release_data = dlsym(RTLD_DEFAULT, "java_release_data");
#else
  java_release_data = (java_release_data_fn_t) GetProcAddress(GetModuleHandleA("libcinterfacetutorial"), "java_release_data");
#endif
  java_release_data(thread, &data);

  /* Enum demo */
  day = SUNDAY;
  java_print_day(thread, day);

  /* Using inheritance in Java to model structural extension, e.g.,
   * header_t is represented by a top @CStruct interface Header, and subdata_t
   * can be represented by a sub-interface of the Header interface.
   */
  subdata = (subdata_t *) malloc(sizeof(subdata_t));
  subdata->header.type = 7;
  subdata->header.name[0] = 's';
  subdata->header.name[1] = '1';
  subdata->header.name[2] = 0;
  subdata->f1 = 0x800000f;
  java_entry_point2(thread, subdata, subdata);
  free(subdata);

  /* Union demo */
  du1 = makeUnion(1);
  du2 = makeUnion(2);

  java_entry_point3(thread, du1, du2, &du1->d1, &du2->d2);

  free(du1);
  free(du2);

  sudata = (sudata_t *) malloc(sizeof(sudata_t));
  sudata->f_ub1 = 0xF0;
  sudata->f_sb1 = 0xF0;
  java_entry_point4(thread, sudata);

  u1 = getUB1_raw_value(thread, sudata);
  u2 = getUB1_masked_raw_value(thread, sudata);
  u3 = getUB1_as_Unsigned_raw_value(thread, sudata);
  u4 = getUB1(sudata);

  printf("getUB1_raw_value              %lld = 0x%llx   (ub1) %d = 0x%x\n", u1, u1, (ub1) u1, (ub1) u1);
  printf("getUB1_masked_raw_value       %lld = 0x%llx   (ub1) %d = 0x%x\n", u2, u2, (ub1) u1, (ub1) u1);
  printf("getUB1_as_Unsigned_raw_value  %lld = 0x%llx   (ub1) %d = 0x%x\n", u3, u3, (ub1) u1, (ub1) u1);
  printf("getUB1                        %lld = 0x%llx   (ub1) %d = 0x%x\n", u4, u4, (ub1) u4, (ub1) u4);

  free(sudata);

  if (graal_tear_down_isolate(thread) != 0) {
    fprintf(stderr, "shutdown error\n");
    return 1;
  }
  return 0;
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

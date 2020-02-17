//
//  bridging.h
//  GraalTest
//
//  Created by Cedric Gatay on 25/10/2019.
//  Copyright © 2019 Code-Troopers. All rights reserved.
//

#ifndef bridging_h
#define bridging_h

#include "eclair.h"

int bridge_send_message(Message_Send_Struct* message);

int azeqsd_graal_method(int a, int b);
int stop_method(void);




/**
 * Function pointer type for the callback.  Callback receives a void
 * pointer, which is then treated as APIStruct * in the callback.
 */
typedef void (*my_cb_t)( void * );

int two_way(my_cb_t);

/**
 * C function using the callback.  It creates an instance of APIStruct, prints
 * it out, and gives it via void pointer to the callback identified by the 1st
 * parameter. If the 2nd parameter is !=0, then the struct is also printed out
 * after the callback returns.
 */
int CUseCallback( my_cb_t, int );

void run_framework(my_cb_t cb, int argc, char** argv);

void run_graal();

#endif /* bridging_h */


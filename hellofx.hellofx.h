#ifndef __HELLOFX_MAIN_H
#define __HELLOFX_MAIN_H

#include "graal_isolate.h"
#include "eclair.h"


#if defined(__cplusplus)
extern "C" {
#endif

int run_main(int paramArgc, char** paramArgv);

void SampleCall__run__eclair__99f9f442468de56c5a3c1e5a775225280906eb25(graal_isolatethread_t*, int, char**);

void send_message(graal_isolatethread_t*, Message_Send_Struct*);

void vmLocatorSymbol(graal_isolatethread_t* thread);

#if defined(__cplusplus)
}
#endif
#endif

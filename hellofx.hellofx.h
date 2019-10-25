#ifndef __HELLOFX_HELLOFX_H
#define __HELLOFX_HELLOFX_H

#include "graal_isolate.h"


#if defined(__cplusplus)
extern "C" {
#endif

int run_main(int paramArgc, char** paramArgv);

int SampleCall__add__a3f8314ffff39c86fbca8fceb58f40cf28050ee7(graal_isolatethread_t*, int, int);

void vmLocatorSymbol(graal_isolatethread_t* thread);

#if defined(__cplusplus)
}
#endif
#endif

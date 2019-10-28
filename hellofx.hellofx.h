#ifndef __HELLOFX_HELLOFX_H
#define __HELLOFX_HELLOFX_H

#include "graal_isolate.h"


#if defined(__cplusplus)
extern "C" {
#endif

int run_main(int paramArgc, char** paramArgv);

int SampleCall__add__a3f8314ffff39c86fbca8fceb58f40cf28050ee7(graal_isolatethread_t*, int, int);

void SampleCall__start__89bf82071c0ea72ae6b9ca8e698e30770700e653(graal_isolatethread_t*);

void SampleCall__stop__f8eb9aba3ae3f98b5d07368204cd00a4879a765d(graal_isolatethread_t*);

void vmLocatorSymbol(graal_isolatethread_t* thread);

#if defined(__cplusplus)
}
#endif
#endif

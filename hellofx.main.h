#ifndef __HELLOFX_MAIN_H
#define __HELLOFX_MAIN_H

#include "graal_isolate.h"
#include "mydata.h"


#if defined(__cplusplus)
extern "C" {
#endif

void CInterfaceTutorial__printingInJava__6b9d765cdfc6b410e0db4c3726442aed1e0d55c1(graal_isolatethread_t*, char*);

void java_entry_point(graal_isolatethread_t*, my_data*);

void java_release_data(graal_isolatethread_t*, my_data*);

void java_print_day(graal_isolatethread_t*, day_of_the_week_t);

void java_entry_point2(graal_isolatethread_t*, subdata_t*, subdata_t*);

void java_entry_point3(graal_isolatethread_t*, du_t*, du_t*, d1_t*, d2_t*);

long long int getUB1_raw_value(graal_isolatethread_t*, sudata_t*);

long long int getUB1_masked_raw_value(graal_isolatethread_t*, sudata_t*);

long long int getUB1_as_Unsigned_raw_value(graal_isolatethread_t*, sudata_t*);

void java_entry_point4(graal_isolatethread_t*, sudata_t*);

int run_main(int paramArgc, char** paramArgv);

int SampleCall__add__a3f8314ffff39c86fbca8fceb58f40cf28050ee7(graal_isolatethread_t*, int, int);

void SampleCall__start__89bf82071c0ea72ae6b9ca8e698e30770700e653(graal_isolatethread_t*);

void SampleCall__stop__f8eb9aba3ae3f98b5d07368204cd00a4879a765d(graal_isolatethread_t*);

int Java_org_pkg_apinative_Native_add(struct JNIEnv_*, void *, long long int, int, int);

void vmLocatorSymbol(graal_isolatethread_t* thread);

#if defined(__cplusplus)
}
#endif
#endif

#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>

#if DEBUG
#define DEBUG_PRINTF(...) printf( __VA_ARGS__)
#else
#define DEBUG_PRINTF(...) {}
#endif

#if TRACE
#define TRACE_PRINTF(...) printf( __VA_ARGS__)
#else
#define TRACE_PRINTF(...) {}
#endif


#endif //DEBUG_H

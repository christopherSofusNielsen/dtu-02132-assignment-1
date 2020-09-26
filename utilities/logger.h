#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <time.h>

#if DEBUG == 1
#define LOG(msg) printf(msg);
#else
#define LOG(msg)
#endif

#if STATE_TIME == 1
#define INIT_STATE_TIME clock_t _t0, _t1
#define START_TIME _t0 = clock()
#define STOP_TIME(msg) \
    _t1 = clock();     \
    printf(msg, ((double)(_t1 - _t0)) / CLOCKS_PER_SEC)
#else
#define INIT_STATE_TIME
#define START_TIME
#define STOP_TIME(msg)
#endif

#endif
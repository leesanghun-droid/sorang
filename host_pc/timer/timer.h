#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <stdio.h>

int createTimer( timer_t *timerID, int sec, int msec );
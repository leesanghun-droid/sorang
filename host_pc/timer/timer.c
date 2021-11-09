#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <stdio.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

int b=0;
void timer_handler(int a)
{
   b++;
   printf("timer%d\n",b);
}

int start_timer()
{   
   struct  sigaction sa;
   struct  itimerval timer;

   memset(&sa,0,sizeof(sa));
   sa.sa_handler = &timer_handler;
   sigaction(SIGVTALRM,&sa,NULL);

   timer.it_value.tv_sec = 0;
   timer.it_value.tv_usec = 250000;

   timer.it_interval.tv_sec = 0;
   timer.it_interval.tv_usec = 250000;

   setitimer(ITIMER_VIRTUAL,&timer,NULL);
}

   

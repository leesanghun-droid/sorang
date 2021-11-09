#include "../include/main.h"
#include <sys/poll.h>
#include "uart.h"
#include "tcpip.h"
#include "../lidar/lidar_law.h"
#include "../display/display.h"

double d_gyro=0;

   int    fd[6];
   struct pollfd     poll_events[6];
   int    poll_state;

int poll_init()
{
      fd[2] = 0;

      if(fd[2]==-1)
         return -1;

   // poll 사용을 위한 준비   
   poll_events[2].fd        = fd[2];
   poll_events[2].events    = POLLIN;          // 수신된 자료가 있는지, 에러가 있는지
   poll_events[2].revents   = 0;

   return 1;
}
#define base_packet 11
#define lidar_packet 22
int64_t ex_lidar_cnt =0;
int poll_run()
{

   while(1)
   {
      poll_state = poll(                                // poll()을 호출하여 event 발생 여부 확인     
                         (struct pollfd*)&poll_events,  // event 등록 변수
                                                    3,  // 체크할 pollfd 개수
                                                 1000  // time out // -1 : inpinity stay
                       );

      if (poll_state > 0)                             // 발생한 event 가 있음
      {     
         if ( poll_events[2].revents & POLLIN)  
         {


         }
      }
      else if(poll_state < 0)
      {
          printf("Critial Error!\n");
          return -1;
      }
      else if(poll_state == 0)
      {
          //printf("wait...\n");
      }

      return 0;
   }
}
void fd_free()
{
      printf("close fd[2]\n");
      close(fd[2]);
}
void write_base_uart(char* data,int length )
{
    write( fd[2], data, length); 
}
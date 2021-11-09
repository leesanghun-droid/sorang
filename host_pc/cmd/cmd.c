#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../com/poll.h"

/*
void send_emc_test(  char elevator, 
                     char lidar,
                     char fan,
                     char left_brush,
                     char right_brush,
                     char main_brush,
                     char left_wheel,
                     char right_wheel,
                     char pump_motor
                  )
*/
/*
void command1(  float angle,
                char elevator, 
                char lidar,
                char fan,
                char left_brush,
                char right_brush,
                char main_brush,
                char left_wheel,
                char right_wheel,
                char pump_motor
            )
{
    char temp[50]={0};
    char header[5]="CMD1";
    int point = 0;
    memcpy(temp+point,header,4);
    point+=4;
    memcpy(temp+point,&angle,4);
    point+=4;
    memcpy(temp+point,&elevator,1);
    point+=1;
    memcpy(temp+point,&lidar,1);
    point+=1;
    memcpy(temp+point,&fan,1);
    point+=1;
    memcpy(temp+point,&left_brush,1);
    point+=1;
    memcpy(temp+point,&right_brush,1);
    point+=1;
    memcpy(temp+point,&main_brush,1);
    point+=1;
    memcpy(temp+point,&left_wheel,1);
    point+=1;
    memcpy(temp+point,&right_wheel,1);
    point+=1;
    memcpy(temp+point,&pump_motor,1);
    point+=1;
    write_base_uart(temp,point);
    //printf("cmd1_point: %d\r\n",point);
}*/
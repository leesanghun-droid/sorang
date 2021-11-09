#include "../include/main.h"
#include "../display/display.h"
char lidar_power;


double ex_start_angle=0;
double lidar_array[4096][2]={0};
int32_t lidar_array_cnt=0;
double ex_data=0;

double angle[4096];
double distance[4096];
int32_t angle_position = 0;

void cal_raw_map(unsigned char * input)
{

double raw_start_angle = ((double)input[7])+((double)input[6])/256;
double raw_end_angle = ((double)input[33])+((double)input[32])/256;

double start_angle = (raw_start_angle-160)*4;
double end_angle = (raw_end_angle-160)*4;

//printf("%0.2f,%0.2f\n",start_angle,end_angle);


double between_angle = 0;

   if(end_angle<start_angle)
      between_angle = (end_angle+360 - start_angle)/11;
   else
      between_angle = (end_angle - start_angle)/11;

   for(int i=0;i<12;i++)
   {
      double distance_temp = ((double)input[9+i*2])*256+((double)input[8+i*2]);

      if(distance_temp==32768)
      distance_temp=0;

      double temp = start_angle+between_angle*i;
         if(temp>360)
            temp=temp-360;

      if(ex_data>temp)
      {
       angle_position=lidar_array_cnt;
       lidar_array_cnt=0;


       //display(angle,distance,angle_position);
      printf("angle_position:%d,\n",angle_position);

      }
      angle[lidar_array_cnt]=temp;
      distance[lidar_array_cnt]=distance_temp;
      //printf("%d,%0.2f,%d,%d\n",lidar_array_cnt,angle[lidar_array_cnt],input[8+i*2],input[9+i*2]);
      lidar_array_cnt++;

      ex_data=temp;
   }
ex_start_angle=start_angle;

}
#include "include/main.h"
#include "com/uart.h"
#include "com/poll.h"
#include "com/tcpip.h"
#include "argument/argu.h"
#include "teminel_key/esc_key.h"
#include "timer/timer.h"
#include "display/display.h"
#include "cmd/cmd.h"

//#include <chrono>
//#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include <gtk/gtk.h>
#include <pthread.h>

#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include <fcntl.h>
#include <linux/input.h>

#include <termios.h> // B115200, CS8 등 상수 정의
#include <fcntl.h>   // O_RDWR , O_NOCTTY 등의 상수 정의
#include <sys/poll.h>

//using namespace std::chrono;
//using namespace std;
unsigned char elevator;
unsigned char lidar;
unsigned char fan=0;;
unsigned char left_brush;
unsigned char right_brush;
unsigned char main_brush;
char left_wheel;
char right_wheel;
unsigned char pump_motor;
unsigned char wheel = 255;
int rotate = 0;
double gyro_default = 0;

/*
void motor_cmd()
{
   command1(0,
            elevator,
            lidar,
            fan,
            left_brush,
            right_brush,
            main_brush,
            left_wheel,
            right_wheel,
            pump_motor);
}
*/
G_MODULE_EXPORT void on_gyro_default_value_changed(GtkRange *range, gdouble value)
{
   gyro_default = gtk_range_get_value(range);
   //printf("rotate: %d\r\n",rotate);
}

G_MODULE_EXPORT void on_lidar_rotate_value_changed(GtkRange *range, gdouble value)
{
   rotate = gtk_range_get_value(range);
   //printf("rotate: %d\r\n",rotate);
}

G_MODULE_EXPORT void on_fan_value_changed(GtkRange *range, gdouble value)
{
   fan = gtk_range_get_value(range);
   //printf("fan: %d\r\n",fan);
   //motor_cmd();
}
G_MODULE_EXPORT void on_wheel_value_changed(GtkRange *range, gdouble value)
{
   wheel = gtk_range_get_value(range);
   //printf("wheel: %d\r\n",wheel);
   //motor_cmd();
}

G_MODULE_EXPORT void on_left_brush_toggled(GtkButton *button, gpointer user_data)
{
   //printf("left_brush_toggle\r\n");
   left_brush = !left_brush;
   //motor_cmd();
}
G_MODULE_EXPORT void on_right_brush_toggled(GtkButton *button, gpointer user_data)
{
   //printf("left_brush_toggle\r\n");
   right_brush = !right_brush;
   //motor_cmd();
}
G_MODULE_EXPORT void on_main_brush_toggled(GtkButton *button, gpointer user_data)
{
   //printf("left_brush_toggle\r\n");
   main_brush = !main_brush;
   //motor_cmd();
}
G_MODULE_EXPORT void on_elevator_toggled(GtkButton *button, gpointer user_data)
{
   //printf("left_brush_toggle\r\n");
   elevator = !elevator;
   //motor_cmd();
}
G_MODULE_EXPORT void on_LIDAR_toggled(GtkButton *button, gpointer user_data)
{
   //printf("left_brush_toggle\r\n");
   lidar = !lidar;
   //motor_cmd();
}
G_MODULE_EXPORT void on_water_pump_toggled(GtkButton *button, gpointer user_data)
{
   //printf("left_brush_toggle\r\n");
   pump_motor = !pump_motor;
   //motor_cmd();
}

G_MODULE_EXPORT void on_button_up_pressed(GtkButton *button, gpointer user_data)
{
   left_wheel = (char)(wheel / 2);
   right_wheel = (char)(wheel / 2);
   //motor_cmd();
}
G_MODULE_EXPORT void on_button_up_released(GtkButton *button, gpointer user_data)
{
   left_wheel = 0;
   right_wheel = 0;
   //motor_cmd();
}

G_MODULE_EXPORT void on_button_down_pressed(GtkButton *button, gpointer user_data)
{
   left_wheel = -(char)(wheel / 2);
   right_wheel = -(char)(wheel / 2);
   //motor_cmd();
}
G_MODULE_EXPORT void on_button_down_released(GtkButton *button, gpointer user_data)
{
   left_wheel = 0;
   right_wheel = 0;
   //motor_cmd();
}
G_MODULE_EXPORT void on_button_left_pressed(GtkButton *button, gpointer user_data)
{
   left_wheel = -(char)(wheel / 2);
   right_wheel = (char)(wheel / 2);
   //motor_cmd();
}
G_MODULE_EXPORT void on_button_left_released(GtkButton *button, gpointer user_data)
{
   left_wheel = 0;
   right_wheel = 0;
   //motor_cmd();
}
G_MODULE_EXPORT void on_button_right_pressed(GtkButton *button, gpointer user_data)
{
   left_wheel = (char)(wheel / 2);
   right_wheel = -(char)(wheel / 2);
   //motor_cmd();
}
G_MODULE_EXPORT void on_button_right_released(GtkButton *button, gpointer user_data)
{
   left_wheel = 0;
   right_wheel = 0;
   //motor_cmd();
}

void *thread_routine(void *arg)
{
   pthread_t tid;
   tid = pthread_self();

   int argc = 0;
   ;
   char **argv;

   GtkBuilder *builder;
   GtkWidget *window;
   gtk_init(&argc, &argv);

   builder = gtk_builder_new();
   gtk_builder_add_from_file(builder, "test.glade", NULL);
   window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
   gtk_builder_connect_signals(builder, NULL);

   g_object_unref(builder);
   gtk_widget_show(window);
   gtk_window_move((GtkWindow*)window,350+250,50);
   gtk_main();
}

static const char *uart_device = "/dev/ttyACM0";



int uart_init(const char *device)
{
   int fd;

   struct termios newtio;

   fd = open(device, O_RDWR | O_NOCTTY); // 디바이스를 open 한다.
   if (0 > fd)
   {
      printf("%s  open error\n", device);
   }
   else
   {
      printf("%s  open\n", device);
   }

   // 시리얼 포트 통신 환경 설정
   memset(&newtio, 0, sizeof(newtio));
   newtio.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
   newtio.c_oflag = 0;
   newtio.c_lflag = 0;
   newtio.c_cc[VTIME] = 0;
   newtio.c_cc[VMIN] = 1;

   tcflush(fd, TCIFLUSH);
   tcsetattr(fd, TCSANOW, &newtio);
   fcntl(fd, F_SETFL, FNDELAY);

   return fd;
}

extern char lidar_power;
extern char motor_speed_R;
extern char motor_speed_L;
extern UART_STATE UART;

uint16_t ch[7][2]={0};


int cmd_mode = 0;
void uart_reader(unsigned char * input,int count)
{
   for(int i=0; i< count; i++)
   {
      unsigned char data = input[i];
      switch(cmd_mode)
      {
         case 0:
            if(data == 'c')
            {
               cmd_mode++;
            }
         break;
         case 1:
            if(data == 'm')
            {
               cmd_mode++;
            }
         break;
         case 2:
            if(data == 'd')
            {
               cmd_mode++;
            }
         break;

         case 3:
         ch[0][0]=data;
         cmd_mode++;
         break;
         case 4:
         ch[0][1]=(uint16_t)data *256;
         cmd_mode++;
         break;
         case 5:
         ch[0][1]=ch[0][1] + (uint16_t)data;
         cmd_mode++;
         break;


         case 6:
         ch[1][0]=data;
         cmd_mode++;
         break;
         case 7:
         ch[1][1]=(uint16_t)data *256;
         cmd_mode++;
         break;
         case 8:
         ch[1][1]=ch[1][1] + (uint16_t)data;
         cmd_mode++;
         break;


         case 9:
         ch[2][0]=data;
         cmd_mode++;
         break;
         case 10:
         ch[2][1]=(uint16_t)data *256;
         cmd_mode++;
         break;
         case 11:
         ch[2][1]=ch[2][1] + (uint16_t)data;
         cmd_mode++;
         break;


         case 12:
         ch[3][0]=data;
         cmd_mode++;
         break;
         case 13:
         ch[3][1]=(uint16_t)data *256;
         cmd_mode++;
         break;
         case 14:
         ch[3][1]=ch[3][1] + (uint16_t)data;
         cmd_mode++;
         break;


         case 15:
         ch[4][0]=data;
         cmd_mode++;
         break;
         case 16:
         ch[4][1]=(uint16_t)data *256;
         cmd_mode++;
         break;
         case 17:
         ch[4][1]=ch[4][1] + (uint16_t)data;
         cmd_mode++;
         break;


         case 18:
         ch[5][0]=data;
         cmd_mode++;
         break;
         case 19:
         ch[5][1]=(uint16_t)data *256;
         cmd_mode++;
         break;
         case 20:
         ch[5][1]=ch[5][1] + (uint16_t)data;
         cmd_mode++;
         break;


         case 21:
         ch[6][0]=data;
         cmd_mode++;
         break;
         case 22:
         ch[6][1]=(uint16_t)data *256;
         cmd_mode++;
         break;
         case 23:
         ch[6][1]=ch[6][1] + (uint16_t)data;
         cmd_mode=0;
         break;
         
      }
   }
}


int main(int argc, char **argv)
{
   pthread_t thread;
   pthread_create(&thread, NULL, thread_routine, NULL);

   display_init();

   int uart_fd=uart_init(uart_device);
   struct pollfd poll_events;
   int poll_state;

   poll_events.fd        = uart_fd;
   poll_events.events    = POLLIN | POLLERR;          // 수신된 자료가 있는지, 에러가 있는지
   poll_events.revents   = 0;

   while (1)
   {
      poll_state = poll((struct pollfd*)&poll_events,1,-1);

      if (poll_state > 0)                             // 발생한 event 가 있음
      {
         if ( poll_events.revents & POLLIN)            // uart2 lidar 수신
         {
            int uart2_cnt = read( uart_fd, buf_uart2, 1000);
            uart_reader(buf_uart2,uart2_cnt);

            draw(ch);
         }
         if ( poll_events.revents & POLLERR)      // event 가 에러?
         {
            printf( "uart2 에 에러가 발생, 프로그램 종료");
            return -1;
         }
      }
            
      else if(poll_state < 0)
      {
          printf("Critial Error!\n");
          return -1;
      }
      else if(poll_state == 0)
      {
          printf("wait...\n");
      }    
      //draw();
      //sleep(1);
   }
   fd_free();
   tcpip_free();
   return 0;
}


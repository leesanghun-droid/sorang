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

extern char lidar_power;
extern char motor_speed_R;
extern char motor_speed_L;
extern UART_STATE UART;

int main(int argc, char **argv)
{
   pthread_t thread;
   pthread_create(&thread, NULL, thread_routine, NULL);

   display_init();

   while (1)
   {
      draw();
      sleep(1);
   }
   fd_free();
   tcpip_free();
   return 0;
}
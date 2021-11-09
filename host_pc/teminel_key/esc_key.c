#include <termios.h>  
#include <unistd.h>
#include <stdio.h>
#include <linux/input.h>

#define EXIT_KEY input_key==27
#define LIDAR_KEY input_key==76 || input_key==108 
#define UP_KEY input_key==87 || input_key==119 
#define DOWN_KEY input_key==83 || input_key==115 
#define LEFT_KEY input_key==65 || input_key==97 
#define RIGHT_KEY input_key==68 || input_key==100 


struct termios org_term;
struct termios new_term;
char input_key = 0;

void esc_key_init()
{
    tcgetattr(STDIN_FILENO, &org_term);
    new_term=org_term;

    new_term.c_lflag &= ~(ECHO | ICANON);
    new_term.c_cc[VMIN]=0;
    new_term.c_cc[VTIME]=0;

    tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
}
extern char lidar_power;
extern char motor_speed_R;
extern char motor_speed_L;
int esc_key_check()
{
    char dummy;
    if(read(STDIN_FILENO, &input_key,1) !=1)
        input_key =0;
    else
    {
        if(EXIT_KEY)
        {
            printf("press ESC\n");
            tcsetattr(STDIN_FILENO, TCSANOW, &org_term);
            return 1;
        }
        else if(LIDAR_KEY)
        {
            lidar_power=!lidar_power;
            if(lidar_power)
            printf("lidar_power ON\n");
            else
            printf("lidar_power OFF\n");
            while(read(STDIN_FILENO, &dummy,1)==1);
        }else if(UP_KEY)
        {
            motor_speed_R=100;
            motor_speed_L=100;
            while(read(STDIN_FILENO, &dummy,1)==1);
        }else if(DOWN_KEY)
        {
            motor_speed_R=-100;
            motor_speed_L=-100;
            while(read(STDIN_FILENO, &dummy,1)==1);
        }else if(LEFT_KEY)
        {
            motor_speed_R=+100;
            motor_speed_L=-100;
            while(read(STDIN_FILENO, &dummy,1)==1);
        }else if(RIGHT_KEY)
        {
            motor_speed_R=-100;
            motor_speed_L=+100;
            while(read(STDIN_FILENO, &dummy,1)==1);
        }else
        {
            motor_speed_R=0;
            motor_speed_L=0;
            while(read(STDIN_FILENO, &dummy,1)==1);
        }
    }

    return 0;
}
#include "../include/main.h"
#include "uart.h"
#include "poll.h"
#include <termios.h>                   // B115200, CS8 등 상수 정의
#include <fcntl.h>                     // O_RDWR , O_NOCTTY 등의 상수 정의
#include "../lidar/lidar_law.h"

UART_STATE UART;

#define header_1   0
#define header_2   1
#define length     2
#define read_data  3

int32_t R_encoder=0;
int32_t L_encoder=0;



int uart_init(const char* device)
{
   int fd;

   struct termios    newtio;

   fd = open(device, O_RDWR | O_NOCTTY );        // 디바이스를 open 한다.
   if ( 0 > fd)
   {        
      printf("%s  open error\n",device);
   }else{
   printf("%s  open\n",device);
   }

   // 시리얼 포트 통신 환경 설정
   memset(&newtio, 0, sizeof(newtio) );
   newtio.c_cflag       = B115200 | CS8 | CLOCAL | CREAD;
   newtio.c_oflag       = 0;
   newtio.c_lflag       = 0;
   newtio.c_cc[VTIME]   = 0;
   newtio.c_cc[VMIN]    = 1;

   tcflush(fd, TCIFLUSH);
   tcsetattr(fd, TCSANOW, &newtio);
   fcntl(fd, F_SETFL, FNDELAY); 

   return fd;
}


void send_speed(char right_speed,char left_speed)
{
   char data[5]={0};
   data[0] = 0xAA;
   data[1] = 0x55;
   data[2] = 0x05;
   data[3] = right_speed;
   data[4] = left_speed;
   write_base_uart(data,5);
}

void encoder_read(unsigned char * input)
{
   R_encoder= ((int32_t)input[6])*65536 + ((int32_t)input[7])*256 + (int32_t)input[8] - 8388608;
   L_encoder= ((int32_t)input[9])*65536 + ((int32_t)input[10])*256 + (int32_t)input[11] - 8388608;
}
   
int32_t gyro_law=0;
double d_gyro=0;
void gyro_read(unsigned char * input)
{
   gyro_law= ((int32_t)input[3])*65536 + ((int32_t)input[4])*256 + (int32_t)input[5];
   //printf("gyro: %d\n",gyro_law);

   if(gyro_law>8388608)
   gyro_law= gyro_law-16777216;

   d_gyro = (double)gyro_law/25600;
   //printf("gyro: %0.2f\n",d_gyro);
}

void print_buf(unsigned char * input,int count)
{
printf("////////////////////////////////////////////////////////////\n");
  for(int i=0;i<count;i++)
  {
      
      printf("0x%02x\n",input[i]);
      
  }
  printf("////////////////////////////////////////////////////////////\n");
}

unsigned short CRC_check(unsigned char* input,int len)
{


	unsigned int i,j;

	unsigned short crc = 0;

 

	for(i=0;i<len;i++)

	{

		crc=crc^((*input)<<8);

		input++;

		for(j=0;j<8;j++)

		{

			if(crc & 0x8000)

			{

				crc = (crc<<1)^0x1021;

			}else{

				crc=crc<<1;

			}

		}

	}

	return crc;
}
int32_t comunicate_cnt=0;
int32_t comunicate_faild_cnt=0;

int cmd_mode_uart1=0;
int data_cnt=0;
int crc_cnt=0;
int64_t ex_time;
void uart1_reader(unsigned char * input,int count)
{
   for(int i=0; i< count; i++)
   {
      unsigned char data = input[i];

      switch(cmd_mode_uart1)
      {
         case header_1:
            if(data == 0xAA)
            {
               cmd_mode_uart1=header_2;
               cmd_uart1[0]=data;
               //printf("ssssssss_uart1_header1_sucess : 0x%02x\n",data);
            }
            else
            {
               UART.uart1_faild++;
               comunicate_faild_cnt++;
               cmd_mode_uart1 = header_1;
               //printf("ffffffff_uart1_header1_faild : 0x%02x\n",data);
            }
         break;
         case header_2:
            if(data == 0x55)
            {
               cmd_mode_uart1=length;
               cmd_uart1[1]=data;
               //printf("ssssssss_uart1_header2_sucess : 0x%02x\n",data);
            }
            else
            {
               UART.uart1_faild++;
               comunicate_faild_cnt++;
               cmd_mode_uart1 = header_1;
               //printf("ffffffff_uart1_header2_faild : 0x%02x\n",data);
            }  
         break;
         case length:
            cmd_uart1[2]=data;
            cmd_mode_uart1=read_data;
            //printf("ssssssss_uart1_length_sucess : 0x%02x\n",data);
            data_cnt=0;
         break;
         case read_data:
         cmd_uart1[3+data_cnt]=data;
         data_cnt++;
         //printf("ssssssss_uart1_read_data_sucess : 0x%02x , data_cnt : %d\n",data,data_cnt);
         //printf("data_cnt :%d \n",data_cnt);
         if(data_cnt>=(cmd_uart1[2]+2))
         {
            cmd_mode_uart1 = header_1;
            comunicate_cnt++;
            //printf("read_done :\n");
            /*
            for(int i=0; i<(cmd[2]+5);i++)
            {
               printf("0x%02x,\n",cmd[i]);
            }
            */
            unsigned short crc=CRC_check(cmd_uart1,cmd_uart1[2]+3);
            unsigned short recive_crc = cmd_uart1[cmd_uart1[2]+3]*256 + cmd_uart1[cmd_uart1[2]+4];

            double com_error = (double)(comunicate_cnt-comunicate_faild_cnt)*100/(double)comunicate_cnt;
            //printf("CRC_CHECK : 0x%04x, 0x%04x\n",crc,recive_crc);
            if(crc==recive_crc)
            {
               gyro_read(cmd_uart1);
               encoder_read(cmd_uart1);
               //printf("ssssssss_uart1_sucess, uart1_faild : %d \n",uart1_faild);
               UART.uart1_sucess++;
            }
            else
            {
               UART.uart1_faild++;
               //printf("ffffffff_uart1_crc_faild, data_cnt : %d\n",data_cnt);
               //printf("FAILD_CRC_CHECK %d/%d  %0.2f \n",comunicate_cnt-comunicate_faild_cnt,comunicate_cnt,com_error);
               comunicate_faild_cnt++;
            }
         }
         break;
         default:
         UART.uart1_faild++;
            //printf("ffffffff_uart1_default\n");
      }
   }

}

int cmd_mode_uart2=0;
int64_t ex_time2;
int uart2_data_cnt=0;
int buf_cnt=0;
void uart2_reader(unsigned char * input,int count)
{
   for(int i=0; i< count; i++)
   {
      unsigned char data = input[i];
      switch(cmd_mode_uart2)
      {
         case header_1:
            if(data == 0x55)
            {
               cmd_mode_uart2=header_2;
               cmd_uart2[0]=data;
               //printf("ssssssss_uart2_header1_sucess : 0x%02x\n",data);
            }
            else
            {
               cmd_mode_uart2 = header_1;
               UART.uart2_faild++;
               //printf("ffffffff_uart2_header1_faild : 0x%02x\n",data);
            }
         break;
         case header_2:
            if(data == 0xAA)
            {
               cmd_mode_uart2=length;
               cmd_uart2[1]=data;
               //printf("ssssssss_uart2_header2_sucess : 0x%02x\n",data);
            }
            else
            {
               cmd_mode_uart2 = header_1;
               UART.uart2_faild++;
               //printf("ffffffff_uart2_header2_faild : 0x%02x\n",data);
            }
               uart2_data_cnt=34;
               buf_cnt=2;
         break;
         case length:
 
            cmd_uart2[buf_cnt]=data;
            buf_cnt++;
            uart2_data_cnt--;
            //printf("ssssssss_uart2_header1_sucess : 0x%02x\n",data);

            if(uart2_data_cnt==0)
            {
               //printf("ssssssss_uart2_sucess, uart2_faild : %d \n",uart2_faild);
               UART.uart2_sucess++;
               cal_raw_map(cmd_uart2);
               cmd_mode_uart2=header_1;
               buf_cnt=0;
            }

         break;
      }
   }

} 
 

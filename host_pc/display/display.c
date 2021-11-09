#define display_x11 True

#define display_lidar True
#define display_control True


#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/X.h>
#include <X11/Xutil.h>
#include <math.h>

#define PI 3.1415926
#define size 0.2
#define width  1000
#define heigth  1000
#define x_center 500
#define y_center 500
static double rotate_angle =310;
int32_t byte_array[heigth][width]={0xFFFFFF};

 Display *disp ;
 Window   win, root , w1 ;
 GC gc;
 XImage *image;
 XGCValues gr_values;
 XFontStruct *fontinfo;
 XColor color, dummy;
 int screen;

 void display_init()
 {

if(display_x11==True)
{
  disp = XOpenDisplay(NULL) ;
  screen = DefaultScreen(disp);
  root = XDefaultRootWindow (disp);
  win = XCreateSimpleWindow ( disp, root, 0, 0, width+500, heigth,
                              2, BlackPixel (disp,0), WhitePixel(disp,0) );

  XMapWindow (disp, win);
  XFlush(disp);

  image = XCreateImage(disp, DefaultVisual(disp, 0), 24, ZPixmap,0, 0, width, heigth, 32, 0);
  gc = XCreateGC(disp, win, 0, NULL);
  image->data = (char *)malloc(image->bytes_per_line * heigth * 4);

  XInitImage(image);

  fontinfo = XLoadQueryFont(disp,"12x24");

  XAllocNamedColor(disp, DefaultColormap(disp, screen),"yellow",
                  &color,&dummy);

  gr_values.font = fontinfo->fid;
  gr_values.foreground = color.pixel;


  gc=XCreateGC(disp,win,GCFont+GCForeground, &gr_values);
}
}

void draw(u_int16_t arr[][2])
{
  /////////////////  draw_origin CIRCLE START //////////////////////

  printf("%d\r\n",arr[0][1]);
  printf("%d\r\n",arr[1][1]);
  printf("%d\r\n",arr[2][1]);
  printf("%d\r\n",arr[3][1]);
  printf("%d\r\n",arr[4][1]);
  printf("%d\r\n",arr[5][1]);
  printf("%d\r\n",arr[6][1]);

  double d_ch[7][2]={0};

  for(int i=0;i<7;i++)
  {
    d_ch[i][0]=(double)arr[i][0];
    d_ch[i][1]=(double)arr[i][1]*0.02929;
  }

  printf("%0.3f\r\n",d_ch[0][1]);
  printf("%0.3f\r\n",d_ch[1][1]);
  printf("%0.3f\r\n",d_ch[2][1]);
  printf("%0.3f\r\n",d_ch[3][1]);
  printf("%0.3f\r\n",d_ch[4][1]);
  printf("%0.3f\r\n",d_ch[5][1]);
  printf("%0.3f\r\n",d_ch[6][1]);



      for(int s =0; s<500; s+=83)
      for(double i=0; i<360;i=i+0.001)
          {
            float x_circle = cos(((i)*PI)/180)*(s);
            float y_circle = -sin(((i)*PI)/180)*(s);
            int x_circle_pos = (int)x_circle+x_center;
            int y_circle_pos = (int)y_circle+y_center;

            if(x_circle_pos>width)
              x_circle_pos=width;
            if(x_circle_pos<0)
              x_circle_pos=0;
            if(y_circle_pos>heigth)
              y_circle_pos=heigth;
            if(y_circle_pos<0)
              y_circle_pos=0;

            byte_array[x_circle_pos-2][y_circle_pos-2]=0x00FF00; 
            byte_array[x_circle_pos-1][y_circle_pos-1]=0x00FF00; 
            byte_array[x_circle_pos][y_circle_pos]=0x00FF00; 
          }


  float ch1_y = -sin(((90)*PI)/180)*(d_ch[0][1]/5)*83+y_center;
  float ch1_x = x_center;

  if(ch1_y>980)
  ch1_y=980;
  if(ch1_x>980)
  ch1_x=980;

  float ch2_y = -sin(((30)*PI)/180)*(d_ch[1][1]/5)*83+y_center;
  float ch2_x = -cos(((30)*PI)/180)*(d_ch[1][1]/5)*83+x_center;

    if(ch2_y>980)
  ch2_y=980;
  if(ch2_x>980)
  ch2_x=980;


  float ch3_y = sin(((30)*PI)/180)*(d_ch[2][1]/5)*83+y_center;
  float ch3_x = -cos(((30)*PI)/180)*(d_ch[2][1]/5)*83+x_center;


  if(ch3_y>980)
  ch3_y=980;
  if(ch3_x>980)
  ch3_x=980;


  float ch4_y = sin(((90)*PI)/180)*(d_ch[4][1]/5)*83+y_center;
  float ch4_x = x_center;


  if(ch4_y>980)
  ch4_y=980;
  if(ch4_x>980)
  ch4_x=980;


  float ch5_y = -sin(((30)*PI)/180)*(d_ch[4][1]/5)*83+y_center;
  float ch5_x = cos(((30)*PI)/180)*(d_ch[4][1]/5)*83+x_center;
  
  if(ch5_y>980)
  ch5_y=980;
  if(ch5_x>980)
  ch5_x=980;


  float ch6_y = sin(((30)*PI)/180)*(d_ch[5][1]/5)*83+y_center;
  float ch6_x = cos(((30)*PI)/180)*(d_ch[5][1]/5)*83+x_center;

  if(ch6_y>980)
  ch6_y=980;
  if(ch6_x>980)
  ch6_x=980;



  for(int i=0;i<20;i++)
  for(int j=0;j<20;j++)
  {
    byte_array[(int)ch1_y+j][(int)ch1_x+i]=0xFF0000;
    byte_array[(int)ch2_y+j][(int)ch2_x+i]=0xFF0000;
    byte_array[(int)ch3_y+j][(int)ch3_x+i]=0xFF0000;
    byte_array[(int)ch4_y+j][(int)ch4_x+i]=0xFF0000;
    byte_array[(int)ch5_y+j][(int)ch5_x+i]=0xFF0000;
    byte_array[(int)ch6_y+j][(int)ch6_x+i]=0xF0000F;
  }



/////////////////  draw_origin CIRCLE END //////////////////////


    // PutPixel
    for(int y=0;y<heigth;y++)
         for(int x=0;x<width;x++)
         {
                  XPutPixel(image, x, y,byte_array[y][x]);
         }


    // byte_array init white
         for(int y=0; y<heigth;y++)
         for(int x=0; x<width;x++)
          {
            byte_array[y][x]=0x000000; //b + g*256 + r*65536
          }
        
        XPutImage(disp, win, gc, image, 0, 0, 0, 0, width, heigth);
        XDrawString(disp, win, gc,500, 0, "35M", 4);
        XDrawString(disp, win, gc,500, 73, "30M", 4);
        XDrawString(disp, win, gc,500, 158, "25M", 4);
        XDrawString(disp, win, gc,500, 241, "15M", 4);
        XDrawString(disp, win, gc,500, 324, "10M", 4);
        XDrawString(disp, win, gc,500, 407, "5M", 4);
        XFlush(disp);
}
/*
void lidar_draw(float *angle,float *distance,int length)
{

//printf("angle[0]: %5.2f\r\n",angle[0]);
//printf("d_gyro: %5.2f,gyro_default: %5.2f\r\n",d_gyro,gyro_default);
double robot_angle_offset = gyro_default-d_gyro;
//printf("robot_angle_offset: %5.2f\r\n",robot_angle_offset);

      for(int i=0; i<length;i++)
          {
            float offset_angle = angle[i]+rotate;
            double x_pos = -cos(((offset_angle-robot_angle_offset)*PI)/180)*distance[i]*size;
            double y_pos = -sin(((offset_angle-robot_angle_offset)*PI)/180)*distance[i]*size;

            int codi_x = x_pos/1+x_center;
            int codi_y = y_pos/1+y_center;

            codi_y=codi_y-2;
            codi_x=codi_x-2;

            if(codi_x>(width-10) || codi_x<10 || codi_y>(heigth-10) || codi_y<10)
            {
               codi_x=0;
               codi_y=0;
            }

            for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
            {
               byte_array[codi_y+j][codi_x+i]=0xFF0000;
            }
          }

/////////////////////  lidar quad  //////////////////////

for(int x=0; x<width; x++)
{
  for(int i=0;i<3;i++)
  {
    byte_array[i][x]=0x000000;
    byte_array[496+i][x]=0x000000;
  }
}
for(int y=0; y<heigth; y++)
{
  for(int i=0;i<3;i++)
  {
    byte_array[y][i]=0x000000;
    byte_array[y][496+i]=0x000000;
  }
}

/////////////////////  lidar quad end  //////////////////

XFlush(disp); i<360;i=i+0.1)
          {
            float x_circle = cos(((i+rotate_angle)*PI)/180)*(40)*size;
            float y_circle = -sin(((i+rotate_angle)*PI)/180)*(40)*size;
            int x_circle_pos = x_circle/1+x_center;
            int y_circle_pos = y_circle/1+y_center;
            byte_array[y_circle_pos][x_circle_pos]=0x0000FF; 
          }

         for(int i=-5;i<5;i++)
         for(int j=-5;j<5;j++)
         {
            byte_array[i+x_center][j+y_center]=0xFFFFFF; 
         }


/////////////////  draw_lidar CIRCLE END //////////////////////
/////////////////  draw_origin CIRCLE START //////////////////////

      for(double i=0; i<360;i=i+0.1)
          {
            float x_circle = cos(((i+rotate_angle)*PI)/180)*(170)*size;
            float y_circle = -sin(((i+rotate_angle)*PI)/180)*(170)*size;
            int x_circle_pos = x_circle/1+x_center+cos((robot_angle_offset*PI)/180)*13;
            int y_circle_pos = y_circle/1+y_center-sin((robot_angle_offset*PI)/180)*13;
            byte_array[y_circle_pos][x_circle_pos]=0x0000FF; 
          }


/////////////////  draw_origin CIRCLE END //////////////////////


    // PutPixel
    for(int y=0;y<heigth;y++)
         for(int x=0;x<width;x++)
         {
                  XPutPixel(image, x, y,byte_array[y][x]);
         }


    // byte_array init white
         for(int y=0; y<heigth;y++)
         for(int x=0; x<width;x++)
          {
            byte_array[y][x]=0xffffff; //b + g*256 + r*65536
          }


         XPutImage(disp, win, gc, image, 0, 0, 0, 0, width, heigth);
}
 */
/////////////////  Lidar data //////////////////////

/*
  void display(float *angle,float *distance,int length)
  {
    if(display_lidar==True)
    {
      lidar_draw(angle,distance,length);
    }

    if(display_control==True)
    {

    }
  }
  */
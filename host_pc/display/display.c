#define display_x11 True

#define display_lidar True
#define display_control True


#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/X.h>
#include <X11/Xutil.h>
#include <math.h>

#define circle_size 60
#define table_size 70
#define PI 3.1415926
#define size 0.2
#define width  2000
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
  win = XCreateSimpleWindow ( disp, root, 0, 0, width, heigth,
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

  double d_ch[7][2]={0};

  for(int i=0;i<7;i++)
  {
    d_ch[i][0]=(double)arr[i][0];
    d_ch[i][1]=(double)arr[i][1]*0.02929;
  }


/////////////// RADAR CIRCLE START//////////////

      for(int s =0; s<420; s+=circle_size)
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

/////////////// RADAR CIRCLE END//////////////

/////////////// TARGET POINT START//////////////

  float ch1_y = -sin(((90)*PI)/180)*(d_ch[0][1]/5)*circle_size+y_center;
  float ch1_x = x_center;

  if(ch1_y>980)
  ch1_y=980;
  if(ch1_x>980)
  ch1_x=980;

  float ch2_y = -sin(((30)*PI)/180)*(d_ch[1][1]/5)*circle_size+y_center;
  float ch2_x = -cos(((30)*PI)/180)*(d_ch[1][1]/5)*circle_size+x_center;

    if(ch2_y>980)
  ch2_y=980;
  if(ch2_x>980)
  ch2_x=980;


  float ch3_y = sin(((30)*PI)/180)*(d_ch[2][1]/5)*circle_size+y_center;
  float ch3_x = -cos(((30)*PI)/180)*(d_ch[2][1]/5)*circle_size+x_center;


  if(ch3_y>980)
  ch3_y=980;
  if(ch3_x>980)
  ch3_x=980;


  float ch4_y = sin(((90)*PI)/180)*(d_ch[3][1]/5)*circle_size+y_center;
  float ch4_x = x_center;


  if(ch4_y>980)
  ch4_y=980;
  if(ch4_x>980)
  ch4_x=980;


  float ch5_y = sin(((30)*PI)/180)*(d_ch[4][1]/5)*circle_size+y_center;
  float ch5_x = cos(((30)*PI)/180)*(d_ch[4][1]/5)*circle_size+x_center;
  
  if(ch5_y>980)
  ch5_y=980;
  if(ch5_x>980)
  ch5_x=980;


  float ch6_y = -sin(((30)*PI)/180)*(d_ch[5][1]/5)*circle_size+y_center;
  float ch6_x = cos(((30)*PI)/180)*(d_ch[5][1]/5)*circle_size+x_center;

  if(ch6_y>980)
  ch6_y=980;
  if(ch6_x>980)
  ch6_x=980;



  for(int i=0;i<20;i++)
  for(int j=0;j<20;j++)
  {
    if(d_ch[0][0]==1)
      byte_array[(int)ch1_y+j][(int)ch1_x+i]=0xFF0000;
    if(d_ch[1][0]==1)
      byte_array[(int)ch2_y+j][(int)ch2_x+i]=0xFF0000;
    if(d_ch[2][0]==1)
      byte_array[(int)ch3_y+j][(int)ch3_x+i]=0xFF0000;
    if(d_ch[3][0]==1)
      byte_array[(int)ch4_y+j][(int)ch4_x+i]=0xFF0000;
    if(d_ch[4][0]==1)
      byte_array[(int)ch5_y+j][(int)ch5_x+i]=0xFF0000;
    if(d_ch[5][0]==1)
      byte_array[(int)ch6_y+j][(int)ch6_x+i]=0xFF0000;
  }

/////////////// TARGET POINT END//////////////

////////////// DRAW TABLE START //////////////
#define table_color 0xFFFFFF

// column 1

int table_start_point_x=1000;
int table_start_point_y=200;

int column_legth = 800;
int row_legth = 600;

int column_num = 7;
int row_num = 4;


for(int j=0; j<=column_num; j++)
{
  for(int i=0;i<column_legth;i++)
  {
    byte_array[table_start_point_y+(row_legth/column_num)*j][table_start_point_x+i]=table_color;
    byte_array[table_start_point_y+(row_legth/column_num)*j+1][table_start_point_x+i]=table_color;
    byte_array[table_start_point_y+(row_legth/column_num)*j+2][table_start_point_x+i]=table_color;
  }
}

for(int j=0; j<=row_num; j++)
{
  for(int i=0;i<row_legth;i++)
  {
    byte_array[table_start_point_y+i][table_start_point_x+(column_legth/row_num)*j]=table_color;
    byte_array[table_start_point_y+i][table_start_point_x+(column_legth/row_num)*j+1]=table_color;
    byte_array[table_start_point_y+i][table_start_point_x+(column_legth/row_num)*j+2]=table_color;
  }
}

//// radar on&off ///
  for(int i=-10;i<10;i++)
  for(int j=-10;j<10;j++)
  {
    for(int k=0;k<6;k++)
    if(d_ch[k][0]==1)
    {
      int point_y = table_start_point_y+(row_legth/column_num)*(1+k)+(row_legth/column_num)/2;
      int point_x = table_start_point_x+(column_legth/row_num)*1+(column_legth/row_num)/2;
      byte_array[point_y+j][point_x+i]=0x00FF00;
    }
  }

//// avoidance///
  for(int i=-10;i<10;i++)
  for(int j=-10;j<10;j++)
  {
    for(int k=0;k<6;k++)
    if(d_ch[k][1]<5)
    {
      int point_y = table_start_point_y+(row_legth/column_num)*(1+k)+(row_legth/column_num)/2;
      int point_x = table_start_point_x+(column_legth/row_num)*3+(column_legth/row_num)/2;
      byte_array[point_y+j][point_x+i]=0xFF0000;
    }
  }


////////////// DRAW TABLE END //////////////



/////////////////  DRAW START//////////////////////


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
        
        char ch7[100]={0};


        XPutImage(disp, win, gc, image, 0, 0, 0, 0, width, heigth);
        XDrawString(disp, win, gc,500, 490-circle_size*6, "30M", 4);
        XDrawString(disp, win, gc,500, 490-circle_size*5, "25M", 4);
        XDrawString(disp, win, gc,500, 490-circle_size*4, "20M", 4);
        XDrawString(disp, win, gc,500, 490-circle_size*3, "15M", 4);
        XDrawString(disp, win, gc,500, 490-circle_size*2, "10M", 4);
        XDrawString(disp, win, gc,500, 490-circle_size*1, "5M", 2);

///////////////////// num ////////////////
        XDrawString(disp, win, gc,table_start_point_x+(column_legth/row_num)/2, table_start_point_y+(row_legth/column_num)*1+(row_legth/column_num)/2+10, "1", 1);
        XDrawString(disp, win, gc,table_start_point_x+(column_legth/row_num)/2, table_start_point_y+(row_legth/column_num)*2+(row_legth/column_num)/2+10, "2", 1);
        XDrawString(disp, win, gc,table_start_point_x+(column_legth/row_num)/2, table_start_point_y+(row_legth/column_num)*3+(row_legth/column_num)/2+10, "3", 1);
        XDrawString(disp, win, gc,table_start_point_x+(column_legth/row_num)/2, table_start_point_y+(row_legth/column_num)*4+(row_legth/column_num)/2+10, "4", 1);
        XDrawString(disp, win, gc,table_start_point_x+(column_legth/row_num)/2, table_start_point_y+(row_legth/column_num)*5+(row_legth/column_num)/2+10, "5", 1);
        XDrawString(disp, win, gc,table_start_point_x+(column_legth/row_num)/2, table_start_point_y+(row_legth/column_num)*6+(row_legth/column_num)/2+10, "6", 1);

////////////////// title ///////////////////
        XDrawString(disp, win, gc,table_start_point_x+(column_legth/row_num)*0+50, table_start_point_y + (row_legth/column_num)/2+10, "Radar num", 9);
        XDrawString(disp, win, gc,table_start_point_x+(column_legth/row_num)*1+20, table_start_point_y + (row_legth/column_num)/2+10, "Radar on/off", 12);
        XDrawString(disp, win, gc,table_start_point_x+(column_legth/row_num)*2+20, table_start_point_y + (row_legth/column_num)/2+10, "Radar distance", 14);
        XDrawString(disp, win, gc,table_start_point_x+(column_legth/row_num)*3+50, table_start_point_y + (row_legth/column_num)/2+10, "avoidance", 9);

////////////////// distance ///////////////////


        char law_data_text[6][30]={0};
        for(int i=0;i<6;i++)
        {
          sprintf(law_data_text[i],"%d",arr[i][1]);
          XDrawString(disp, win, gc,table_start_point_x+(column_legth/row_num)*2 + (column_legth/row_num)/2, table_start_point_y+(row_legth/column_num)*(i+1)+(row_legth/column_num)/2+10, law_data_text[i], sizeof(law_data_text[i])/sizeof(char));
        }




        sprintf(ch7,"%0.1f",d_ch[6][1]);

        XDrawString(disp, win, gc,840, 750, ch7, 4);

        XFlush(disp);
}

/////////////////  DRAW END //////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static unsigned char buf_uart1[4096];
static unsigned char buf_uart2[4096];
static unsigned char buf_tcpip[10000];


static unsigned char cmd_uart1[4096];
static unsigned char cmd_uart2[4096];

static int uart1_cnt;
static int uart2_cnt;

static const char *lidar_uart_device = "/dev/ttyS3";
static const char *base_uart_device = "/dev/ttyS1";

typedef struct uart_state {
   int64_t uart1_faild;
   int64_t uart2_faild;
   int64_t uart1_sucess;
   int64_t uart2_sucess;
}UART_STATE;

void uart1_reader(unsigned char * input,int count);
void uart2_reader(unsigned char * input,int count);
void send_speed(char right_speed,char left_speed);
int uart_init(const char* device);
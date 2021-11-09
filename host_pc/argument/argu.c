#include "../include/main.h"

char* input_host_address;
int port_num;

void input_parameter(int argc, char **argv)
{
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    port_num=atoi(argv[2]);
    input_host_address = argv[1];

    printf("host_address: %s\n", input_host_address);
    printf("port: %d\n", port_num);
    printf("input_parameter_check_done\n");

}
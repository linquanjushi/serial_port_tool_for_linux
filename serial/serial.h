#ifndef LINQUAN_INCLUDE_SERIAL_H
#define LINQUAN_INCLUDE_SERIAL_H

#include <pthread.h>

int serial_fd; /* File descriptor for the port */
pthread_t tid;

int open_port(char* name);
int close_port();
int read_data(unsigned char* buf,int num);
int start_readThread();
int write_data(unsigned char* buf,int size);


void * func_callback(void * func);

struct serial_device_t {
    int (*read_data_callback)(unsigned char* buf, int size);
} *serial_device;

//serial_device serial_port;
//serial_device_t* serial_device;

#endif

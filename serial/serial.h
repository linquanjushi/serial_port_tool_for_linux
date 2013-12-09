#ifdef LINQUAN_INCLUDE_SERIAL_H
#define LINQUAN_INCLUDE_SERIAL_H

#include <pthread.h>

int serial_fd; /* File descriptor for the port */
//pthread_t tid;

int open_port(char* name);
int close_port();
int read_data(unsined char* buf,int num);
int start_readThread();
int write_data(unsigned char* buf,int size);


#endif

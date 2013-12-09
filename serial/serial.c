#include <unistd.h>
#include <termios.h>
#include <fcntl.h> 
#include <stdlib.h>
#include <stdio.h>


#include "serial.h"

//open serial port
int serial_fd = -1;
int open_port(char* name)
{
	//system("chmod 666 /dev/ttyUSB0");
	//"/dev/ttyUSB0"
	serial_fd = open(name, O_RDWR | O_NOCTTY | O_NDELAY);
	//serial_fd = open(name, O_RDWR | O_NOCTTY );
	//fcntl(fd, F_SETFL, FNDELAY);
	if (serial_fd == -1)
	{
		/*
		 * Could not open the port.
		 */
		g_print("open_port: Unable to open %s -",name);
	}
	else
	{
		 if(isatty(serial_fd))
	      {
				g_print("isatty\n");
                        struct termios  ios;
                        tcgetattr(serial_fd, &ios);

                       // LOGI("set to 115200bps, 8-N-1");
                        bzero(&ios, sizeof(ios));
                        ios.c_cflag = B4800 | CS8 | CLOCAL | CREAD;
                        ios.c_iflag = IGNPAR;
                        ios.c_oflag = 0;
                        ios.c_lflag = 0;  // disable ECHO, ICANON, etc... 
						tcsetattr(serial_fd, TCSANOW, &ios);
           }
		//fcntl(serial_fd, F_SETFL, 0);
	     start_readThread();
	}
		return (serial_fd);
}

int close_port()
{
	g_print("close port ...");
	return close(serial_fd);
}

int write_data(unsigned char* buf,int size)
{
	int n = write(serial_fd, buf,size);
	if (n < 0)
       g_print("write() of %d bytes failed!\n",size);
	return n;

}

int read_data(unsigned char* buf,int num)
{
	int n = read(serial_fd,buf,num);
	return 0;
}

void *thrd_func(void *arg){
	g_print("start thrd func...\n");
	unsigned char buf[24];
		int size=0;
		while(1){
		g_print("start to read data...");
		while((size = read_data(buf,8)) > 0){
			int i=0;
			for(i=0;i<size;i++){
				g_print("%x ",buf[i]);
			}
			g_printf("\n");
		}
			if(size == 0){g_print("no data \n");}
			usleep(1000000);
			//break;	
		}

//pthread_exit(NULL); //退出线程
}

int start_readThread(){
	g_print("start read thread...\n");
	pthread_t tid;
	  // 创建线程tid，且线程函数由thrd_func指向，是thrd_func的入口点，即马上执行此线程函数
	
    if (pthread_create(&tid,NULL,thrd_func,NULL)!=0) {
         printf("Create thread error!\n");
         exit(1);
     }
	
return 1;
}

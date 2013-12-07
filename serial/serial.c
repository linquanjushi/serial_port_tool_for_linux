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
	//"/dev/ttyUSB0"
	serial_fd = open(name, O_RDWR | O_NOCTTY | O_NDELAY);
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
				g_print("isatty");
                        struct termios  ios;
                        tcgetattr(serial_fd, &ios);

                       // LOGI("set to 115200bps, 8-N-1");
                        bzero(&ios, sizeof(ios));
                        ios.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
                        ios.c_iflag = IGNPAR;
                        ios.c_oflag = 0;
                        ios.c_lflag = 0;  // disable ECHO, ICANON, etc... 
						tcsetattr(serial_fd, TCSANOW, &ios);
           }
		//fcntl(serial_fd, F_SETFL, 0);
	}
		return (serial_fd);
}

int close_port()
{
	return close(serial_fd);
}

int write_data()
{
	int n = write(serial_fd, "ATZ\r", 4);
	if (n < 0)
       g_print("write() of 4 bytes failed!\n");
	return n;

}

int read_data()
{
	return 0;
}
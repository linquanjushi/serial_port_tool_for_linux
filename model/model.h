#ifndef LINQUAN_SRAIL_MODEL_H
#define LINQUAN_SRAIL_MODEL_H

#include<gtk/gtk.h>

static const char* serial_port_list[]={
	"ttyUSB0",
	"ttyS0",
	"ttyS1",
	"none",
};

static const char* ctrol_list[]={
	"波特率",
	"数据位",
	"停止位",
	"校验位",
	"流控制"
};

GtkTextBuffer* display_buffer;

#endif


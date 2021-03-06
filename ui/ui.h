#ifndef SERIAL_UI_H
#define SERIAL_UI_H

#include<gtk/gtk.h>
#include "../model/model.h"
//窗口部件
GtkWidget *main_window; //主窗口

GtkWidget* display_area;//显示区域
GtkWidget* button_openFile;//打开文件按钮
GtkWidget* view_fileName;//显示文件名区域
GtkWidget* button_sendFile;//发送文件
GtkWidget* button_saveWindow;//保存窗口按钮
GtkWidget* button_clearWindow;//清除窗口内容
GtkWidget* checkbox_hex;//16进制显示窗口内容多选按钮
GtkWidget* label_hex_display;//HEX显示

GtkWidget* label_serial_num;//串口号
GtkWidget* serial_list_choice;//串口选择下拉列表
GtkWidget* pic_serial_status;//串口开关状态的图片
GtkWidget* button_open_close_serial_port;//串口开关
GtkWidget* button_help;//帮助按钮
GtkWidget* label_net_info;//
GtkWidget* button_expand;//扩展窗口按钮

GtkWidget* label_baud_rate;//波特率
GtkWidget* list_baud_rate;//波特率下拉菜单

GtkWidget* label_data_bit;//数据位
GtkWidget* list_data_bit;//
GtkWidget* label_stop_bit;//停止位
GtkWidget* list_stop_bit;
GtkWidget* label_check_bit;//校验位
GtkWidget* list_check_bit;
GtkWidget* label_flow_control;//流控制
GtkWidget* list_flow_control;

GtkWidget* checkbox_DTR;//DTR
GtkWidget* label_DTR;
GtkWidget* checkbox_regularly_sent;//定时发送
GtkWidget* label_regularly_sent;//
GtkWidget* checkbox_hex_send;//HEX 发送
GtkWidget* label_hex_send;
GtkWidget* checkbox_RTS;//RTS
GtkWidget* label_RTS;
GtkWidget* inputview_send_rate;//?ms/次
GtkWidget* label_send_rate;
GtkWidget* checkbox_send_newline;//发送新行
GtkWidget* label_send_newline;
GtkWidget* label_inputbox;//
GtkWidget* button_send_message;//发送按钮
GtkWidget* inputbox_sendmessage;//字符串输入框
GtkWidget* label_html_info;//html

GtkWidget* label_status_http;
GtkWidget* label_status_send_byte;
GtkWidget* label_status_receive_byte;
GtkWidget* label_status_serial_port;//串口信息
GtkWidget* label_status_other;//CTS,DSR,RLSD

//窗口框架
GtkWidget* main_vbox;
GtkWidget* hbox_display;//显示框区域
GtkWidget* hbox_open;//打开文件一行的显示框架
GtkWidget* hbox_serial_nub;//串口号一行的显示框架

GtkWidget* hbox_baud_rate;//波特率一行的显示区域
//GtkWidget* vbox_baud_rate;

//GtkWidget* vbox_DTR_big;
//GtkWidget* hbox_DTR_big;
//GtkWidget* vbox_DTR_small;
//GtkWidget* vbox_html_info;

//GtkWidget* hbox_input_view;

GtkWidget* hbox_status;//状态栏一行的显示框架


//窗口布局函数
void makeUI();
void makeMainWindow();
void main_frame();
void makeDisplayArea();
void make_first_line();
void make_second_line();
void make_third_line();
void make_status_line();

//
enum{
	COL_CITY,
	N_COLUMNS
};


static GtkWidget* ctrol_combs[5];//波特率，数据位，停止位，校验位，流控制

//GtkTextBuffer *data_buffer;


#endif

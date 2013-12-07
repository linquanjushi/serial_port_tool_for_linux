#ifndef LINQUAN_SERIAL_TOOL_EVENT_H
#define LINQUAN_SERIAL_TOOL_EVENT_H

#include "../serial/serial.h"
//exit
void  cb_exit(GtkWidget *widget, gpointer data);

void init_events();

//open file
void open_file(GtkWidget *widget, gpointer data);

//send file
void send_file(GtkWidget *widget, gpointer data);
//save window
void save_window(GtkWidget *widget, gpointer data);
//clear window
void clear_window(GtkWidget *widget, gpointer data);
//set hex display
void set_HEX_display(GtkWidget *widget, gpointer data);
//select serial port
void set_serial_port(GtkWidget *widget, gpointer data);
//open close serial port
void enable_serial_port(GtkWidget *widget, gpointer data);
//help info
void show_help(GtkWidget *widget, gpointer data);
//show expand view
void show_expand_view(GtkWidget *widget, gpointer data);
//set baud rate
void set_baud_rate(GtkWidget *widget, gpointer data);
//set data bit
void set_data_bit(GtkWidget *widget, gpointer data);
//set stop bit
void set_stop_bit(GtkWidget *widget, gpointer data);
//set check bit
void set_check_bit(GtkWidget *widget, gpointer data);
//set flow control
void set_flow_control(GtkWidget *widget, gpointer data);
//set DTR
void setDTR(GtkWidget *widget, gpointer data);
void setRTS(GtkWidget *widget, gpointer data);
// timeing send
void set_time_send(GtkWidget *widget, gpointer data);
//send rate
void set_send_rate(GtkWidget *widget, gpointer data);
void set_hex_send(GtkWidget *widget, gpointer data);
void set_send_new_line(GtkWidget *widget, gpointer data);
void start_send_msg(GtkWidget *widget, gpointer data);

#endif

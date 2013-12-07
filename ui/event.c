#include "ui.h"
#include "event.h"
//#include "../serial/serial.h"

void  cb_exit(GtkWidget *widget, gpointer data) {
	// 按钮"button"的回调函数  
	g_print("你单击了退出按钮\n");       
	gtk_main_quit(); 
}

void init_events(){
	g_print("init events\n");  
	g_signal_connect(G_OBJECT(button_openFile),"clicked",G_CALLBACK(open_file),NULL);
	g_signal_connect(G_OBJECT(button_sendFile),"clicked",G_CALLBACK(send_file),NULL);
	g_signal_connect(G_OBJECT(button_saveWindow),"clicked",G_CALLBACK(save_window),NULL);
	g_signal_connect(G_OBJECT(button_clearWindow),"clicked",G_CALLBACK(clear_window),NULL);
	g_signal_connect(G_OBJECT(checkbox_hex),"clicked",G_CALLBACK(set_HEX_display),NULL);

	g_signal_connect (serial_list_choice, "changed", G_CALLBACK (set_serial_port), NULL);
	
	g_signal_connect(G_OBJECT(button_open_close_serial_port),"clicked",G_CALLBACK(enable_serial_port),NULL);
	g_signal_connect(G_OBJECT(button_help),"clicked",G_CALLBACK(show_help),NULL);
	g_signal_connect(G_OBJECT(button_expand),"clicked",G_CALLBACK(show_expand_view),NULL);

//
	g_signal_connect (G_OBJECT(list_baud_rate), "changed", G_CALLBACK (set_baud_rate), NULL);
	g_signal_connect (G_OBJECT(list_data_bit), "changed", G_CALLBACK (set_data_bit), NULL);
	g_signal_connect (G_OBJECT(list_stop_bit), "changed", G_CALLBACK (set_stop_bit), NULL);
	g_signal_connect (G_OBJECT(list_check_bit), "changed", G_CALLBACK (set_check_bit), NULL);
	g_signal_connect (G_OBJECT(list_flow_control), "changed", G_CALLBACK (set_flow_control), NULL);
//

	g_signal_connect(G_OBJECT(checkbox_DTR),"clicked",G_CALLBACK(setDTR),NULL);
	g_signal_connect(G_OBJECT(checkbox_regularly_sent),"clicked",G_CALLBACK(set_time_send),NULL);
	g_signal_connect(G_OBJECT(checkbox_hex_send),"clicked",G_CALLBACK(set_hex_send),NULL);
	g_signal_connect(G_OBJECT(checkbox_RTS),"clicked",G_CALLBACK(setRTS),NULL);
	g_signal_connect(G_OBJECT(checkbox_send_newline),"clicked",G_CALLBACK(set_send_new_line),NULL);

	g_signal_connect(G_OBJECT(button_send_message),"clicked",G_CALLBACK(start_send_msg),NULL);


	

	g_print("init events finished...\n");
}

//open file
void open_file(GtkWidget *widget, gpointer data){
	g_print("open_file...\n");     
}

//send file
void send_file(GtkWidget *widget, gpointer data){
	g_print(" send_file...\n");
}

//save window
void save_window(GtkWidget *widget, gpointer data){
	g_print(" save window...\n");
}

//clear window
void clear_window(GtkWidget *widget, gpointer data){
	g_print(" clear window...\n");
}

//set hex display
void set_HEX_display(GtkWidget *widget, gpointer data){
	g_print(" set_HEX_display...\n");	
	gboolean  checked = gtk_toggle_button_get_active(checkbox_hex);
	if(checked){
		g_print(" set_HEX_display: true...\n");	
	}else{
		g_print(" set_HEX_display: false...\n");		
	}
}

//select serial port
void set_serial_port(GtkWidget *widget, gpointer data){
	g_print("set_serial_port...\n");
	int i = gtk_combo_box_get_active( GTK_COMBO_BOX(widget) );
	g_print("selected item : %d\n",i);
	//if(i == -1 )return;
	GtkListStore *store = gtk_combo_box_get_model(GTK_COMBO_BOX(widget));
	//gtk_list_store_clear(store);
	
	//GtkListStore *item_store = gtk_list_store_new(1, G_TYPE_STRING);
	/*
	{
		GtkTreeIter iter, tmp_iter;
		gboolean valid;
		valid = gtk_tree_model_get_iter_first(store, &iter);
		while(valid)
		{
    		tmp_iter = iter;
    		valid = gtk_tree_model_iter_next(store, &iter);//先判断是否到结尾
    		gtk_list_store_remove(GTK_LIST_STORE(store), &tmp_iter);
		}
	}*/

	//GtkTreeIter iter;
	//gtk_list_store_append(GTK_LIST_STORE(item_store), &iter);
    //gtk_list_store_set(GTK_LIST_STORE(item_store), &iter, 0, "new item", -1);
	//gtk_combo_box_set_model(serial_list_choice,GTK_TREE_MODEL(item_store));
}

//open close serial port
void enable_serial_port(GtkWidget *widget, gpointer data){
	g_print("enable_serial_port...\n");
	if(open_port("/dev/ttyUSB0") >= 0){
		g_print("open port ok...\n");
		close_port();
	}else{
		g_print("open port error!...\n");
	}
}

//help info
void show_help(GtkWidget *widget, gpointer data){
	g_print("show help...\n");
}

//show expand view
void show_expand_view(GtkWidget *widget, gpointer data){
	g_print("show_expand_view...\n");
}

//set baud rate
void set_baud_rate(GtkWidget *widget, gpointer data){
	g_print("set_baud_rate...\n");
}

//set data bit
void set_data_bit(GtkWidget *widget, gpointer data){
	g_print("set_data_bit...\n");
}

//set stop bit
void set_stop_bit(GtkWidget *widget, gpointer data){
	g_print("set_stop_bit...\n");
}

//set check bit
void set_check_bit(GtkWidget *widget, gpointer data){
	g_print("set_check_bit...\n");
}

//set flow control
void set_flow_control(GtkWidget *widget, gpointer data){
	g_print("set_flow_control...\n");
}

//set DTR
void setDTR(GtkWidget *widget, gpointer data){
	g_print("set DTR...\n");
}
void setRTS(GtkWidget *widget, gpointer data){
	g_print("set RTS...\n");
}

// timeing send
void set_time_send(GtkWidget *widget, gpointer data){
	g_print("set timeine send...\n");
}

//send rate
void set_send_rate(GtkWidget *widget, gpointer data){
	g_print("set_send_rate...\n");
}

void set_hex_send(GtkWidget *widget, gpointer data){
	g_print("set_hex_send...\n");
}

void set_send_new_line(GtkWidget *widget, gpointer data){
	g_print("set_send_new_line...\n");
}

void start_send_msg(GtkWidget *widget, gpointer data){
	g_print("start send message...\n");
}

#include "ui.h"
#include "event.h"
#include "../model/model.h"

/*组装所有显示组件*/
void makeUI(){
	g_print("makeUI....\n");
	makeMainWindow();
	main_frame();

	makeDisplayArea();
	make_first_line();
	make_second_line();
 	make_third_line();
 	make_status_line();

	g_print("makeUI finished....\n");
}

//主框口
void makeMainWindow(){
	g_print("make main window start....\n");
 	main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);         //创建窗口(200x200大小)  
	gtk_window_set_title(GTK_WINDOW(main_window), "linux serial tool");         //设置窗口标题
	//设置窗口的默认大小（宽200，高度50）          
	//gtk_window_set_default_size(GTK_WINDOW(main_window), 400,250);
	g_signal_connect(G_OBJECT(main_window), "destroy",  G_CALLBACK(cb_exit),NULL);
	gtk_window_set_position(GTK_WINDOW(main_window), GTK_WIN_POS_CENTER);
	gtk_container_set_border_width (GTK_CONTAINER (main_window), 10);

	g_print("make main window finished....\n");
}

//显示框架
void main_frame(){
	g_print("make main frame start....\n");
	main_vbox = gtk_vbox_new(FALSE,10); //主框架
	gtk_container_add(GTK_CONTAINER(main_window),main_vbox);

	hbox_display = gtk_hbox_new(FALSE,10);//数据显示区域
	hbox_open = gtk_hbox_new(FALSE,10);//打开文件一行区域
	hbox_serial_nub = gtk_hbox_new(FALSE,10);//打开串口号一行区域
	hbox_baud_rate = gtk_hbox_new(FALSE,10);//波特率一行区域
	hbox_status = gtk_hbox_new(FALSE,10);//状态栏一行区域

	gtk_widget_set_size_request(hbox_display,-1,150);
	//gtk_widget_set_size_request(hbox_open,-1,10);
	//gtk_widget_set_size_request(hbox_serial_nub,-1,10);

	gtk_container_add(GTK_CONTAINER(main_vbox),hbox_display);
	gtk_container_add(GTK_CONTAINER(main_vbox),hbox_open);
	gtk_container_add(GTK_CONTAINER(main_vbox),hbox_serial_nub);
	gtk_container_add(GTK_CONTAINER(main_vbox),hbox_baud_rate);
	gtk_container_add(GTK_CONTAINER(main_vbox),hbox_status);

	g_print("make main frame finished....\n");
}
//数据显示区域
void makeDisplayArea(){
	g_print("makeDisplayArea....\n");
	GtkWidget* scrolled = gtk_scrolled_window_new(NULL,NULL); /*创建滚动窗口构件*/
	gtk_container_add(GTK_CONTAINER(hbox_display),scrolled);/*将滚动窗口构件加入窗体*/
	//gtk_widget_show(scrolled);/*显示滚动窗口构件*/

	display_buffer =  gtk_text_buffer_new(NULL);
	display_area = gtk_text_view_new_with_buffer(display_buffer);/*创建文本视图构件*/
	//data_buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (display_area));
	//gtk_text_buffer_set_text (data_buffer, "Your 1st GtkTextView widget!", -1);
	gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (display_area), GTK_WRAP_WORD);
	gtk_text_view_set_justification (GTK_TEXT_VIEW (display_area), GTK_JUSTIFY_LEFT);
	gtk_text_view_set_editable (GTK_TEXT_VIEW (display_area), FALSE);
	
	//gtk_source_view_set_indent_on_tab(GTK_SOURCE_VIEW(display_area),TRUE);//
	//gtk_text_view_get_buffer()
	//gtk_text_buffer_set_text()
/*
gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (textview), GTK_WRAP_WORD);
            gtk_text_view_set_justification (GTK_TEXT_VIEW (textview), GTK_JUSTIFY_LEFT);
            gtk_text_view_set_editable (GTK_TEXT_VIEW (textview), TRUE);
            gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (textview), TRUE);
            gtk_text_view_set_pixels_above_lines (GTK_TEXT_VIEW (textview), 5);
            gtk_text_view_set_pixels_below_lines (GTK_TEXT_VIEW (textview), 5);
            gtk_text_view_set_pixels_inside_wrap (GTK_TEXT_VIEW (textview), 5);
            gtk_text_view_set_left_margin (GTK_TEXT_VIEW (textview), 10);
            gtk_text_view_set_right_margin (GTK_TEXT_VIEW (textview), 10);
*/

	gtk_container_add(GTK_CONTAINER(scrolled), display_area);

	g_print("makeDisplayArea finished....\n");
	
}

void make_first_line(){
	g_print("make_first_line....\n");
	button_openFile = gtk_button_new_with_label("打开文件");
	view_fileName = gtk_text_view_new();
	gtk_widget_set_size_request(view_fileName,100,-1);
	button_sendFile = gtk_button_new_with_label("发送文件");
	button_saveWindow = gtk_button_new_with_label("保存窗口");
	button_clearWindow = gtk_button_new_with_label("清除窗口");
	checkbox_hex = gtk_check_button_new();
	label_hex_display = gtk_label_new_with_mnemonic("HEX显示");

	gtk_container_add(GTK_CONTAINER(hbox_open),button_openFile);
	gtk_container_add(GTK_CONTAINER(hbox_open),view_fileName);
	gtk_container_add(GTK_CONTAINER(hbox_open),button_sendFile);
	gtk_container_add(GTK_CONTAINER(hbox_open),button_saveWindow);
	gtk_container_add(GTK_CONTAINER(hbox_open),button_clearWindow);
	gtk_container_add(GTK_CONTAINER(hbox_open),checkbox_hex);
	gtk_container_add(GTK_CONTAINER(hbox_open),label_hex_display);
	
	g_print("make_first_line finished....\n");
}

void make_second_line(){
	g_print("make_second_line....\n");

	label_serial_num = gtk_label_new_with_mnemonic("串口号");
	serial_list_choice = gtk_combo_box_new();

	GtkListStore *item_store = gtk_list_store_new(1, G_TYPE_STRING);
	GtkTreeIter iter;
	GtkCellRenderer *renderer = NULL;
	{	
		int i;
		for(i=0; i<4; i++) {
   			gtk_list_store_append(item_store, &iter);
    		gtk_list_store_set(item_store, &iter, 0, serial_port_list[i], -1);
		}

		gtk_combo_box_set_model(serial_list_choice,GTK_TREE_MODEL(item_store));
		//serial_list_choice = gtk_combo_box_new_with_model(GTK_TREE_MODEL(item_store));

		renderer = gtk_cell_renderer_text_new();
    	gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(serial_list_choice), renderer, TRUE);
    	gtk_cell_layout_set_attributes(
        GTK_CELL_LAYOUT(serial_list_choice), renderer, "text", 0, NULL);

		gtk_combo_box_set_active (GTK_COMBO_BOX(serial_list_choice),0);
	}

	pic_serial_status = gtk_image_new_from_file ("../imgs/on.png");
	button_open_close_serial_port = gtk_button_new_with_label("串口开关");
	button_help = gtk_button_new_with_label("帮助");
	label_net_info = gtk_label_new_with_mnemonic("Author: 林泉居士");
	button_expand = gtk_button_new_with_label("扩展");

	gtk_container_add(GTK_CONTAINER(hbox_serial_nub),label_serial_num);
	gtk_container_add(GTK_CONTAINER(hbox_serial_nub),serial_list_choice);
	gtk_container_add(GTK_CONTAINER(hbox_serial_nub),pic_serial_status);
	gtk_container_add(GTK_CONTAINER(hbox_serial_nub),button_open_close_serial_port);
	gtk_container_add(GTK_CONTAINER(hbox_serial_nub),button_help);
	gtk_container_add(GTK_CONTAINER(hbox_serial_nub),label_net_info);
	gtk_container_add(GTK_CONTAINER(hbox_serial_nub),button_expand);
	
	g_print("make_second_line finished....\n");
}

void make_third_line(){
	g_print("make_third_line....\n");

	GtkWidget* vbox_left,*vbox_right;
	vbox_left = gtk_vbox_new(FALSE,10);//波特率。。。
	vbox_right = gtk_vbox_new(FALSE,10);//DTR..
	gtk_container_add(GTK_CONTAINER(hbox_baud_rate),vbox_left);
	gtk_container_add(GTK_CONTAINER(hbox_baud_rate),vbox_right);

	GtkWidget* hbox_r1,*hbox_r2;
	hbox_r1 = gtk_hbox_new(FALSE,10);
	hbox_r2 = gtk_hbox_new(FALSE,10);//input data
	gtk_container_add(GTK_CONTAINER(vbox_right),hbox_r1);
	gtk_container_add(GTK_CONTAINER(vbox_right),hbox_r2);

	GtkWidget* vbox_r1,*vbox_r2;
	vbox_r1 = gtk_vbox_new(FALSE,10);//DTR..
	vbox_r2 = gtk_vbox_new(FALSE,10);//html...
	gtk_container_add(GTK_CONTAINER(hbox_r1),vbox_r1);
	gtk_container_add(GTK_CONTAINER(hbox_r1),vbox_r2);

	int i = 0;
	for(i=0;i<5;i++){//左侧一列下拉框
		GtkWidget* label =  gtk_label_new_with_mnemonic(ctrol_list[i]);
		ctrol_combs[i] = gtk_combo_box_new();
		GtkWidget* hbox = gtk_hbox_new(FALSE,10);
		gtk_container_add(GTK_CONTAINER(hbox),label);
		gtk_container_add(GTK_CONTAINER(hbox),ctrol_combs[i]);
		gtk_container_add(GTK_CONTAINER(vbox_left),hbox);
	}
	list_baud_rate = ctrol_combs[0];
	list_data_bit = ctrol_combs[1];
	list_stop_bit = ctrol_combs[2];
	list_check_bit = ctrol_combs[3];
	list_flow_control = ctrol_combs[4];

    
	//DTR
	GtkWidget* hbox = gtk_hbox_new(FALSE,10);
	checkbox_DTR = gtk_check_button_new();
	label_DTR = gtk_label_new_with_mnemonic("DTR");
	 gtk_label_set_justify(label_DTR,GTK_JUSTIFY_LEFT);
	gtk_container_add(GTK_CONTAINER(hbox),checkbox_DTR);
	gtk_container_add(GTK_CONTAINER(hbox),label_DTR);
	//RTS
	checkbox_RTS = gtk_check_button_new();
	label_RTS = gtk_label_new_with_mnemonic("RTS");
	gtk_container_add(GTK_CONTAINER(hbox),checkbox_RTS);
	gtk_container_add(GTK_CONTAINER(hbox),label_RTS);
	gtk_container_add(GTK_CONTAINER(vbox_r1),hbox);

	//定时发送
	hbox = gtk_hbox_new(FALSE,10);
	checkbox_regularly_sent = gtk_check_button_new();
	label_regularly_sent = gtk_label_new_with_mnemonic("定时发送");
	gtk_container_add(GTK_CONTAINER(hbox),checkbox_regularly_sent);
	gtk_container_add(GTK_CONTAINER(hbox),label_regularly_sent);
	//发送频率
	inputview_send_rate = gtk_text_view_new();
	gtk_widget_set_size_request(inputview_send_rate,60,-1);
	label_send_rate = gtk_label_new_with_mnemonic("ms/次");
	gtk_container_add(GTK_CONTAINER(hbox),inputview_send_rate);
	gtk_container_add(GTK_CONTAINER(hbox),label_send_rate);
	gtk_container_add(GTK_CONTAINER(vbox_r1),hbox);

	//hex发送
	hbox = gtk_hbox_new(FALSE,10);
	checkbox_hex_send = gtk_check_button_new();
	label_hex_send = gtk_label_new_with_mnemonic("HEX发送");
	gtk_container_add(GTK_CONTAINER(hbox),checkbox_hex_send);
	gtk_container_add(GTK_CONTAINER(hbox),label_hex_send);
	//发送新行
	checkbox_send_newline = gtk_check_button_new();
	label_send_newline = gtk_label_new_with_mnemonic("发送新行");
	gtk_container_add(GTK_CONTAINER(hbox),checkbox_send_newline);
	gtk_container_add(GTK_CONTAINER(hbox),label_send_newline);
	gtk_container_add(GTK_CONTAINER(vbox_r1),hbox);
	
	//字符串输入框按钮
	hbox = gtk_hbox_new(FALSE,10);
	label_inputbox = gtk_label_new_with_mnemonic("字符串输入框 ： ");
	button_send_message = gtk_button_new_with_label("发送");
	gtk_container_add(GTK_CONTAINER(hbox),label_inputbox);
	gtk_container_add(GTK_CONTAINER(hbox),button_send_message);
	gtk_container_add(GTK_CONTAINER(vbox_r1),hbox);

	//html text view
	label_html_info = gtk_label_new_with_mnemonic("html from net work... ");
	gtk_container_add(GTK_CONTAINER(vbox_r2),label_html_info);

	//字符串输入框
	GtkTextBuffer* char_input_buffer =  gtk_text_buffer_new(NULL);
	inputbox_sendmessage = gtk_text_view_new_with_buffer(char_input_buffer);/*创建文本视图构件*/
	//inputbox_sendmessage = gtk_text_view_new();
	gtk_container_add(GTK_CONTAINER(hbox_r2),inputbox_sendmessage);

	g_print("make_third_line finished....\n");
}

void make_status_line(){
	g_print("make_status_line....\n");
	
	label_status_http = gtk_label_new_with_mnemonic("http://www.baidu.com");
	label_status_send_byte = gtk_label_new_with_mnemonic("S:0");
	label_status_receive_byte = gtk_label_new_with_mnemonic("R:0");
	label_status_serial_port = gtk_label_new_with_mnemonic("serial number");
	label_status_other = gtk_label_new_with_mnemonic("CTS=0 DSR=0 RLSD=0");

	gtk_container_add(GTK_CONTAINER(hbox_status),label_status_http);
	gtk_container_add(GTK_CONTAINER(hbox_status),label_status_send_byte);
	gtk_container_add(GTK_CONTAINER(hbox_status),label_status_receive_byte);
	gtk_container_add(GTK_CONTAINER(hbox_status),label_status_serial_port);
	gtk_container_add(GTK_CONTAINER(hbox_status),label_status_other);

	g_print("make_status_line finished....\n");

	
}

#if 0
void com_box_list(){
GtkListStore*list_store;
GtkCellRenderer*renderer;
GtkTreeIter iter;
int i;

list_store=gtk_list_store_new(N_COLUMNS,G_TYPE_STRING);
for(i=0;i<sizeof(items)/sizeof(items[0]);i++){
gtk_list_store_append(list_store,&iter);
gtk_list_store_set(list_store,&iter,
COL_CITY,items[i],
-1);
}
gtk_combo_box_set_model(GTK_COMBO_BOX(combo),GTK_TREE_MODEL(list_store));

renderer=gtk_cell_renderer_text_new();
gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(combo),renderer,TRUE);
gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(combo),renderer,
"text",COL_CITY,
NULL);

}
# endif

void makeAreaTools(){
	g_print("makeAreaTools....\n");
}

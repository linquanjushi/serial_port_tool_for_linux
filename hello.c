#include<gtk/gtk.h> 
 /* 一般可以在 /usr/include/gtk-2.0 下找到上边的头文件  
  * 上边的头文件的作用是包含进行GTK编程所有可能用到的头  
  * 文件，包括glib.h等 */ 

void  cb_exit(GtkWidget *widget, gpointer data) {
	// 按钮"button"的回调函数  
	g_print("你单击了按钮\n");       
	gtk_main_quit(); 
}

GdkPixbuf *create_pixbuf(const gchar * filename){ 
   GdkPixbuf *pixbuf; 
   GError *error = NULL; 
   pixbuf = gdk_pixbuf_new_from_file(filename, &error); 
   if(!pixbuf) { 
      fprintf(stderr, "%s\n", error->message); 
      g_error_free(error); 
   }     
	return pixbuf; 
}



int main(int argc, char *argv[]) {      
    GtkWidget *main_window;          // GtkWidget 是绝大部分可视组件的的基类  
	GtkWidget *button,*hbox, *editor;  //将要放置到主窗口中的按钮对象
    
	GtkWidget *menubar, *filemenu,*lookmenu,*look,*search,*file,*open,*quit;
  
    gtk_init(&argc, &argv);          //对程序传入的命令行参数进行标准化处理          
    main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);         //创建窗口(200x200大小)         
    gtk_window_set_title(GTK_WINDOW(main_window), "linux serial tool");         //设置窗口标题  

	//设置窗口的默认大小（宽200，高度50）          
	gtk_window_set_default_size(GTK_WINDOW(main_window), 200,50);
	g_signal_connect(G_OBJECT(main_window), "destroy",  G_CALLBACK(cb_exit),NULL);

	button = gtk_button_new_with_label("退出程序");         
   // gtk_container_add(GTK_CONTAINER(main_window), button);       
    //为"button"连接“单击事件”要调用的回调函数         
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(cb_exit),NULL);
      
	editor = gtk_entry_new();
	hbox = gtk_hbox_new(FALSE,10);

	menubar = gtk_menu_bar_new();
	filemenu = gtk_menu_new();
	lookmenu = gtk_menu_new();
	file = gtk_menu_item_new_with_label("File"); 
	//quit = gtk_menu_item_new_with_label("Quit");
	open = gtk_image_menu_item_new_from_stock(GTK_STOCK_OPEN, NULL);
	quit = gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT, NULL);

	look = gtk_menu_item_new_with_label("Look");
	search = gtk_menu_item_new_with_label("Search");

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), open); 
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);	
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(look), lookmenu); 
	gtk_menu_shell_append(GTK_MENU_SHELL(lookmenu), search);	
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), look);

	


	gtk_box_pack_start(GTK_BOX(hbox),editor,TRUE,TRUE,10);
	gtk_box_pack_start(GTK_BOX(hbox),button,FALSE,FALSE,10);

	gtk_box_pack_start(GTK_BOX(hbox),menubar,FALSE,FALSE,3);


	gtk_container_add(GTK_CONTAINER(main_window),hbox);
  
	gtk_window_set_icon(GTK_WINDOW(main_window), create_pixbuf("imgs/sunny.png"));
	gtk_window_set_position(GTK_WINDOW(main_window), GTK_WIN_POS_CENTER);

	g_signal_connect(G_OBJECT(quit),  "activate",G_CALLBACK(cb_exit), NULL); 
	//gtk_widget_show(button);
   // gtk_widget_show(main_window);         //显示窗口   
	//上边的两句可以合为 

	gtk_widget_show_all(main_window) ;
    

    gtk_main();          //Gtk程序主循环         
    return 0; 
} 

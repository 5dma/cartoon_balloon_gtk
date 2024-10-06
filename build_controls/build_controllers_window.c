#include "../headers.h"


/**
 * @file build_controls_window.c
 * @brief Contains functions for adding callbacks to the application window.
 */


void get_preview_widget_size(GdkSurface* self, GdkEvent* event, gpointer data) {
	User_Data * user_data = (User_Data *)data; 
	g_print("here\n");

	GtkWidget *picture_preview = user_data->gui_data->gui_data_annotation->picture_preview;
	Dimensions *dimensions_picture_preview_widget = &(user_data->annotation->dimensions_picture_preview_widget);

	dimensions_picture_preview_widget->width = gtk_widget_get_width (picture_preview);
	dimensions_picture_preview_widget->height = gtk_widget_get_height (picture_preview);


	g_print("width: %d, height: %d\n", dimensions_picture_preview_widget->width, dimensions_picture_preview_widget->height);
}

/**
Assigns callbacks to controls in the application window
 */
void build_controllers_window(User_Data *user_data) {

/* 	GtkGesture *gesture = gtk_gesture_click_new();
	gtk_gesture_single_set_button(GTK_GESTURE_SINGLE(gesture), 0);
	gtk_widget_add_controller(user_data->gui_data->window, (GTK_EVENT_CONTROLLER(gesture)));
	 */
	
	//g_signal_connect (user_data->gui_data->window, "show", G_CALLBACK (get_preview_widget_size), user_data);

}

#include "../headers.h"


/**
 * @file build_controllers_window.c
 * @brief Contains functions for adding callbacks to the application window.
 */

/**
Called when user clicks the window close control. The function writes all settings to disk and then destroys the window.
*/
void save_settings(GtkWidget *self, gpointer data) {

	User_Data *user_data = (User_Data *)data;
	save_files(user_data);
	gtk_window_destroy (GTK_WINDOW(self));
}

/**
Assigns callbacks to controls in the application window
 */
void build_controllers_window(User_Data *user_data) {

/* 	GtkGesture *gesture = gtk_gesture_click_new();
	gtk_gesture_single_set_button(GTK_GESTURE_SINGLE(gesture), 0);
	gtk_widget_add_controller(user_data->gui_data->window, (GTK_EVENT_CONTROLLER(gesture)));
	 */
	
	g_signal_connect (user_data->gui_data->window, "close-request", G_CALLBACK (save_settings), user_data);

}

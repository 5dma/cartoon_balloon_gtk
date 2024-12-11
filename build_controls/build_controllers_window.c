#include <headers.h>
/**
 * @file build_controllers_window.c
 * @brief Contains functions for adding callbacks to the application window.
 */

/**
Fired when user clicks the window close control. The function writes all settings to disk and then destroys the window.
* @param self Pointer to the application window.
* @param data Pointer to user data.
* \sa save_files()
*/
void save_settings(GtkWidget *self, gpointer data) {

	User_Data *user_data = (User_Data *)data;
	save_files(user_data);
	gtk_window_destroy (GTK_WINDOW(self));
}

/**
Assigns callbacks to controls in the application window.
* @param user_data Pointer to user data.
* \sa save_files()
 */
void build_controllers_window(User_Data *user_data) {

	g_signal_connect (user_data->gui_data->window, "close-request", G_CALLBACK (save_settings), user_data);

}

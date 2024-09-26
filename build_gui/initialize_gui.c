#include <gtk/gtk.h>
#include "../headers.h"

/**
 * @file initialize_gui.c
 * @brief Functions for populating the GUI.
 */

/**
 * Initializes the GUI from the settings read from disk.
 */
void initialize_gui(User_Data *user_data) {
	Gui_Data * gui_data = user_data->gui_data;
	Gui_Data_Configuration gui_data_configuration = gui_data->gui_data_configuration;
	g_print("Got before");
	gtk_spin_button_set_value ( GTK_SPIN_BUTTON(gui_data_configuration.spin_max_annotation_length), 100);
	g_print("Got here");

}
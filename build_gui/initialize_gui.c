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
	Gui_Controls * gui_data = user_data->gui_data;
	gtk_spin_button_set_value ( GTK_SPIN_BUTTON(gui_data-> configuration_controls ->spin_max_annotation_length), 100);

}
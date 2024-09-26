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

	/* Initialize the controls in the Configuration tab. */
	Gui_Data_Configuration gui_data_configuration = gui_data->gui_data_configuration;
	gtk_spin_button_set_value ( GTK_SPIN_BUTTON(gui_data_configuration.spin_max_annotation_length), user_data->configuration->max_annotation_length);
	gtk_spin_button_set_value ( GTK_SPIN_BUTTON(gui_data_configuration.spin_padding), user_data->configuration->padding);
	gtk_spin_button_set_value ( GTK_SPIN_BUTTON(gui_data_configuration.spin_elevation), user_data->configuration->elevation);
	gtk_spin_button_set_value ( GTK_SPIN_BUTTON(gui_data_configuration.spin_space), user_data->configuration->space);
	gtk_spin_button_set_value ( GTK_SPIN_BUTTON(gui_data_configuration.spin_top_margin), user_data->configuration->top_margin);
}
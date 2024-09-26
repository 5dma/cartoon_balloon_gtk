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


	/* Initialize the controls in the Annotation tab. */
	Gui_Data_Annotation gui_data_annotation = gui_data->gui_data_annotation;

	GtkEntryBuffer *temp_buffer = gtk_entry_get_buffer (GTK_ENTRY(gui_data_annotation.entry_input_image));
	gtk_entry_buffer_set_text (temp_buffer, user_data->annotation->input_image, -1);

	gtk_spin_button_set_value ( GTK_SPIN_BUTTON(gui_data_annotation.spin_text_bottom_left_x), user_data->annotation->text_bottom_left.x);
	gtk_spin_button_set_value ( GTK_SPIN_BUTTON(gui_data_annotation.spin_text_bottom_left_y), user_data->annotation->text_bottom_left.y);
	gtk_spin_button_set_value ( GTK_SPIN_BUTTON(gui_data_annotation.spin_vertex_x), user_data->annotation->vertex.x);
	gtk_spin_button_set_value ( GTK_SPIN_BUTTON(gui_data_annotation.spin_vertex_y), user_data->annotation->vertex.y);
	gtk_spin_button_set_value ( GTK_SPIN_BUTTON(gui_data_annotation.spin_new_width), user_data->annotation->new_width);

	temp_buffer = gtk_entry_get_buffer (GTK_ENTRY(gui_data_annotation.entry_text_string));
	gtk_entry_buffer_set_text (temp_buffer, user_data->annotation->text_string, -1);

}
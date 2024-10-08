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
	Gui_Data *gui_data = user_data->gui_data;

	/* Initialize the controls in the Configuration tab. */
	Gui_Data_Configuration *gui_data_configuration = gui_data->gui_data_configuration;
	gtk_spin_button_set_value ( GTK_SPIN_BUTTON(gui_data_configuration->spin_max_annotation_length), user_data->configuration->max_annotation_length);
	gtk_spin_button_set_value ( GTK_SPIN_BUTTON(gui_data_configuration->spin_padding), user_data->configuration->padding);
	gtk_spin_button_set_value ( GTK_SPIN_BUTTON(gui_data_configuration->spin_elevation), user_data->configuration->elevation);
	gtk_spin_button_set_value ( GTK_SPIN_BUTTON(gui_data_configuration->spin_space), user_data->configuration->space);
	gtk_spin_button_set_value ( GTK_SPIN_BUTTON(gui_data_configuration->spin_top_margin), user_data->configuration->top_margin);


	/* Initialize the controls in the Annotation tab. */
	Gui_Data_Annotation *gui_data_annotation = gui_data->gui_data_annotation;

	GtkEntryBuffer *temp_buffer = gtk_entry_get_buffer (GTK_ENTRY(gui_data_annotation->entry_input_image));
	gtk_entry_buffer_set_text (temp_buffer, user_data->annotation->input_image, -1);
	gtk_spin_button_set_value ( GTK_SPIN_BUTTON(gui_data_annotation->spin_text_bottom_left_x), user_data->annotation->text_bottom_left.x);
	gtk_spin_button_set_value ( GTK_SPIN_BUTTON(gui_data_annotation->spin_text_bottom_left_y), user_data->annotation->text_bottom_left.y);
	gtk_spin_button_set_value ( GTK_SPIN_BUTTON(gui_data_annotation->spin_vertex_x), user_data->annotation->vertex.x);
	gtk_spin_button_set_value ( GTK_SPIN_BUTTON(gui_data_annotation->spin_vertex_y), user_data->annotation->vertex.y);
	gtk_spin_button_set_value ( GTK_SPIN_BUTTON(gui_data_annotation->spin_new_width), user_data->annotation->new_width);


	gtk_entry_buffer_set_text (temp_buffer, user_data->annotation->text_string, -1);

	guint hash_size;
	gpointer key_array = g_hash_table_get_keys_as_array (user_data->theme_hash, &hash_size);
	GtkStringList *stringlist = gtk_string_list_new (key_array);
	gtk_drop_down_set_model ( GTK_DROP_DOWN( gui_data_annotation->dropdown_theme ), G_LIST_MODEL(stringlist));
	/* On initialize, set the first item in the model as selected. */
	gtk_drop_down_set_selected (GTK_DROP_DOWN( gui_data_annotation->dropdown_theme), 0); 
	GtkSingleSelection *single_selection_theme_dropdown = gtk_single_selection_new ( G_LIST_MODEL(stringlist));
	g_free(key_array);


	/* Initialize the controls in the Theme tab. */

	Gui_Data_Theme *gui_data_theme = gui_data->gui_data_theme;

	gtk_drop_down_set_model ( GTK_DROP_DOWN(gui_data_theme->dropdown_theme), G_LIST_MODEL(stringlist));
	gtk_drop_down_set_selected (GTK_DROP_DOWN( gui_data_theme->dropdown_theme), 0); 

	GtkStringObject *selected_theme_key = (GtkStringObject *)gtk_single_selection_get_selected_item (single_selection_theme_dropdown);
	const char *selected_theme_string = gtk_string_object_get_string (selected_theme_key);

	Theme *selected_theme_value = (Theme *) g_hash_table_lookup (user_data->theme_hash, selected_theme_string);

	temp_buffer = gtk_entry_get_buffer (GTK_ENTRY(gui_data_theme->entry_font_name));
	gtk_entry_buffer_set_text (temp_buffer, selected_theme_value->font , -1);
	
	temp_buffer = gtk_entry_get_buffer (GTK_ENTRY(gui_data_theme->entry_font_color));
	gtk_entry_buffer_set_text (temp_buffer, selected_theme_value->text_color , -1);
	
	gtk_spin_button_set_value ( GTK_SPIN_BUTTON(gui_data_theme->spin_font_size), selected_theme_value->font_size);
	
	temp_buffer = gtk_entry_get_buffer (GTK_ENTRY(gui_data_theme->entry_fill_color));
	gtk_entry_buffer_set_text (temp_buffer, selected_theme_value->balloon_fill_color, -1);

	temp_buffer = gtk_entry_get_buffer (GTK_ENTRY(gui_data_theme->entry_stroke_color));
	gtk_entry_buffer_set_text (temp_buffer, selected_theme_value->balloon_stroke_color, -1);

	gtk_spin_button_set_value ( GTK_SPIN_BUTTON(gui_data_theme->spin_stroke_width), selected_theme_value->stroke_width);

}
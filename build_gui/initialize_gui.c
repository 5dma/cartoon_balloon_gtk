#include <gtk/gtk.h>
#include <headers.h>

/**
 * @file initialize_gui.c
 * @brief Functions for populating the GUI.
 */

/**
 * Initializes the GUI from the settings read from disk.
 */
void initialize_gui(User_Data *user_data) {
	Gui_Data *gui_data = user_data->gui_data;
	Gui_Data_Annotation *gui_data_annotation = gui_data->gui_data_annotation;

	/* Initialize controls in the Annotations tab */

	const gchar *input_image = gtk_editable_get_text (GTK_EDITABLE(gui_data_annotation->entry_input_image));
	
	gtk_picture_set_filename (GTK_PICTURE(gui_data_annotation->picture_preview), input_image);
	/* Get initial dimensions of the image. */
	gdk_pixbuf_get_file_info(input_image, &(user_data->annotation->dimensions_original_image.width), &(user_data->annotation->dimensions_original_image.height));


	/* Initialize the controls in the Configuration tab. */
	Gui_Data_Configuration *gui_data_configuration = gui_data->gui_data_configuration;
	gtk_spin_button_set_value ( GTK_SPIN_BUTTON(gui_data_configuration->spin_max_annotation_length), user_data->configuration->max_annotation_length);
	gtk_spin_button_set_value ( GTK_SPIN_BUTTON(gui_data_configuration->spin_padding), user_data->configuration->padding);
	gtk_spin_button_set_value ( GTK_SPIN_BUTTON(gui_data_configuration->spin_elevation), user_data->configuration->elevation);
	gtk_spin_button_set_value ( GTK_SPIN_BUTTON(gui_data_configuration->spin_space), user_data->configuration->space);
	gtk_spin_button_set_value ( GTK_SPIN_BUTTON(gui_data_configuration->spin_top_margin), user_data->configuration->top_margin);

	guint hash_size;
	gpointer key_array = g_hash_table_get_keys_as_array (user_data->theme_hash, &hash_size);

	GListStore *list_store_themes = g_list_store_new(GTK_TYPE_STRING_OBJECT);
	user_data->list_store_themes = list_store_themes;

	const gchar **interator = (const gchar **)key_array;
	while(*interator != NULL) {
		g_list_store_append(list_store_themes, gtk_string_object_new(*interator));
		interator++;
	}
	
	g_free(key_array);

	g_list_store_append (list_store_themes, gtk_string_object_new(NEW_THEME));
	
	g_list_store_sort(list_store_themes,comparestrings, NULL);

	gtk_drop_down_set_model ( GTK_DROP_DOWN( gui_data_annotation->dropdown_theme ), G_LIST_MODEL(list_store_themes));
	/* On initialize, set the first item in the model as selected. */
	gtk_drop_down_set_selected (GTK_DROP_DOWN( gui_data_annotation->dropdown_theme), 0); 


	/* Initialize the controls in the Theme tab. */

	Gui_Data_Theme *gui_data_theme = gui_data->gui_data_theme;

	gtk_drop_down_set_model ( GTK_DROP_DOWN(gui_data_theme->dropdown_theme), G_LIST_MODEL(list_store_themes));
	gtk_drop_down_set_selected (GTK_DROP_DOWN( gui_data_theme->dropdown_theme), 0);

	gpointer temp = g_list_model_get_item (G_LIST_MODEL(list_store_themes), 0);
	const gchar *first_theme_name = gtk_string_object_get_string (GTK_STRING_OBJECT(temp));

	Theme *selected_theme_value = (Theme *) g_hash_table_lookup (user_data->theme_hash, first_theme_name);

	GtkEntryBuffer *temp_buffer = gtk_entry_get_buffer (GTK_ENTRY(gui_data_theme->entry_font_color));
	gtk_entry_buffer_set_text (temp_buffer, selected_theme_value->text_color , -1);
	
	temp_buffer = gtk_entry_get_buffer (GTK_ENTRY(gui_data_theme->entry_fill_color));
	gtk_entry_buffer_set_text (temp_buffer, selected_theme_value->balloon_fill_color, -1);

	temp_buffer = gtk_entry_get_buffer (GTK_ENTRY(gui_data_theme->entry_stroke_color));
	gtk_entry_buffer_set_text (temp_buffer, selected_theme_value->balloon_stroke_color, -1);

	gtk_spin_button_set_value ( GTK_SPIN_BUTTON(gui_data_theme->spin_stroke_width), selected_theme_value->stroke_width);

}
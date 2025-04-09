#include <gtk/gtk.h>
#include <headers.h>
#include <controls.h>

/**
 * @file initialize_gui.c
 * @brief Functions for populating the GUI.
 */

/**
 * Initializes the GUI from the settings read from disk.
*  @param user_data Pointer to user data.
 */
void initialize_gui(User_Data *user_data) {
	Gui_Data *gui_data = user_data->gui_data;
	Gui_Data_Annotation *gui_data_annotation = gui_data->gui_data_annotation;

	/* Initialize controls in the Annotations tab */

	const gchar *input_image = gtk_editable_get_text (GTK_EDITABLE(gui_data_annotation->entry_input_image));
	
	gtk_picture_set_filename (GTK_PICTURE(gui_data_annotation->original_preview), input_image);
	gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(gui_data_annotation->annotated_preview), draw_annotated_preview, user_data, NULL);
	gtk_widget_queue_draw(gui_data_annotation->annotated_preview);

	/* Get initial dimensions of the image. */
	gdk_pixbuf_get_file_info(input_image, &(user_data->annotation->dimensions_original_image.width), &(user_data->annotation->dimensions_original_image.height));

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

	gtk_editable_set_text (GTK_EDITABLE(gui_data_theme->entry_font_color), selected_theme_value->text_color);

	gtk_editable_set_text (GTK_EDITABLE(gui_data_theme->entry_fill_color), selected_theme_value->balloon_fill_color);

	gtk_editable_set_text (GTK_EDITABLE(gui_data_theme->entry_stroke_color), selected_theme_value->balloon_stroke_color);

	gtk_spin_button_set_value ( GTK_SPIN_BUTTON(gui_data_theme->spin_stroke_width), selected_theme_value->stroke_width);

	gtk_check_button_set_active (GTK_CHECK_BUTTON(gui_data_theme->check_rounded_corners), selected_theme_value->rounded_corners); 

}
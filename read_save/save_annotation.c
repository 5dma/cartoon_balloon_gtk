#include <glib/gstdio.h>
#include <headers.h>
#include <json-glib/json-glib.h>

/**
 * @file save_annotation.c
 * @brief Contains a function for saving the `annotation` stanza in the settings file.
 */


/**
* Formats into JSON the settings in the Annotation struct.
* @param user_data Pointer to user data.
* @param builder Pointer to the currently active JSON builder.
*/
void save_annotation(User_Data *user_data, JsonBuilder *builder) {

	Gui_Data_Annotation *gui_data_annotation = user_data->gui_data->gui_data_annotation;

	json_builder_set_member_name (builder, "annotation");

	json_builder_begin_object (builder);
	
	const gchar *entry_text = gtk_editable_get_text (GTK_EDITABLE(gui_data_annotation->entry_input_image));
	json_builder_set_member_name (builder, "input_image");
	json_builder_add_string_value(builder, entry_text);


	json_builder_set_member_name (builder, "text_bottom_left");
	json_builder_begin_object (builder); /* text_bottom_left*/

	double config_value  = gtk_spin_button_get_value (GTK_SPIN_BUTTON(gui_data_annotation->spin_text_bottom_left_x));
	json_builder_set_member_name (builder, "x");
	json_builder_add_int_value(builder, (guint64) config_value);

	config_value  = gtk_spin_button_get_value (GTK_SPIN_BUTTON(gui_data_annotation->spin_text_bottom_left_y));
	json_builder_set_member_name (builder, "y");
	json_builder_add_int_value(builder, (guint64) config_value);
	json_builder_end_object (builder); /* text_bottom_left */


	json_builder_set_member_name (builder, "vertex");
	json_builder_begin_object (builder); /* vertex*/

	config_value  = gtk_spin_button_get_value (GTK_SPIN_BUTTON(gui_data_annotation->spin_vertex_x));
	json_builder_set_member_name (builder, "x");
	json_builder_add_int_value(builder, (guint64) config_value);

	config_value  = gtk_spin_button_get_value (GTK_SPIN_BUTTON(gui_data_annotation->spin_vertex_y));
	json_builder_set_member_name (builder, "y");
	json_builder_add_int_value(builder, (guint64) config_value);
	json_builder_end_object (builder); /* vertex */

	config_value  = gtk_spin_button_get_value (GTK_SPIN_BUTTON(gui_data_annotation->spin_new_width));
	json_builder_set_member_name (builder, "new_width");
	json_builder_add_int_value(builder, (guint64) config_value);


	entry_text = gtk_editable_get_text (GTK_EDITABLE(gui_data_annotation->entry_text_string ));
	json_builder_set_member_name (builder, "text_string");
	json_builder_add_string_value(builder, entry_text);

	GObject *gobject = gtk_drop_down_get_selected_item (GTK_DROP_DOWN(gui_data_annotation->dropdown_theme));
	entry_text = gtk_string_object_get_string (GTK_STRING_OBJECT(gobject));
	json_builder_set_member_name (builder, "theme");
	json_builder_add_string_value(builder, entry_text);


	json_builder_end_object (builder); /* annotation */


}
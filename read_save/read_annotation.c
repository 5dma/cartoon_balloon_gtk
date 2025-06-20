#include <glib-object.h>
#include <headers.h>
#include <json-glib/json-glib.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @file read_annotation.c
 * @brief Contains a function for reading the `annotation` stanza in the settings file.
 */

/**
Reads the relevant settings file into an Annotation struct. The settings in this struct file, such as the annotation text, are one-off: they can apply to only the current image.
* @param user_data Pointer to user data.
* @param reader Pointer to the currently active JSON object.
 */
void read_annotation(User_Data *user_data, JsonReader *reader) {
	Annotation *annotation = user_data->annotation;
	Gui_Data_Annotation *gui_data_annotation = user_data->gui_data->gui_data_annotation;

	json_reader_read_member(reader, "annotation");

	json_reader_read_member(reader, "input_image");
	if (!json_reader_get_null_value(reader)) {
		gtk_editable_set_text(GTK_EDITABLE(gui_data_annotation->entry_input_image),
							  json_reader_get_string_value(reader));
	}
	json_reader_end_member(reader);

	json_reader_read_member(reader, "text_bottom_left");
	json_reader_read_member(reader, "x");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(gui_data_annotation->spin_text_bottom_left_x), json_reader_get_int_value(reader));
	json_reader_end_member(reader);

	json_reader_read_member(reader, "y");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(gui_data_annotation->spin_text_bottom_left_y), json_reader_get_int_value(reader));
	json_reader_end_member(reader);
	json_reader_end_member(reader); /* text_bottom_left */

	json_reader_read_member(reader, "vertex");
	json_reader_read_member(reader, "x");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(gui_data_annotation->spin_vertex_x), json_reader_get_int_value(reader));
	json_reader_end_member(reader);

	json_reader_read_member(reader, "y");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(gui_data_annotation->spin_vertex_y), json_reader_get_int_value(reader));
	json_reader_end_member(reader);
	json_reader_end_member(reader); /* vertex */

	json_reader_read_member(reader, "new_width");
	guint annotation_value = json_reader_get_int_value(reader);
	if (annotation_value == 0) {
		annotation_value = 520;
	}
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(gui_data_annotation->spin_new_width), annotation_value);
	json_reader_end_member(reader);

	json_reader_read_member(reader, "text_string");
	if (!json_reader_get_null_value(reader)) {
		gtk_editable_set_text(GTK_EDITABLE(gui_data_annotation->entry_text_string), json_reader_get_string_value(reader));
	}
	json_reader_end_member(reader);

	json_reader_end_member(reader); /* annotation */

	annotation->resize_proportion_x = 0;
	annotation->resize_proportion_y = 0;
	/* The following object is freed in cleanup(). */
	annotation->crosshair_cursor = gdk_cursor_new_from_name("crosshair", NULL);
	annotation->is_selecting_text_bottom_left_point = FALSE;
	annotation->is_selecting_vertex_point = FALSE;
}

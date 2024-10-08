#include <stdio.h>
#include <stdlib.h>
#include <glib-object.h>
#include <json-glib/json-glib.h>
#include "headers.h"


/**
 * @file read_annotation.c
 * @brief Reads an annotation's configuration file.
 */

/**
Reads the configuration file into an `Annotation` struct. The settings in this configuration file, such as the annotation text, are one-off: they can apply to only the current image. 
 */
void read_annotation(User_Data *user_data)
{

	user_data->annotation = (Annotation *)g_malloc(sizeof(Annotation));
	Annotation *annotation = user_data->annotation;

	JsonReader *reader = user_data->reader;

	json_reader_read_member(reader, "annotation");

	json_reader_read_member(reader, "input_image");
	g_strlcpy(annotation->input_image, json_reader_get_string_value(reader), MAX_PATH_LENGTH);
	json_reader_end_member(reader);

	json_reader_read_member(reader, "text_bottom_left");
	json_reader_read_member(reader, "x");
	annotation->text_bottom_left.x = json_reader_get_int_value(reader);
	json_reader_end_member(reader);

	json_reader_read_member(reader, "y");
	annotation->text_bottom_left.y = json_reader_get_int_value(reader);
	json_reader_end_member(reader);
	json_reader_end_member(reader); /* text_bottom_left */

	json_reader_read_member(reader, "vertex");
	json_reader_read_member(reader, "x");
	annotation->vertex.x = json_reader_get_int_value(reader);
	json_reader_end_member(reader);

	json_reader_read_member(reader, "y");
	annotation->vertex.y = json_reader_get_int_value(reader);
	json_reader_end_member(reader);
	json_reader_end_member(reader); /* vertex */


	json_reader_read_member(reader, "new_width");
	annotation->new_width = json_reader_get_int_value(reader);
	json_reader_end_member(reader);


	json_reader_read_member(reader, "text_string");
	g_strlcpy(annotation->text_string, json_reader_get_string_value(reader), user_data->configuration->max_annotation_length );
	json_reader_end_member(reader);

	json_reader_read_member(reader, "theme");
	g_strlcpy(annotation->theme, json_reader_get_string_value(reader), MAX_PATH_LENGTH);
	json_reader_end_member(reader);
	json_reader_end_member(reader); /* annotation */

	annotation->resize_proportion_x = 0;
	annotation->resize_proportion_y = 0;
	annotation->crosshair_cursor = gdk_cursor_new_from_name ("crosshair", NULL );
	annotation->is_selecting_text_bottom_left_point = FALSE;
	annotation->is_selecting_vertex_point = FALSE;

}

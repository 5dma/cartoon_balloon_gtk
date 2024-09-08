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
Annotation *read_annotation(Settings *settings)
{
	JsonParser *parser;
	GError *error;
	Annotation *annotation;

	parser = json_parser_new();
	error = NULL;
	json_parser_load_from_file(parser, ANNOTATION_FILE, &error);
	if (error)
	{
		logger(G_LOG_LEVEL_CRITICAL,"Unable to parse annotation JSON file", settings);
		g_print("Unable to parse `%s': %s\n", ANNOTATION_FILE, error->message);
		g_error_free(error);
		g_object_unref(parser);
		return NULL;
	}
	annotation = (Annotation *)g_malloc(sizeof(Annotation));

	json_parser_get_root(parser);
	JsonReader *reader;
	reader = json_reader_new(json_parser_get_root(parser));

	json_reader_read_member(reader, "new_width");
	annotation->new_width = json_reader_get_int_value(reader);
	json_reader_end_member(reader);

	json_reader_read_member(reader, "text_string");
	g_strlcpy(annotation->text_string, json_reader_get_string_value(reader), MAX_ANNOTATION_LENGTH);
	json_reader_end_member(reader);

	json_reader_read_member(reader, "original_image_path");
	g_strlcpy(annotation->original_image_path, json_reader_get_string_value(reader), MAX_ANNOTATION_LENGTH);
	json_reader_end_member(reader);

	json_reader_read_member(reader, "theme");
	g_strlcpy(annotation->theme, json_reader_get_string_value(reader), MAX_ANNOTATION_LENGTH);
	json_reader_end_member(reader);

	json_reader_read_member(reader, "text_bottom_left");
	json_reader_read_member(reader, "x");
	annotation->text_bottom_left.x = json_reader_get_int_value(reader);
	json_reader_end_member(reader);

	json_reader_read_member(reader, "y");
	annotation->text_bottom_left.y = json_reader_get_int_value(reader);
	json_reader_end_member(reader);
	json_reader_end_member(reader);

	json_reader_read_member(reader, "callout_vertex");
	json_reader_read_member(reader, "x");
	annotation->callout_vertex.x = json_reader_get_int_value(reader);
	json_reader_end_member(reader);

	json_reader_read_member(reader, "y");
	annotation->callout_vertex.y = json_reader_get_int_value(reader);

	annotation->resize_proportion_x = 0;
	annotation->resize_proportion_y = 0;

	/* Clean up */
	g_object_unref(parser);
	g_object_unref(reader);
	return annotation;
}

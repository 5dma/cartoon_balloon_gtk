#include <glib-object.h>
#include <json-glib/json-glib.h>
#include <stdio.h>
#include <stdlib.h>

#include "headers.h"

/**
 * @file read_json.c
 * @brief Reads the application's configuration file.
 */

/**
Reads the configuration file into a `Settings` struct. The settings in this configuration file are relatively static: they can apply to multiple images. 
 */
Settings *read_json() {
	JsonParser *parser;
	GError *error;
	Settings *settings;

	parser = json_parser_new();
	error = NULL;
	json_parser_load_from_file(parser, CONFIG_FILE, &error);
	if (error) {
		g_print("Unable to parse `%s': %s\n", CONFIG_FILE, error->message);
		g_error_free(error);
		g_object_unref(parser);
		return NULL;
	}
	settings = (Settings *)g_malloc(sizeof(Settings));

	JsonReader *reader;
	reader = json_reader_new(json_parser_get_root(parser));

	json_reader_read_member(reader, "balloon_fill_color");
	g_strlcpy(settings->balloon_fill_color, json_reader_get_string_value(reader), 8);
	json_reader_end_member(reader);

	json_reader_read_member(reader, "balloon_stroke_color");
	g_strlcpy(settings->balloon_stroke_color, json_reader_get_string_value(reader), 8);
	json_reader_end_member(reader);

	json_reader_read_member(reader, "padding");
	settings->padding = json_reader_get_int_value(reader);
	json_reader_end_member(reader);

	json_reader_read_member(reader, "elevation");
	settings->elevation = json_reader_get_int_value(reader);
	json_reader_end_member(reader);

	json_reader_read_member(reader, "space");
	settings->space = json_reader_get_int_value(reader);
	json_reader_end_member(reader);

	json_reader_read_member(reader, "stroke_width");
	settings->stroke_width = json_reader_get_int_value(reader);
	json_reader_end_member(reader);

	json_reader_read_member(reader, "top_margin");
	settings->top_margin = json_reader_get_int_value(reader);
	json_reader_end_member(reader);

	json_reader_read_member(reader, "font_size");
	settings->font_size = json_reader_get_int_value(reader);
	json_reader_end_member(reader);

	json_reader_read_member(reader, "text_color");
	g_strlcpy(settings->text_color, json_reader_get_string_value(reader), 8);
	json_reader_end_member(reader);

	json_reader_read_member(reader, "font");
	g_strlcpy(settings->font, json_reader_get_string_value(reader), 256);
	json_reader_end_member(reader);

	json_reader_read_member(reader, "new_image_path");
	g_strlcpy(settings->new_image_path, json_reader_get_string_value(reader), 256);
	json_reader_end_member(reader);

	json_reader_read_member(reader, "log_file_path");
	g_strlcpy(settings->log_file_path, json_reader_get_string_value(reader), 256);

	g_object_unref(parser);
	g_object_unref(reader);
	
	return settings;
}

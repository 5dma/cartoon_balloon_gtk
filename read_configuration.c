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
Reads the configuration file into a `Settings` struct. The settings in this configuration file are relatively static: they can apply to multiple images. Also opens the log file.
 */
void read_configuration(User_Data * user_data) {
	JsonParser *parser;
	GError *error;


	parser = json_parser_new();
	error = NULL;
	json_parser_load_from_file(parser, CONFIG_FILE, &error);
	if (error) {
		g_print("Unable to parse `%s': %s\n", CONFIG_FILE, error->message);
		g_error_free(error);
		g_object_unref(parser);
		return;
	}
	user_data->configuration = (Configuration *)g_malloc(sizeof(Configuration));
	Configuration * configuration = user_data->configuration;

	JsonReader *reader;
	reader = json_reader_new(json_parser_get_root(parser));
	
	gboolean success = FALSE;

	user_data->parser = parser;
	user_data->reader = reader;

	success = json_reader_read_member(reader, "configuration");

	json_reader_read_member(reader, "max_annotation_length");
	configuration->max_annotation_length = json_reader_get_int_value(reader);
	json_reader_end_member(reader);

	json_reader_read_member(reader, "padding");
	configuration->padding = json_reader_get_int_value(reader);
	json_reader_end_member(reader);

	json_reader_read_member(reader, "elevation");
	configuration->elevation = json_reader_get_int_value(reader);
	json_reader_end_member(reader);

	json_reader_read_member(reader, "space");
	configuration->space = json_reader_get_int_value(reader);
	json_reader_end_member(reader);

	json_reader_read_member(reader, "top_margin");
	configuration->top_margin = json_reader_get_int_value(reader);
	json_reader_end_member(reader);

	json_reader_read_member(reader, "log_file_path");
	g_strlcpy(configuration->log_file_path, json_reader_get_string_value(reader), 256);
	json_reader_end_member(reader);

	json_reader_read_member(reader, "new_image_path");
	g_strlcpy(configuration->new_image_path, json_reader_get_string_value(reader), 256);
	json_reader_end_member(reader);

	json_reader_end_member(reader); /* configuration stanza */

	configuration->log_file_pointer = get_log_file_pointer(configuration);

}

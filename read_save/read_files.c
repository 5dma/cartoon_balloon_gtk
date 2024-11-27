#include <headers.h>
#include <read_save.h>

/**
 * @file read_files.c
 * @brief Contains parent function for reading settings from disk in JSON format.
*/



/**
 * Reads settings from disk in JSON format. See also
 * - read_configuration()
 * - read_annotation()
 * - read_themes()
*/
void read_files(User_Data *user_data) {

	JsonParser *parser;
	GError *error;


	parser = json_parser_new();
	error = NULL;
	json_parser_load_from_file(parser, CONFIG_FILE, &error);
	if (error) {
		g_print("Unable to parse `%s': %s\n", CONFIG_FILE, error->message);
		g_error_free(error);
		g_object_unref(parser);

		/* Free memory that was allocated in allocate_structures(). */
		g_free(user_data->gui_data->gui_data_theme);
		g_free(user_data->gui_data->gui_data_annotation);
		g_free(user_data->gui_data->gui_data_configuration);
		g_free(user_data->gui_data);
		g_free(user_data);
		exit(1);
	}


	JsonReader *reader;
	reader = json_reader_new(json_parser_get_root(parser));
	
	read_configuration(user_data, reader);
	read_annotation(user_data, reader);
	read_themes(user_data, reader);

	g_object_unref(reader);
	g_object_unref(parser);
}
#include <headers.h>
#include <read_save.h>

/**
 * @file read_files.c
 * @brief Contains the parent function for reading settings in JSON format from disk.
*/

/**
 * Reads settings from disk in JSON format.
 * @param user_data Pointer to user data.
 * \sa read_configuration()
 * read_annotation()
 * read_themes() 
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

		cleanup(user_data, FALSE);
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
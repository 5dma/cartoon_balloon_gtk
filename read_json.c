#include <stdio.h>
#include <stdlib.h>
#include <glib-object.h>
#include <json-glib/json-glib.h>
#include "headers.h"

Settings * read_json() {
	printf("Inside read_json\n");
	JsonParser *parser;
	JsonNode *root;
	GError *error;
	parser = json_parser_new ();
	error = NULL;
	json_parser_load_from_file (parser, "/Users/mlautman/Documents/programming/c/balloon/configuration.json", &error);
	if (error)
	{
		g_print ("Unable to parse `%s': %s\n", "/Users/mlautman/Documents/programming/c/balloon/data.json", error->message);
		g_error_free (error);
		g_object_unref (parser);
		return NULL;
	 }
	Settings * settings;
	settings = (Settings *) g_malloc(sizeof(Settings));
	root = json_parser_get_root (parser);
	JsonReader * reader;
	reader = json_reader_new (json_parser_get_root (parser));
	gboolean test;
	test = json_reader_read_member (reader, "new_width");
	gint64 omg;
	omg = json_reader_get_int_value (reader);
	g_print("The value of omg is %lli\n", omg);

	g_object_unref (parser);
	return settings;
}



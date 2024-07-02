#include <stdio.h>
#include <stdlib.h>
#include <glib-object.h>
#include <json-glib/json-glib.h>

int read_json() {
	printf("Inside read_json\n");
	JsonParser *parser;
	JsonNode *root;
	GError *error;
	parser = json_parser_new ();
	error = NULL;
	json_parser_load_from_file (parser, "/Users/mlautman/Documents/programming/c/balloon/data.json", &error);
	if (error)
	{
		g_print ("Unable to parse `%s': %s\n", "/Users/mlautman/Documents/programming/c/balloon/data.json", error->message);
		g_error_free (error);
		g_object_unref (parser);
		return EXIT_FAILURE;
	 }
	root = json_parser_get_root (parser);
	g_object_unref (parser);
	return 0;
}



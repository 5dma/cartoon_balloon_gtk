#include <stdio.h>
#include <stdlib.h>
#include <glib-object.h>
#include <json-glib/json-glib.h>
#include "headers.h"

Annotation * read_annotation() {
	JsonParser *parser;
	GError *error;
	Annotation * annotation;
	JsonNode *root;
	
	parser = json_parser_new ();
	error = NULL;
	json_parser_load_from_file (parser, "/Users/mlautman/Documents/programming/c/balloon/annotation.json", &error);
	if (error)
	{
		g_print ("Unable to parse `%s': %s\n", "/Users/mlautman/Documents/programming/c/balloon/annotation.json", error->message);
		g_error_free (error);
		g_object_unref (parser);
		return NULL;
	}
	annotation = (Annotation *) g_malloc(sizeof(Annotation));
	
	root = json_parser_get_root (parser);
	JsonReader * reader;
	reader = json_reader_new (json_parser_get_root (parser));
	gboolean json_cursor;
	
	json_cursor = json_reader_read_member (reader, "text_string");
	g_strlcpy(annotation->text_string, json_reader_get_string_value (reader), 255);

	json_reader_end_member(reader);


	g_object_unref (parser);
	g_object_unref(reader);
	return annotation;
}



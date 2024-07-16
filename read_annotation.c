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
	g_print("The text string is %s\n", annotation->text_string);

	json_cursor = json_reader_read_member (reader, "text_bottom_left");
	json_cursor = json_reader_read_member (reader, "x");
	annotation->text_bottom_left.x = json_reader_get_int_value (reader);
	json_reader_end_member(reader);

	json_cursor = json_reader_read_member (reader, "y");
	annotation->text_bottom_left.y = json_reader_get_int_value (reader);
	json_reader_end_member(reader);
	json_reader_end_member(reader);
	
	json_cursor = json_reader_read_member (reader, "callout_vertex");
	json_cursor = json_reader_read_member (reader, "x");
	annotation->callout_vertex.x = json_reader_get_int_value (reader);
	json_reader_end_member(reader);

	json_cursor = json_reader_read_member (reader, "y");
	annotation->callout_vertex.y = json_reader_get_int_value (reader);

	annotation->resize_proportion_x = 0;
	annotation->resize_proportion_y = 0;

	g_print("Text bottom vertex x, y = %lld , %lld\n", annotation->text_bottom_left.x, annotation->text_bottom_left.y);
	g_print("Callout vertex x, y = %lld , %lld\n", annotation->callout_vertex.x, annotation->callout_vertex.y);

	g_object_unref (parser);
	g_object_unref(reader);
	return annotation;
}



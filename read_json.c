#include <stdio.h>
#include <stdlib.h>
#include <glib-object.h>
#include <json-glib/json-glib.h>
#include "headers.h"

Settings * read_json() {
	JsonParser *parser;
	GError *error;
	Settings * settings;
	JsonNode *root;
	
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
	settings = (Settings *) g_malloc(sizeof(Settings));
	
	root = json_parser_get_root (parser);
	JsonReader * reader;
	reader = json_reader_new (json_parser_get_root (parser));
	gboolean json_cursor;
	
	json_cursor = json_reader_read_member (reader, "new_width");
	settings->new_width = json_reader_get_int_value (reader);
	json_reader_end_member(reader);

	json_cursor = json_reader_read_member (reader, "balloon_fill_color");
	g_strlcpy(settings->balloon_fill_color, json_reader_get_string_value (reader), 8);
	json_reader_end_member(reader);

	json_cursor = json_reader_read_member (reader, "balloon_stroke_color");
	g_strlcpy(settings->balloon_stroke_color, json_reader_get_string_value (reader), 8);
	json_reader_end_member(reader);

	json_cursor = json_reader_read_member (reader, "excess_font_height");
	settings->excess_font_height = json_reader_get_int_value (reader);
	json_reader_end_member(reader);

	json_cursor = json_reader_read_member (reader, "padding");
	settings->padding = json_reader_get_int_value (reader);
	json_reader_end_member(reader);

	json_cursor = json_reader_read_member (reader, "excess_text_height");
	settings->excess_text_height = json_reader_get_int_value (reader);
	json_reader_end_member(reader);

	json_cursor = json_reader_read_member (reader, "callout_indent");
	settings->callout_indent = json_reader_get_int_value (reader);
	json_reader_end_member(reader);

	json_cursor = json_reader_read_member (reader, "callout_space");
	settings->callout_space = json_reader_get_int_value (reader);
	json_reader_end_member(reader);

	json_cursor = json_reader_read_member (reader, "elevation");
	settings->elevation = json_reader_get_int_value (reader);
	json_reader_end_member(reader);

	json_cursor = json_reader_read_member (reader, "space");
	settings->space = json_reader_get_int_value (reader);
	json_reader_end_member(reader);

	json_cursor = json_reader_read_member (reader, "stroke_width");
	settings->stroke_width = json_reader_get_int_value (reader);
	json_reader_end_member(reader);

	json_cursor = json_reader_read_member (reader, "extra_offset");
	settings->extra_offset = json_reader_get_int_value (reader);
	json_reader_end_member(reader);

	json_cursor = json_reader_read_member (reader, "font_size");
	settings->font_size = json_reader_get_int_value (reader);
	json_reader_end_member(reader);

	json_cursor = json_reader_read_member (reader, "font");
	g_strlcpy(settings->font, json_reader_get_string_value (reader), 256);
	json_reader_end_member(reader);

	json_cursor = json_reader_read_member (reader, "new_image_path");
	g_strlcpy(settings->new_image_path, json_reader_get_string_value (reader), 256);

	g_object_unref (parser);
	g_object_unref(reader);
	return settings;
}



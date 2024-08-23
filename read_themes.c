#include <stdio.h>
#include <stdlib.h>
#include <glib-object.h>
#include <json-glib/json-glib.h>
#include "headers.h"


/**
 * @file read_themes.c
 * @brief Reads the list of themes.
 */

/**
Reads the file of defined themes into a `GSList` of `Theme` structs. 
 */
GSList *read_themes(Settings *settings)
{
	JsonParser *parser;
	GError *error;
	Theme *theme;

	GSList * theme_list = NULL;
	parser = json_parser_new();
	error = NULL;
	json_parser_load_from_file(parser, "/home/abba/programming/c_programs/cartoon_balloon_gtk/themes.json", &error);
	if (error)
	{
		g_print("Unable to parse `%s': %s\n", "/home/abba/programming/c_programs/cartoon_balloon_gtk/themes.json", error->message);
		g_error_free(error);
		g_object_unref(parser);
		return NULL;
	}
	

	json_parser_get_root(parser);
	JsonReader *reader;
	reader = json_reader_new(json_parser_get_root(parser));
	gboolean success;
	
	success = json_reader_read_member(reader, "themes");

	success = json_reader_is_array(reader);

	gint number_of_themes = json_reader_count_elements (reader);

	for (gint i = 0; i<number_of_themes; i++) {
		theme = (Theme *)g_malloc(sizeof(Theme));
		success = json_reader_read_element (reader, i);
		success = json_reader_read_member(reader, "name");
		g_strlcpy(theme->name, json_reader_get_string_value(reader), 100);
		json_reader_end_member(reader);
		success = json_reader_read_member(reader, "properties");
		success = json_reader_read_member(reader, "text_color");
		g_strlcpy(theme->text_color, json_reader_get_string_value(reader), 100);
		json_reader_end_member(reader);
		success = json_reader_read_member(reader, "font");
		g_strlcpy(theme->font, json_reader_get_string_value(reader), 100);
		json_reader_end_member(reader);
		success = json_reader_read_member(reader, "font_size");
		theme->font_size = json_reader_get_int_value (reader);
		json_reader_end_member(reader);
		success = json_reader_read_member(reader, "stroke_width");
		theme->stroke_width = json_reader_get_int_value (reader);
		json_reader_end_member(reader);
		success = json_reader_read_member(reader, "balloon_fill_color");
		g_strlcpy(theme->balloon_fill_color, json_reader_get_string_value(reader), 100);
		json_reader_end_member(reader);
		success = json_reader_read_member(reader, "balloon_stroke_color");
		g_strlcpy(theme->balloon_stroke_color, json_reader_get_string_value(reader), 100);
	}

	success = json_reader_read_member(reader, "name");
	settings->new_width = json_reader_get_int_value(reader);



	/* Clean up */
	g_object_unref(parser);
	g_object_unref(reader);
	return theme_list;
}

#include <stdio.h>
#include <stdlib.h>
#include <glib-object.h>
#include <json-glib/json-glib.h>
#include "headers.h"


/**
 * @file read_themes.c
 * @brief Functions for reading and applying themes.
 */

/**
 * Reads the file of defined themes into a `GHashTable` of `Theme` structs. 
 */
void read_themes(User_Data *user_data)
{

	user_data->theme_hash  = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, g_free);

	JsonReader *reader = user_data->reader;
	
	GHashTable* theme_hash = user_data->theme_hash;

	gboolean success = FALSE;
	
	success = json_reader_read_member(reader, "themes");

	success = json_reader_is_array(reader);
	gint number_of_themes = json_reader_count_elements (reader);

	for (gint i = 0; i<number_of_themes; i++) {
		Theme *theme = (Theme *)g_malloc(sizeof(Theme));
		success = json_reader_read_element (reader, i);
		success = json_reader_read_member(reader, "name");
		g_strlcpy(theme->name, json_reader_get_string_value(reader), 100);
		json_reader_end_member(reader);
		
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
		json_reader_end_member(reader); /* From read_member inside balloon_stroke_color. */
		json_reader_end_element(reader); /* From read_element at element inside themes array . */

		success = g_hash_table_insert (theme_hash, theme->name, theme);
	}


}

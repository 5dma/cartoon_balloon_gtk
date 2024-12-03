#include <stdio.h>
#include <stdlib.h>
#include <glib-object.h>
#include <json-glib/json-glib.h>
#include <headers.h>


/**
 * @file read_themes.c
 * @brief Contains a function for reading the `themes` stanza in the settings file.
 */

/**
 * Reads the relevant settings file into a Themes struct. In particular, it creates a new Theme struct for every theme in the settings file and places that struct into a hash table. 
 */
void read_themes(User_Data *user_data, JsonReader *reader)
{

	/* The following object is freed in cleanup(). Each value in the hash is a Theme struct with no pointers, so they can safey be freed with the g_free function specified in the following statement. */
	user_data->theme_hash  = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, g_free);

	GHashTable* theme_hash = user_data->theme_hash;

	json_reader_read_member(reader, "themes");

	json_reader_is_array(reader);
	gint number_of_themes = json_reader_count_elements (reader);

	/* For each theme in the `themes` stanza, allocate a struct and place that struct in a hash table. */
	for (gint i = 0; i<number_of_themes; i++) {
		/* Each Theme object is freed in cleanup with g_hash_table_destroy(). */
		Theme *theme = (Theme *)g_malloc(sizeof(Theme));
		json_reader_read_element (reader, i);
		json_reader_read_member(reader, "name");
		g_strlcpy(theme->name, json_reader_get_string_value(reader), 100);
		json_reader_end_member(reader);
		
		json_reader_read_member(reader, "text_color");
		g_strlcpy(theme->text_color, json_reader_get_string_value(reader), 100);
		json_reader_end_member(reader);
		
		json_reader_read_member(reader, "font");
		g_strlcpy(theme->font_name, json_reader_get_string_value(reader), 100);
		json_reader_end_member(reader);
		
		json_reader_read_member(reader, "font_size");
		theme->font_size = json_reader_get_int_value (reader);
		json_reader_end_member(reader);
		
		json_reader_read_member(reader, "stroke_width");
		theme->stroke_width = json_reader_get_int_value (reader);
		json_reader_end_member(reader);
		
		json_reader_read_member(reader, "balloon_fill_color");
		g_strlcpy(theme->balloon_fill_color, json_reader_get_string_value(reader), 100);
		json_reader_end_member(reader);
		
		json_reader_read_member(reader, "balloon_stroke_color");
		g_strlcpy(theme->balloon_stroke_color, json_reader_get_string_value(reader), 100);
		json_reader_end_member(reader); /* From read_member inside balloon_stroke_color. */

		json_reader_read_member(reader, "rounded_corners");
		theme->rounded_corners = json_reader_get_boolean_value(reader);
		json_reader_end_member(reader); /* rounded corners. */

		json_reader_end_element(reader); /* From read_element at element inside themes array . */

		g_hash_table_insert (theme_hash, theme->name, theme);
	}


}

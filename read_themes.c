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
GHashTable *read_themes(Settings *settings)
{
	JsonParser *parser;
	GError *error;
	Theme *theme;

	//GHashTable* theme_hash = g_hash_table_new(g_str_hash, g_str_equal);
	GHashTable* theme_hash = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, g_free);
	
	parser = json_parser_new();
	error = NULL;
	json_parser_load_from_file(parser, "/home/abba/programming/c_programs/cartoon_balloon_gtk/configuration.json", &error);
	if (error)
	{
		g_print("Unable to parse `%s': %s\n", "/home/abba/programming/c_programs/cartoon_balloon_gtk/configuration.json", error->message);
		g_error_free(error);
		g_object_unref(parser);
		return NULL;
	}
	

	json_parser_get_root(parser);
	JsonReader *reader;
	reader = json_reader_new(json_parser_get_root(parser));
	gboolean success = FALSE;
	
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
		json_reader_end_member(reader); /* From read_member inside properties. */
		json_reader_end_member(reader); /* From read_member at outside properties*/
		json_reader_end_element(reader); /* From read_element at element inside themes array . */
		success = g_hash_table_insert (theme_hash, theme->name, theme);
	}

	/* Clean up */
	g_object_unref(parser);
	g_object_unref(reader);
	return theme_hash;
}

/**
* Retieves the requested theme from the theme_hash, and applies that theme's settings to the corresponding members of Settings. If the requested theme is not in the theme hash, the output falls back to the default theme. 
 */
void apply_theme(GHashTable * theme_hash, const Annotation * annotation, Settings **settings) {
	Theme * requested_theme = (Theme *)g_hash_table_lookup (theme_hash, annotation->theme);
	if (requested_theme == NULL) {
		return;
	}
	Settings * local_settings = *settings;
	g_strlcpy(local_settings->balloon_fill_color, requested_theme->balloon_fill_color, 8);
	g_strlcpy(local_settings->balloon_stroke_color, requested_theme->balloon_stroke_color, 8);
	g_strlcpy(local_settings->font, requested_theme->balloon_stroke_color, 256);
	g_strlcpy(local_settings->text_color, requested_theme->text_color, 8);
	local_settings->font_size = requested_theme->font_size;
	local_settings->stroke_width = requested_theme->stroke_width;
}
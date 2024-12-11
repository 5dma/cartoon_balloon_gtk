#include <glib/gstdio.h>
#include <headers.h>
#include <json-glib/json-glib.h>

/**
 * @file save_themes.c
 * @brief Contains a function for saving the `themes` stanza in the settings file.
 */


/**
* Formats into JSON the settings in the hash of Theme structs.
* @param key Key for the theme.
* @param value Pointer to the theme being saved.
* @param data Pointer to user data.
*/
void add_theme_object (gpointer key, gpointer value, gpointer data) {

	gchar *theme_name = (gchar *)key;
	Theme *theme = (Theme *)value;
	JsonBuilder *builder = (JsonBuilder *)data;

	json_builder_begin_object(builder);
	
	json_builder_set_member_name (builder, "name");
	json_builder_add_string_value(builder, theme_name);

	json_builder_set_member_name (builder, "text_color");
	json_builder_add_string_value(builder, theme->text_color);
	
	json_builder_set_member_name (builder, "font");
	json_builder_add_string_value(builder, theme->font_name);
	
	json_builder_set_member_name (builder, "font_size");
	json_builder_add_int_value(builder, (int) theme->font_size);
	
	json_builder_set_member_name (builder, "stroke_width");
	json_builder_add_int_value(builder, (int) theme->stroke_width);
	
	json_builder_set_member_name (builder, "balloon_fill_color");
	json_builder_add_string_value(builder, theme->balloon_fill_color);
		
	json_builder_set_member_name (builder, "balloon_stroke_color");
	json_builder_add_string_value(builder, theme->balloon_stroke_color);

	json_builder_set_member_name (builder, "rounded_corners");
	json_builder_add_boolean_value(builder,theme->rounded_corners);

	json_builder_end_object(builder);
}


/**
* Formats into JSON the settings in the hash of Theme structs. For each entry in the hash, calls add_theme_object() to format an individual theme.
* @param user_data Pointer to user data.
* @param builder Pointer to a `JsonBuilder`.
*/
void save_themes(User_Data *user_data, JsonBuilder *builder) {

	GHashTable* theme_hash = user_data->theme_hash;

	json_builder_set_member_name (builder, "themes");

	json_builder_begin_array (builder);
	
	g_hash_table_foreach (theme_hash, add_theme_object, builder);
	
	json_builder_end_array(builder); /* array */

}
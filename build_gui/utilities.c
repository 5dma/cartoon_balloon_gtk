#include <gtk/gtk.h>
#include <headers.h>
/**
 * @file utilities.c
 * @brief Contains utility functions required for building the GUI.
 */


/**
* Function for sorting the themes in the theme model. This sort function ensures that the entry (new) appears last.
*/
gint comparestrings (gconstpointer a, gconstpointer b, gpointer user_data) {
	GtkStringObject *object_a = (GtkStringObject *)a;
	GtkStringObject *object_b = (GtkStringObject *)b;
	const char *string_a = gtk_string_object_get_string(object_a);
	const char *string_b = gtk_string_object_get_string(object_b);

	/* Ensure that (new) is always at the end of the model */
	if (g_ascii_strcasecmp (string_a, NEW_THEME) == 0) {
		return -1;
	}

	if (g_ascii_strcasecmp (string_b, NEW_THEME) == 0) {
		return -1;
	}

	return g_ascii_strncasecmp (string_a, string_b, 10);
}



/**
 * Returns a pointer to the theme for the currently selected theme name in the Themes or Annotation tab.
 */
gpointer get_selected_theme_from_hash(User_Data *user_data, GtkWidget *dropdown_theme) {

	guint selected_item = gtk_drop_down_get_selected(GTK_DROP_DOWN(dropdown_theme));
	GListModel *model_theme = gtk_drop_down_get_model(GTK_DROP_DOWN(dropdown_theme));
	gpointer temp = g_list_model_get_item (G_LIST_MODEL(model_theme), selected_item);
	const char *selected_theme_name = gtk_string_object_get_string (GTK_STRING_OBJECT(temp));
	gpointer selected_theme = g_hash_table_lookup( user_data->theme_hash, selected_theme_name);	
	return selected_theme;
}

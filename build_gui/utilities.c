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

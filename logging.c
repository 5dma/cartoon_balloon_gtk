#include <glib.h>
#include <stdio.h>
#include <headers.h>
#include <stdarg.h>
/**
 * @file logging.c
 * @brief Contains macro definitions and functions pertaining to logging.
 */


/**
   \brief Maximal size of the possible literals for log levels `ERROR`, `CRITICAL`, etc. Required for performing `g_strlcpy` into the containing log message.
*/
#define LOG_LEVEL_LENGTH 50

/**
 * @file logging.c
 * @brief Functions for logging.
 */

/**
Receives a log level and text message, and outputs them along with a time stamp to the log file.
 */
void logger(GLogLevelFlags log_level, const gchar *message, User_Data *user_data) {
	
	FILE *log_file_pointer = user_data->configuration->log_file_pointer;

	if (log_file_pointer == NULL) {
		return;
	}

	gchar my_log_level[LOG_LEVEL_LENGTH + 1];

	switch (log_level) {
		case G_LOG_LEVEL_ERROR:
			g_strlcpy(my_log_level, "ERROR", LOG_LEVEL_LENGTH);
			break;
		case G_LOG_LEVEL_CRITICAL:
			g_strlcpy(my_log_level, "CRITICAL", LOG_LEVEL_LENGTH);
			break;
		case G_LOG_LEVEL_WARNING:
			g_strlcpy(my_log_level, "WARNING", LOG_LEVEL_LENGTH);
			break;
		case G_LOG_LEVEL_MESSAGE:
			g_strlcpy(my_log_level, "MESSAGE", LOG_LEVEL_LENGTH);
			break;
		case G_LOG_LEVEL_INFO:
			g_strlcpy(my_log_level, "INFO", LOG_LEVEL_LENGTH);
			break;
		case G_LOG_LEVEL_DEBUG:
			g_strlcpy(my_log_level, "DEBUG", LOG_LEVEL_LENGTH);
			break;
		default:
			g_strlcpy(my_log_level, "MESSAGE", LOG_LEVEL_LENGTH);
			break;
	}

    GDateTime *date_time = g_date_time_new_now_local();
    gchar *date_time_string = g_date_time_format(date_time, "%H:%M:%S");
	fprintf (log_file_pointer, "%-8s %s %s\n", my_log_level, date_time_string, message);
	fflush (log_file_pointer);
	g_free(date_time_string);
	g_date_time_unref(date_time);
}

/**
Opens the log file and returns the pointer.
 */
FILE *get_log_file_pointer(Configuration *configuration) {
	FILE *file_ptr = fopen (configuration ->log_file_path, "a");
	if (file_ptr == NULL) {
		g_print("Could not open log file, so no messages are logged\n");
	}
	return file_ptr;

}
/**
* Constructs a log message describing a theme.
*/
void print_theme(gpointer key, gpointer value, gpointer user_data) {

	GStrvBuilder *message_builder = (GStrvBuilder *) user_data;
	gchar *theme_name = (gchar *) key;
	Theme *theme = (Theme *) value;

	gchar *current_line;
	current_line = g_strdup_printf ("  %s:", theme_name);
	g_strv_builder_add (message_builder,current_line);
	g_free(current_line);
	
	current_line = g_strdup_printf ("%-23s: %s", "    text_color", theme->text_color);
	g_strv_builder_add (message_builder,current_line);
	g_free(current_line);
	
	current_line = g_strdup_printf ("%-23s: %s", "    font", theme->font_name);
	g_strv_builder_add (message_builder,current_line);
	g_free(current_line);
	
	current_line = g_strdup_printf ("%-23s: %ld", "    font_size", theme->font_size);
	g_strv_builder_add (message_builder,current_line);
	g_free(current_line);

	current_line = g_strdup_printf ("%-23s: %ld", "    stroke_width", theme->stroke_width);
	g_strv_builder_add (message_builder,current_line);
	g_free(current_line);

	current_line = g_strdup_printf ("%-23s: %s", "    balloon_fill_color", theme->balloon_fill_color);
	g_strv_builder_add (message_builder,current_line);
	g_free(current_line);

	current_line = g_strdup_printf ("%-23s: %s", "    balloon_stroke_color", theme->balloon_stroke_color);
	g_strv_builder_add (message_builder,current_line);
	g_free(current_line);
}

/**
Writes to the log file the current settings.
 */
void log_configuration_values(User_Data *user_data) {
	Configuration *configuration = user_data->configuration;
	GStrvBuilder *message_builder = g_strv_builder_new ();
	g_strv_builder_add (message_builder,"Read settings values:");
	
	/* Writes configuration settigngs. */
	g_strv_builder_add (message_builder,"Configuration:");

	gchar *current_line;
	current_line = g_strdup_printf ("%-23s: %ld", "  max_annotation_length", configuration->max_annotation_length);
	g_strv_builder_add (message_builder,current_line);
	g_free(current_line);

	current_line = g_strdup_printf ("%-23s: %ld", "  padding", configuration->padding);
	g_strv_builder_add (message_builder,current_line);
	g_free(current_line);

	current_line = g_strdup_printf ("%-23s: %ld", "  elevation", configuration->elevation);
	g_strv_builder_add (message_builder,current_line);
	g_free(current_line);

	current_line = g_strdup_printf ("%-23s: %ld", "  space", configuration->space);
	g_strv_builder_add (message_builder,current_line);
	g_free(current_line);

	current_line = g_strdup_printf ("%-23s: %ld", "  top_margin", configuration->top_margin);
	g_strv_builder_add (message_builder,current_line);
	g_free(current_line);

	current_line = g_strdup_printf ("%-23s: %s", "  log_file_path", configuration->log_file_path);
	g_strv_builder_add (message_builder,current_line);
	g_free(current_line);

	current_line = g_strdup_printf ("%-23s: %s", "  new_image_path", configuration->new_image_path);
	g_strv_builder_add (message_builder,current_line);
	g_free(current_line);

	/* Writes annotation settigngs. */

	Annotation *annotation = user_data->annotation;
	Gui_Data_Annotation *gui_data_annotation = user_data->gui_data->gui_data_annotation;

	g_strv_builder_add (message_builder,"\nAnnotation:");

	const gchar *input_image = gtk_editable_get_text (GTK_EDITABLE( gui_data_annotation->entry_input_image));
	current_line = g_strdup_printf ("%-23s: %s", "  input_image", input_image);
	g_strv_builder_add (message_builder,current_line);
	g_free(current_line);

	guint text_bottom_left_x = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(gui_data_annotation->spin_text_bottom_left_x));
	guint text_bottom_left_y = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(gui_data_annotation->spin_text_bottom_left_y));
	current_line = g_strdup_printf ("%-23s: x: %ld, y: %ld", "  text_bottom_left",text_bottom_left_x, text_bottom_left_y);
	g_strv_builder_add (message_builder,current_line);
	g_free(current_line);

	guint vertex_x = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(gui_data_annotation->spin_vertex_x));
	guint vertex_y = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(gui_data_annotation->spin_vertex_y));
	current_line = g_strdup_printf ("%-23s: x: %ld, y: %ld", "  vertex",vertex_x, vertex_y);
	g_strv_builder_add (message_builder,current_line);
	g_free(current_line);


	guint new_width = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(gui_data_annotation->spin_new_width));
	current_line = g_strdup_printf ("%-23s: %ld", "  new width", new_width);
	g_strv_builder_add (message_builder,current_line);
	g_free(current_line);

	const gchar *text_string = gtk_editable_get_text (GTK_EDITABLE( gui_data_annotation->entry_text_string));
	current_line = g_strdup_printf ("%-23s: %s", "  text_string", text_string);
	g_strv_builder_add (message_builder,current_line);
	g_free(current_line);

	gpointer selected_theme = get_selected_theme_from_hash(user_data, gui_data_annotation->dropdown_theme);
	const gchar *theme_name = ((Theme *)selected_theme)->name;
	current_line = g_strdup_printf ("%-23s: %s", "  theme", theme_name);
	g_strv_builder_add (message_builder,current_line);
	g_free(current_line);

	/* Writes theme settings. */

	GHashTable *theme_hash = user_data->theme_hash;
	g_strv_builder_add (message_builder,"\nThemes:");
	g_hash_table_foreach (theme_hash,  print_theme, message_builder);

	/* Complete the message and send to the logger */
	GStrv message_vector = g_strv_builder_end (message_builder);
	gchar *final_message = g_strjoinv("\n", message_vector);
	logger(G_LOG_LEVEL_INFO,final_message, user_data);
	
	/* Cleanup */
	g_free(final_message);
	g_strv_builder_unref(message_builder);
}

/**
 * Updates the text in the status bar.
 */
void populate_status_bar(GtkWidget *status_bar, const gchar *formatting_string, ...) {

	va_list pargs;
	va_start(pargs, formatting_string);

	gchar *status_line;
	status_line = g_strdup_vprintf (formatting_string, pargs);
	
	GtkEntryBuffer *buffer = gtk_entry_get_buffer (GTK_ENTRY(status_bar));

	gtk_entry_buffer_set_text(buffer, status_line, -1);
	
	g_free(status_line);
	va_end(pargs);
}
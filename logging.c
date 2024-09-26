#include <glib.h>
#include <stdio.h>
#include "headers.h"
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
FILE * get_log_file_pointer(Configuration * configuration) {
	FILE * file_ptr = fopen (configuration ->log_file_path, "a");
	if (file_ptr == NULL) {
		g_print("Could not open log file, so no messages are logged\n");
	}
	return file_ptr;

}

void log_configuration_values(User_Data *user_data) {
	Configuration *configuration = user_data->configuration;
	GStrvBuilder *message_builder = g_strv_builder_new ();
	g_strv_builder_add (message_builder,"Read settings values:");
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


	Annotation *annotation = user_data->annotation;
	g_strv_builder_add (message_builder,"Annotation:");

	current_line = g_strdup_printf ("%-23s: %s", "  input_image", annotation->input_image);
	g_strv_builder_add (message_builder,current_line);
	g_free(current_line);

	current_line = g_strdup_printf ("%-23s: x: %ld, y: %ld", "  text_bottom_left",annotation->text_bottom_left.x, annotation->text_bottom_left.y);
	g_strv_builder_add (message_builder,current_line);
	g_free(current_line);

	current_line = g_strdup_printf ("%-23s: x: %ld, y: %ld", "  vertex",annotation->vertex.x, annotation->vertex.y);
	g_strv_builder_add (message_builder,current_line);
	g_free(current_line);


	current_line = g_strdup_printf ("%-23s: %ld", "  new width", annotation->new_width);
	g_strv_builder_add (message_builder,current_line);
	g_free(current_line);

	current_line = g_strdup_printf ("%-23s: %s", "  text_string", annotation->text_string);
	g_strv_builder_add (message_builder,current_line);
	g_free(current_line);

	current_line = g_strdup_printf ("%-23s: %s", "  theme", annotation->theme);
	g_strv_builder_add (message_builder,current_line);
	g_free(current_line);

	GStrv message_vector = g_strv_builder_end (message_builder);
	gchar *final_message = g_strjoinv("\n", message_vector);
	logger(G_LOG_LEVEL_INFO,final_message, user_data);
	g_free(final_message);
	g_strv_builder_unref(message_builder);
}
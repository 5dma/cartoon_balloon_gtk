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
	const int key_field_length = 21;
	g_autoptr(GStrvBuilder) configuration_message = g_strv_builder_new ();
	g_strv_builder_add (configuration_message,"Read settings values:");
	g_strv_builder_add (configuration_message,"Configuration:");
	g_auto(GStrv) final_message = g_strv_builder_end (configuration_message);
	gchar *final_barf = g_strjoinv("\n", final_message);
	//final_barf = g_strjoin("\n", "OMG", "BARF", NULL);

	logger(G_LOG_LEVEL_INFO,final_barf, user_data);
}
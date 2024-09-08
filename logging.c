#include <glib.h>
#include <stdio.h>
#include "headers.h"
#define LOG_LEVEL_LENGTH 50



void logger(GLogLevelFlags log_level, const gchar * message, gpointer user_data) {
	Settings * settings = (Settings *) user_data;

	if (settings->log_file_pointer == NULL) {
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
	fprintf (settings->log_file_pointer, "%-8s %s %s\n", my_log_level, date_time_string, message);
	fflush (settings->log_file_pointer);
	g_free(date_time_string);
	g_date_time_unref(date_time);
}

FILE * get_log_file_pointer(Settings * settings) {
	FILE * file_ptr = fopen (settings ->log_file_path, "a");
	if (file_ptr == NULL) {
		g_print("Could not open log file, so no messages are logged\n");
	}
	return file_ptr;

}

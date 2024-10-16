#include "glib.h"
#include "headers.h"
/**
 * @file cleanup.c
 * @brief Frees memory.
 */

/**
  Frees memory in the User_Data instance.
 */
void cleanup(User_Data *user_data) {
	

	g_object_unref(user_data->parser);
	g_object_unref(user_data->reader);
	g_object_unref(user_data->annotation->crosshair_cursor);

	g_hash_table_destroy(user_data->theme_hash);
	fclose(user_data->configuration->log_file_pointer);

	g_free(user_data->gui_data->gui_data_configuration);
	g_free(user_data->gui_data->gui_data_annotation);
	g_free(user_data->gui_data->gui_data_theme);
	
	g_free(user_data->gui_data);
	g_free(user_data->configuration);
	g_free(user_data->annotation);
	g_free(user_data->theme_preview);
	g_free(user_data);
}

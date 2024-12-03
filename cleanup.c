#include <glib.h>
#include <headers.h>
/**
 * @file cleanup.c
 * @brief Contains a function for freeing memory.
 */

/**
  Frees memory in the User_Data instance.
 */
void cleanup(User_Data *user_data, gboolean detailed)
{

	if (detailed)
	{
		g_object_unref(user_data->annotation->crosshair_cursor);
		g_object_unref(user_data->gui_data->gui_data_annotation->file_filter);
		g_object_unref(user_data->gui_data->provider);

		g_hash_table_destroy(user_data->theme_hash);
		fclose(user_data->configuration->log_file_pointer);
	}

	g_list_store_remove_all(user_data->list_store_themes);
	g_object_unref(user_data->list_store_themes);

	g_free(user_data->gui_data->gui_data_configuration);
	g_free(user_data->gui_data->gui_data_annotation);
	g_free(user_data->gui_data->gui_data_theme);

	g_free(user_data->gui_data);
	g_free(user_data->configuration);
	g_free(user_data->annotation);
	g_free(user_data->text_analysis);
	g_free(user_data->theme_geometry);
	g_free(user_data);
}

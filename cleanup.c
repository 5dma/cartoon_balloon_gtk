#include <glib.h>
#include <headers.h>
/**
 * @file cleanup.c
 * @brief Contains a function for freeing memory.
 */

/**
  Frees memory of string objects in the list store of theme names.
  @param list_store_themes Pointer to the `GListStore` for which we are freeing the entries' memory.
 */
void free_themes_in_list_store(GListStore * list_store_themes) {

	guint number_themes = g_list_model_get_n_items ( G_LIST_MODEL(list_store_themes));
	for (int i=0; i<number_themes; i++) {
		GObject *theme_object = g_list_model_get_object (G_LIST_MODEL(list_store_themes), 0);
		g_object_unref(GTK_STRING_OBJECT(theme_object));
	}
}


/**
  Frees memory in the User_Data instance.
  @param user_data Pointer to user data.
  @param detailed If `TRUE`, all memory has been allocated and this function frees it as well. If `FALSE`, only the preliminary memory was allocated at application start.
  \sa allocate_structures()
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

	free_themes_in_list_store(user_data->list_store_themes);
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

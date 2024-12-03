#include <glib/gstdio.h>
#include <headers.h>
#include <read_save.h>
/**
 * @file save_files.c
 * @brief Contains the parent function for saving settings in JSON format to disk.
*/

/**
 * Saves settings to disk in JSON format. See also
 * - save_configuration()
 * - save_annotation()
 * - save_themes()
*/
void save_files(User_Data *user_data) {

	GError *error;

	/* Copy the settings file to a backup file. */
	g_rename (CONFIG_FILE, CONFIG_FILE_BACKUP);

	JsonBuilder *builder = json_builder_new ();
	json_builder_begin_object (builder);
	save_configuration(user_data, builder);
	save_annotation(user_data, builder);
	save_themes(user_data, builder);

	json_builder_end_object (builder); /* root */
	
	JsonNode *root = json_builder_get_root (builder);

	JsonGenerator *generator = json_generator_new ();
	json_generator_set_root (generator, root);
	json_generator_to_file (generator, CONFIG_FILE, &error);

	if (error) {
		g_print("Unable to save the new configuration file.\n%s\nYou should rename the backup %s to %s\n", error->message, CONFIG_FILE_BACKUP, CONFIG_FILE);
		g_error_free(error);
	}
	g_object_unref(generator);
	// Unreffing root gives an error, not sure why as the caller takes possession.
	g_object_unref(builder);
}


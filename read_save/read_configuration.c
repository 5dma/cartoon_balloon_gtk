#include <glib-object.h>
#include <json-glib/json-glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <headers.h>

/**
 * @file read_configuration.c
 * @brief Contains a function for reading the `configuration` stanza in the settings file.
 */

/**
Reads the relevant settings file into a Configuration struct. The settings in this struct file are relatively static: they can apply to multiple images and themes. Also calls get_log_file_pointer() to open the log file.
* @param user_data Pointer to user data.
* @param reader Pointer to the currently active JSON object.
*/
void read_configuration(User_Data *user_data, JsonReader *reader) {

	Configuration *configuration = user_data->configuration;
	Gui_Data_Configuration *gui_data_configuration = user_data->gui_data->gui_data_configuration;
	gint64 configuration_value;

	json_reader_read_member(reader, "configuration");

	json_reader_read_member(reader, "max_annotation_length");
	configuration_value = json_reader_get_int_value(reader);
	if (configuration_value == 0) {
		configuration_value = 256;
	}
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(gui_data_configuration->spin_max_annotation_length), configuration_value);
	json_reader_end_member(reader);

	json_reader_read_member(reader, "padding");
	configuration_value = json_reader_get_int_value(reader);
	if (configuration_value == 0) {
		configuration_value = 5;
	}
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(gui_data_configuration->spin_padding), configuration_value);
	json_reader_end_member(reader);


	json_reader_read_member(reader, "elevation");
	configuration_value = json_reader_get_int_value(reader);
	if (configuration_value == 0) {
		configuration_value = 5;
	}
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(gui_data_configuration->spin_elevation), configuration_value);
	json_reader_end_member(reader);

	json_reader_read_member(reader, "space");
	configuration_value = json_reader_get_int_value(reader);
	if (configuration_value == 0) {
		configuration_value = 5;
	}
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(gui_data_configuration->spin_space), configuration_value);
	json_reader_end_member(reader);

	json_reader_read_member(reader, "top_margin");
	configuration_value = json_reader_get_int_value(reader);
	if (configuration_value == 0) {
		configuration_value = 10;
	}
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(gui_data_configuration->spin_top_margin), configuration_value);
	json_reader_end_member(reader);

	json_reader_read_member(reader, "log_file_path");
	g_strlcpy(configuration->log_file_path, json_reader_get_string_value(reader), 256);
	json_reader_end_member(reader);

	json_reader_read_member(reader, "new_image_path");
	g_strlcpy(configuration->new_image_path, json_reader_get_string_value(reader), 256);
	json_reader_end_member(reader);

	json_reader_read_member(reader, "rounding_radius");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(gui_data_configuration->spin_rounding_radius), json_reader_get_int_value (reader));
	json_reader_end_member(reader);

	json_reader_end_member(reader); /* configuration stanza */

	configuration->log_file_pointer = get_log_file_pointer(configuration);

}

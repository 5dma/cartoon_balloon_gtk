#include <glib/gstdio.h>
#include <headers.h>
#include <json-glib/json-glib.h>

/**
 * @file save_configuration.c
 * @brief Contains a function for saving the `configuration` stanza in the settings file.
 */

/**
* Formats into JSON the settings in the Configuration struct.
*/
void save_configuration(User_Data *user_data, JsonBuilder *builder) {

	Configuration *configuration = user_data->configuration;
	Gui_Data_Configuration *gui_data_configuration = user_data->gui_data->gui_data_configuration;

	json_builder_set_member_name (builder, "configuration");

	json_builder_begin_object (builder);
	
	double config_value  = gtk_spin_button_get_value (GTK_SPIN_BUTTON(gui_data_configuration->spin_max_annotation_length));
 	json_builder_set_member_name (builder, "max_annotation_length");
	json_builder_add_int_value(builder, (guint64) config_value);

	config_value  = gtk_spin_button_get_value (GTK_SPIN_BUTTON(gui_data_configuration->spin_padding));
	json_builder_set_member_name (builder, "padding");
	json_builder_add_int_value(builder, (guint64) config_value);

	config_value  = gtk_spin_button_get_value (GTK_SPIN_BUTTON(gui_data_configuration->spin_elevation));
	json_builder_set_member_name (builder, "elevation");
	json_builder_add_int_value(builder, (guint64) config_value);

	config_value  = gtk_spin_button_get_value (GTK_SPIN_BUTTON(gui_data_configuration->spin_space));
	json_builder_set_member_name (builder, "space");
	json_builder_add_int_value(builder, (guint64) config_value);

	config_value  = gtk_spin_button_get_value (GTK_SPIN_BUTTON(gui_data_configuration->spin_top_margin));
	json_builder_set_member_name (builder, "top_margin");
	json_builder_add_int_value(builder, (guint64) config_value);

	config_value  = gtk_spin_button_get_value (GTK_SPIN_BUTTON(gui_data_configuration->spin_rounding_radius));
	json_builder_set_member_name (builder, "rounding_radius");
	json_builder_add_int_value(builder, (guint64) config_value);

	json_builder_set_member_name (builder, "log_file_path");
	json_builder_add_string_value(builder, configuration->log_file_path);

	json_builder_set_member_name (builder, "new_image_path");
	json_builder_add_string_value(builder, configuration->new_image_path);

	json_builder_end_object (builder); /* configuration */


}
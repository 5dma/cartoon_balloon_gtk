#include <glib/gstdio.h>
#include <headers.h>


/**
 * @file save_configuration.c
 * @brief Places a configuration's settings into a passed JSON builder.
 */

/**
 * Places configuration settings into a JSON structure for later save to disk. See also save_files().
 */
void save_configuration(User_Data *user_data, JsonBuilder *builder) {

	Configuration *configuration = user_data->configuration;

	json_builder_set_member_name (builder, "configuration");

	json_builder_begin_object (builder);
	
	json_builder_set_member_name (builder, "max_annotation_length");
	json_builder_add_int_value(builder, configuration->max_annotation_length);

	json_builder_set_member_name (builder, "padding");
	json_builder_add_int_value(builder, configuration->padding);

	json_builder_set_member_name (builder, "elevation");
	json_builder_add_int_value(builder, configuration->elevation);

	json_builder_set_member_name (builder, "space");
	json_builder_add_int_value(builder, configuration->space);

	json_builder_set_member_name (builder, "top_margin");
	json_builder_add_int_value(builder, configuration->top_margin);

	json_builder_set_member_name (builder, "log_file_path");
	json_builder_add_string_value(builder, configuration->log_file_path);

	json_builder_set_member_name (builder, "new_image_path");
	json_builder_add_string_value(builder, configuration->new_image_path);

	json_builder_end_object (builder); /* configuration */


}
#include <glib/gstdio.h>
#include "headers.h"

void save_annotation(User_Data *user_data, JsonBuilder *builder) {

	Annotation *annotation = user_data->annotation;

	json_builder_set_member_name (builder, "annotation");

	json_builder_begin_object (builder);
	

	json_builder_set_member_name (builder, "input_image");
	json_builder_add_string_value(builder, annotation->input_image);


	json_builder_set_member_name (builder, "text_bottom_left");
	json_builder_begin_object (builder); /* text_bottom_left*/
	json_builder_set_member_name (builder, "x");
	json_builder_add_int_value(builder, (int) annotation->text_bottom_left.x);
	json_builder_set_member_name (builder, "y");
	json_builder_add_int_value(builder, (int) annotation->text_bottom_left.y);
	json_builder_end_object (builder); /* text_bottom_left */


	json_builder_set_member_name (builder, "vertex");
	json_builder_begin_object (builder); /* vertex*/
	json_builder_set_member_name (builder, "x");
	json_builder_add_int_value(builder, (int) annotation->vertex.x);
	json_builder_set_member_name (builder, "y");
	json_builder_add_int_value(builder, (int) annotation->vertex.y);
	json_builder_end_object (builder); /* vertex */


	json_builder_set_member_name (builder, "new_width");
	json_builder_add_int_value(builder, (int) annotation->new_width);

	json_builder_set_member_name (builder, "text_string");
	json_builder_add_string_value(builder, annotation->text_string);


	json_builder_set_member_name (builder, "theme");
	json_builder_add_string_value(builder, annotation->theme);


	json_builder_end_object (builder); /* annotation */


}
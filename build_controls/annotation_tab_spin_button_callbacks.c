#include <headers.h>
/**
 * @file annotation_tab_spin_button_callbacks.c
 * @brief Contains callback functions for spin buttons in the Annotations tab. (The functions in this file need to be replaced by removing extraneous fields in the Annotation structure.)
 */


/**
This function is fired when any of the five spinners on the Annotations tab is changed. The function checks which spinner was changed, and updates the corresponding field in the Annotation structure.
*/
void on_annotation_spinner_changed (GtkSpinButton* self, gpointer data) {
	g_print("Changed!\n");
	User_Data *user_data = (User_Data *)data;
	Annotation *annotation = user_data->annotation;
	Gui_Data_Annotation *gui_data_annotation =  user_data->gui_data->gui_data_annotation;
	uintptr_t int_pointer = (uintptr_t) self;
	guint64 new_value = (gint64) gtk_spin_button_get_value(self);

	if (int_pointer == (uintptr_t) gui_data_annotation->spin_text_bottom_left_x) {
		annotation->text_bottom_left.x = new_value;
		return;
	}
	if (int_pointer == (uintptr_t) gui_data_annotation->spin_text_bottom_left_y) {
		annotation->text_bottom_left.y = new_value;
		return;
	}
	if (int_pointer == (uintptr_t) gui_data_annotation->spin_vertex_x) {
		annotation->vertex.x = new_value;
		return;
	}
	if (int_pointer == (uintptr_t) gui_data_annotation->spin_vertex_y) {
		annotation->vertex.y = new_value;
		return;
	}
	if (int_pointer == (uintptr_t) gui_data_annotation->spin_new_width) {
		annotation->new_width = new_value;
		return;
	}
}
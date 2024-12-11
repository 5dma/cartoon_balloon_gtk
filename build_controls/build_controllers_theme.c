#include <headers.h>
#include <rgb_hex.h>
#include <controls.h>
/**
 * @file build_controllers_theme.c
 * @brief Contains a function for assigning callbacks to controls in the **Themes** tab.
 */


/**
* Assigns callbacks to controls in the **Themes** tab. For a description of the callbacks, see build_controls/theme_tab_callbacks.c.
* @param user_data Pointer to user data.
 */
void build_controllers_theme(User_Data *user_data)
{

	Theme_Geometry *theme_geometry = user_data->theme_geometry;
	theme_geometry->balloon_top_left.x = 20;
	theme_geometry->balloon_top_left.y = 15;
	theme_geometry->balloon_bottom_right.x = 158;
	theme_geometry->balloon_bottom_right.y = 90;

	const int midpoint_horizontal = (theme_geometry->balloon_bottom_right.x - theme_geometry->balloon_top_left.x) / 2 + theme_geometry->balloon_top_left.x;
	const int midpoint_vertical = (theme_geometry->balloon_bottom_right.y - theme_geometry->balloon_top_left.y) / 2 + theme_geometry->balloon_top_left.y;
	const int elevation = theme_geometry->balloon_bottom_right.y - 10;

	theme_geometry->vertex_left.x = midpoint_horizontal - 10;
	theme_geometry->vertex_left.y = elevation;

	theme_geometry->vertex_bottom.x = midpoint_horizontal;
	theme_geometry->vertex_bottom.y = theme_geometry->balloon_bottom_right.y + 20;

	theme_geometry->vertex_right.x = midpoint_horizontal + 10;
	theme_geometry->vertex_right.y = elevation;

	theme_geometry->text_start.x = midpoint_horizontal - 20;
	theme_geometry->text_start.y = midpoint_vertical;

	Gui_Data_Theme *gui_data_theme = user_data->gui_data->gui_data_theme;
	gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(gui_data_theme->drawing_balloon), draw_theme, user_data, NULL);

	g_signal_connect(gui_data_theme->dropdown_theme, "notify::selected", G_CALLBACK(theme_selection_changed), user_data);
	g_signal_connect(gui_data_theme->btn_font_name_picker, "font-set", G_CALLBACK(save_selected_font_to_theme), user_data);
	g_signal_connect(gui_data_theme->spin_stroke_width, "value-changed", G_CALLBACK(save_selected_stroke_width_to_theme), user_data);

	/* Create a controller for exiting the new theme field. */
	GtkEventController *new_theme_controller_focus = gtk_event_controller_focus_new();
	g_signal_connect(new_theme_controller_focus, "leave", G_CALLBACK(new_theme), user_data);
	gtk_widget_add_controller(gui_data_theme->entry_new_theme, new_theme_controller_focus);

	g_signal_connect(gui_data_theme->entry_new_theme, "changed", G_CALLBACK(get_new_theme_name), user_data);
	g_signal_connect(gui_data_theme->btn_delete, "clicked", G_CALLBACK(delete_theme), user_data);
}

#include "../headers.h"

/**
 * @file build_controllers_theme.c
 * @brief Contains functions for adding callbacks to the themes window.
 */

void theme_selection_changed(GObject *self, GParamSpec *pspec, gpointer data) {
	User_Data *user_data = (User_Data *)data;
	Gui_Data_Theme *gui_data_theme = user_data->gui_data->gui_data_theme;

	guint selected_item = gtk_drop_down_get_selected(GTK_DROP_DOWN(gui_data_theme->dropdown_theme));

	GListModel *model_theme = gtk_drop_down_get_model(GTK_DROP_DOWN(gui_data_theme->dropdown_theme));
	const char *selected_theme_name = gtk_string_list_get_string(GTK_STRING_LIST(model_theme), selected_item);

	int new_compare = g_strcmp0(NEW_THEME, selected_theme_name);
	if (new_compare == 0) {
		gtk_widget_set_sensitive(gui_data_theme->entry_new_theme, TRUE);
		gtk_widget_grab_focus(gui_data_theme->entry_new_theme);
	} else {
		gtk_widget_set_sensitive(gui_data_theme->entry_new_theme, FALSE);
		Theme *theme = (Theme *)g_hash_table_lookup(user_data->theme_hash, selected_theme_name);

		GtkEntryBuffer *entry_buffer = gtk_entry_get_buffer(GTK_ENTRY(gui_data_theme->entry_font_name));
		gtk_entry_buffer_set_text(entry_buffer, theme->font, -1);

		entry_buffer = gtk_entry_get_buffer(GTK_ENTRY(gui_data_theme->entry_font_color));
		gtk_entry_buffer_set_text(entry_buffer, theme->text_color, -1);

		gtk_spin_button_set_value(GTK_SPIN_BUTTON(gui_data_theme->spin_font_size), theme->font_size);

		entry_buffer = gtk_entry_get_buffer(GTK_ENTRY(gui_data_theme->entry_fill_color));
		gtk_entry_buffer_set_text(entry_buffer, theme->balloon_fill_color, -1);

		entry_buffer = gtk_entry_get_buffer(GTK_ENTRY(gui_data_theme->entry_stroke_color));
		gtk_entry_buffer_set_text(entry_buffer, theme->balloon_stroke_color, -1);

		gtk_spin_button_set_value(GTK_SPIN_BUTTON(gui_data_theme->spin_stroke_width), theme->stroke_width);
	}
}

double scaled_rgb(int input) {
	return (double)input / 255;
}

void draw_theme(GtkDrawingArea *drawing_area, cairo_t *cr,
				int width,
				int height,
				gpointer data) {
	g_print("Draw\n");

	User_Data *user_data = (User_Data *)data;
	Theme_Preview *theme_preview = user_data->theme_preview;


	/* Draw balloon and fill */

	cairo_set_source_rgb(cr, theme_preview->fill_rgb[0] ,theme_preview->fill_rgb[1], theme_preview->fill_rgb[2]);
	cairo_set_line_width(cr, 5);
	cairo_new_path(cr);
	cairo_move_to(cr, theme_preview->balloon_top_left.x, theme_preview->balloon_top_left.y);
	cairo_line_to(cr, theme_preview->balloon_bottom_right.x, theme_preview->balloon_top_left.y);
	cairo_line_to(cr, theme_preview->balloon_bottom_right.x, theme_preview->balloon_bottom_right.y);
	cairo_line_to(cr, theme_preview->balloon_top_left.x, theme_preview->balloon_bottom_right.y);
	cairo_close_path(cr);
	cairo_fill_preserve(cr);

	/* Stroke balloon */


	cairo_set_source_rgb(cr, theme_preview->stroke_rgb[0] ,theme_preview->stroke_rgb[1], theme_preview->stroke_rgb[2]);
	cairo_stroke(cr);

	/* Draw vertex and fill */


	cairo_set_source_rgb(cr, theme_preview->fill_rgb[0] ,theme_preview->fill_rgb[1], theme_preview->fill_rgb[2]);

	cairo_move_to(cr,theme_preview->vertex_left.x,theme_preview->vertex_left.y);
	cairo_line_to(cr, theme_preview->vertex_bottom.x,theme_preview->vertex_bottom.y);
	cairo_line_to(cr, theme_preview->vertex_right.x,theme_preview->vertex_right.y);
	cairo_fill_preserve(cr);

	/* Stroke vertex */
	cairo_set_source_rgb(cr, theme_preview->stroke_rgb[0] ,theme_preview->stroke_rgb[1], theme_preview->stroke_rgb[2]);
	cairo_stroke(cr);

	/* Add text */
	cairo_select_font_face(cr, "sans-serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(cr, 15);
	cairo_move_to(cr, theme_preview->text_start.x, theme_preview->text_start.y);
	cairo_show_text(cr, "THEME");
}

/**
Assigns callbacks to controls in the theme tab
 */
void build_controllers_theme(User_Data *user_data) {


	Theme_Preview *theme_preview = user_data->theme_preview;
	theme_preview->balloon_top_left.x = 20;
	theme_preview->balloon_top_left.y = 15;
	theme_preview->balloon_bottom_right.x = 158;
	theme_preview->balloon_bottom_right.y = 90;

	const int midpoint_horizontal = (theme_preview->balloon_bottom_right.x - theme_preview->balloon_top_left.x) / 2 + theme_preview->balloon_top_left.x;
	const int midpoint_vertical = (theme_preview->balloon_bottom_right.y - theme_preview->balloon_top_left.y) / 2 + theme_preview->balloon_top_left.y;
	const int elevation = theme_preview->balloon_bottom_right.y - 10;
	
	theme_preview->vertex_left.x = midpoint_horizontal - 10;
	theme_preview->vertex_left.y = elevation;

	theme_preview->vertex_bottom.x = midpoint_horizontal;
	theme_preview->vertex_bottom.y = theme_preview->balloon_bottom_right.y + 20;

	theme_preview->vertex_right.x = midpoint_horizontal + 10;
	theme_preview->vertex_right.y = elevation;

	theme_preview->fill_rgb[0]= 0.44;
	theme_preview->fill_rgb[1]= 0.62;
	theme_preview->fill_rgb[2]= 0.81;

	theme_preview->stroke_rgb[0]= 0.02;
	theme_preview->stroke_rgb[1]= 0.0;
	theme_preview->stroke_rgb[2]= 0.98;

	theme_preview->text_start.x = midpoint_horizontal - 20;
	theme_preview->text_start.y = midpoint_vertical;

	Gui_Data_Theme *gui_data_theme = user_data->gui_data->gui_data_theme;

	g_signal_connect(gui_data_theme->dropdown_theme, "notify::selected", G_CALLBACK(theme_selection_changed), user_data);

	gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(gui_data_theme->drawing_balloon), draw_theme, user_data, NULL);
}

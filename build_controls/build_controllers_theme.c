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

double scaled_rgb (int input) {
	return (double) input / 255;
}

void draw_theme(GtkDrawingArea* drawing_area, cairo_t* cr,
  int width,
  int height,
  gpointer user_data) {
	g_print("Draw\n");

	int left = 20;
	int top = 15;
	int right = 158;
	int bottom = 90;
	int elevation = bottom - 10;
	int midpoint = (right - left) / 2 + left;
	int vertex_left = midpoint - 10;
	int vertex_right = midpoint + 10;
	int vertex_bottom = bottom + 30;

double barf1 = scaled_rgb (114);
double barf2 = scaled_rgb (159);
double barf3 = scaled_rgb (207);

	cairo_set_source_rgb (cr,barf1, barf2, barf3);
	cairo_set_line_width(cr, 5);
	cairo_new_path(cr);
	cairo_move_to(cr,left, top);
	cairo_line_to(cr, right, top);
	cairo_line_to(cr, right, bottom);
	cairo_line_to(cr, left, bottom);
	cairo_close_path(cr);
	cairo_fill_preserve (cr);
	 barf1 = scaled_rgb (51);
barf2 = scaled_rgb (71);
barf3 = scaled_rgb (230);



	cairo_set_source_rgb (cr,barf1, barf2, barf3);
	 cairo_stroke(cr);


 //cairo_surface_t *surface_vertex = cairo_surface_create_similar (cairo_get_target (cr),
 //                                         CAIRO_CONTENT_COLOR_ALPHA,
 //                                         width, height);

 //cairo_t *vertex_cr = cairo_create (surface_vertex);

	 barf1 = scaled_rgb (252);
barf2 = scaled_rgb (10);
barf3 = scaled_rgb (20);
 	cairo_set_source_rgb (cr,barf1, barf2, barf3);


cairo_move_to(cr,vertex_left, elevation);
	cairo_line_to(cr, midpoint,vertex_bottom);
	cairo_line_to(cr,vertex_right,elevation);
	cairo_close_path(cr);
	 cairo_stroke(cr);

/* cairo_set_operator (vertex_cr, CAIRO_OPERATOR_OVER);
  cairo_set_source_surface (cr, surface_vertex, 0, 0);
 cairo_paint (vertex_cr);
 cairo_surface_flush (surface_vertex);
 cairo_paint(cr); */




}


/**
Assigns callbacks to controls in the theme tab
 */
void build_controllers_theme(User_Data *user_data) {
	Gui_Data_Theme *gui_data_theme = user_data->gui_data->gui_data_theme;

	g_signal_connect(gui_data_theme->dropdown_theme, "notify::selected", G_CALLBACK(theme_selection_changed), user_data);

	gtk_drawing_area_set_draw_func ( GTK_DRAWING_AREA(gui_data_theme->drawing_balloon), draw_theme, user_data, NULL);

}

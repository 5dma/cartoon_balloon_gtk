#include "../headers.h"
#include <ctype.h>


/**
 * @file build_controllers_theme.c
 * @brief Contains functions for adding callbacks to the themes window.
 */

/**
 * Converts a passed hexadecimal character to its corresponding integer.
 */
gint convert_hex_to_int(const gchar digit) {

	switch (toupper(digit)) {
		case '0':
			return 0;
		case '1':
			return 1;
		case '2':
			return 2;
		case '3':
			return 3;
		case '4':
			return 4;
		case '5':
			return 5;
		case '6':
			return 6;
		case '7':
			return 7;
		case '8':
			return 8;
		case '9':
			return 9;
		case 'A':
			return 10;
		case 'B':
			return 11;
		case 'C':
			return 12;
		case 'D':
			return 13;
		case 'E':
			return 14;
		case 'F':
			return 15;
		default:
			return 0;
	}
	return 0;

}

/**
 * Converts a hexadecimal color (such as `#ABCD12`) to an RGB triplet.
 */
void convert_hex_to_rgb(float *rgb, gchar *hex) {

	gchar *r_hex = g_strndup (hex + 1, 2);
 	gchar *g_hex =  g_strndup (hex + 3, 2);
	gchar *b_hex =   g_strndup (hex + 5, 2);

	g_print("red: %s\n", r_hex);
	g_print("green: %s\n", g_hex);
	g_print("blue: %s\n", b_hex);
	
	/* Scale red */
	int trash1 = convert_hex_to_int(r_hex[0]);
	int trash2 = convert_hex_to_int(r_hex[1]);
	int trash = 16*trash1 + trash2;
	float normalized = (float) trash / 256;
	g_print("r: %d, g: %d, b: %d, %f\n", trash1, trash2, trash, normalized);
	*rgb = normalized;

	/* Scale green */
	trash1 = convert_hex_to_int(g_hex[0]);
	trash2 = convert_hex_to_int(g_hex[1]);
	trash = 16*trash1 + trash2;
	normalized = (float) trash / 256;
	g_print("r: %d, g: %d, b: %d, %f\n", trash1, trash2, trash, normalized);
	*(rgb + 1) = normalized;

	/* Scale blue */
	trash1 = convert_hex_to_int(b_hex[0]);
	trash2 = convert_hex_to_int(b_hex[1]);
	trash = 16*trash1 + trash2;
	normalized = (float) trash / 256;
	g_print("r: %d, g: %d, b: %d, %f\n", trash1, trash2, trash, normalized);
	*(rgb + 2) = normalized;


	g_free(r_hex);
	g_free(g_hex);
	g_free(b_hex);

}

/**
 * Called when the user selects a new theme in the Themes tab. The function displays the selected theme's settings.
 */
void theme_selection_changed(GObject *self, GParamSpec *pspec, gpointer data) {
	g_print("New theme selected\n");
	User_Data *user_data = (User_Data *)data;

	Gui_Data_Theme *gui_data_theme = user_data->gui_data->gui_data_theme;

	guint selected_item = gtk_drop_down_get_selected(GTK_DROP_DOWN(gui_data_theme->dropdown_theme));

	GListModel *model_theme = gtk_drop_down_get_model(GTK_DROP_DOWN(gui_data_theme->dropdown_theme));
	const char *selected_theme_name = gtk_string_list_get_string(GTK_STRING_LIST(model_theme), selected_item);

	int new_compare = g_strcmp0(NEW_THEME, selected_theme_name);

	if (new_compare == 0) {
		/* If the user selected (new), enable the entry box for the new theme name.*/
		gtk_widget_set_sensitive(gui_data_theme->entry_new_theme, TRUE);
		gtk_widget_grab_focus(gui_data_theme->entry_new_theme);
	} else {
		/* Otherwise, disable the entry box and set the controls to the values for the selected theme. */
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


		/* Save values in the theme_preview structure as we will be passing them to the function that draws the preview. */
		Theme_Preview *theme_preview = user_data->theme_preview;
		theme_preview->selected_theme = theme;

		convert_hex_to_rgb(theme_preview->fill_rgb, theme->balloon_fill_color);
		convert_hex_to_rgb(theme_preview->stroke_rgb, theme->balloon_stroke_color);
		g_stpcpy (theme_preview->font, theme->font);


		/* Go draw the theme preview. */
		gtk_widget_queue_draw(user_data->gui_data->gui_data_theme->drawing_balloon);
	}
}

/**
 * Scales a standard R, G, or B value in the range 0-255 to a double in the range 0-1.
 */
double scaled_rgb(int input) {
	return (double)input / 255;
}


/**
 * Draws a preview of the selected theme in the Themes tab.
 */
void draw_theme(GtkDrawingArea *drawing_area, cairo_t *cr,
				int width,
				int height,
				gpointer data) {
	g_print("Draw\n");

	User_Data *user_data = (User_Data *)data;
	Theme_Preview *theme_preview = user_data->theme_preview;

	user_data->gui_data->gui_data_theme->cr = cr;
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
	/* In following line, sans-serif is hard coded because cairo_selet_font_face supports only
	the basic fonts sans-serif, serif, monospace. */
	cairo_select_font_face(cr, "sans-serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);


/*
Preliminary attempts at using cairo to retrieve the back-end fonts. Pango may be better way to go.
cairo_set_font_face (cairo_t *cr,
                     cairo_font_face_t *font_face);
 cairo_scaled_font_t *scaled_font = cairo_scaled_font_create (cairo_font_face_t *font_face,
                          const cairo_matrix_t *font_matrix,
                          const cairo_matrix_t *ctm,
                          const cairo_font_options_t *options);

	FT_Face font_face = cairo_ft_scaled_font_lock_face (cairo_scaled_font_t *scaled_font);
	cairo_font_face_t status = cairo_font_face_set_user_data (font_face, &key,
                               ft_face, (cairo_destroy_func_t) FT_Done_Face); */


	cairo_set_font_size(cr, 15);
	cairo_move_to(cr, theme_preview->text_start.x, theme_preview->text_start.y);
	cairo_show_text(cr, "THEME");
}


void get_font_name (GtkButton* self,  gpointer data) {
	g_print("Clicked\n");
	
	User_Data *user_data = (User_Data *)data;

	/* gchar *selected_font = gtk_font_chooser_get_font (GTK_FONT_CHOOSER(self));
	g_print("Font: %s\n",selected_font);
	g_free(selected_font);

 */
	PangoFontFace *pango_font_face = gtk_font_chooser_get_font_face (GTK_FONT_CHOOSER(self));
 	const gchar *face_name  = pango_font_face_get_face_name (pango_font_face);
	g_print("Face name: %s\n",face_name); 

	PangoFontFamily *pango_font_family = pango_font_face_get_family (pango_font_face);
	const gchar *font_family = pango_font_family_get_name (pango_font_family);
	g_print("Font family: %s\n",font_family);

/* 	const gchar *font_family_from_pango = pango_font_family_get_name (pango_font_family);
	g_print("Font family from pango: %s\n",font_family_from_pango); */


/* 
	selected_font = gtk_font_chooser_get_font_features (GTK_FONT_CHOOSER(self));
	g_print("Font features: %s\n",selected_font);
	g_free(selected_font);
 */
	gint fontsize = gtk_font_chooser_get_font_size (GTK_FONT_CHOOSER(self)) / 1000;
	g_print("Font size: %d\n",fontsize);
 

	gchar *font_family_and_face = g_strconcat (font_family,"-",face_name, NULL);
	g_print("Before: %s\n", font_family_and_face);
	gchar *normalized_font_name = g_strdelimit (font_family_and_face," ",'-');
	g_print("After: %s\n", normalized_font_name);
	g_print("Back to the original: %s\n", font_family_and_face);

	//g_free(normalized_font_name);
	//g_free(font_family_and_face);
	

}


/**
Assigns callbacks to controls in the theme tab
 */
void build_controllers_theme(User_Data *user_data) {

	g_print("Started build_controllers_theme\n");

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

	theme_preview->text_start.x = midpoint_horizontal - 20;
	theme_preview->text_start.y = midpoint_vertical;

	Gui_Data_Theme *gui_data_theme = user_data->gui_data->gui_data_theme;
	gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(gui_data_theme->drawing_balloon), draw_theme, user_data, NULL);

	g_signal_connect(gui_data_theme->dropdown_theme, "notify::selected", G_CALLBACK(theme_selection_changed), user_data);
	g_signal_connect(gui_data_theme->btn_font_name_picker, "font-set", G_CALLBACK(get_font_name), user_data);


}

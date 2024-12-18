#include <headers.h>
#include <rgb_hex.h>
/**
 * @file theme_tab_callbacks.c
 * @brief Contains callback functions for controls in the **Themes** tab.
 */

/**
 * Fired when the user selects a font in the GtkFontChooser widget. The function does the following:
 * - Ingests the selected font, which includes the font's family and size. For example, for `DejaVu Sans Mono Bold 12`:
 *   - `DejaVu Sans Mono Bold` is the font family.
 *   - `12` is the font size.
 * - Saves the font family and face in the theme's `font_name` field.
 * - Saves the font size in the theme's `font_size` field.
* @param self Pointer to the font chooser widget.
* @param data Pointer to user data.
 */
void save_selected_font_to_theme(GtkButton *self, gpointer data)
{

	User_Data *user_data = (User_Data *)data;

	const gchar *font = gtk_font_chooser_get_font (GTK_FONT_CHOOSER(self));

	/* Find the last space in the returned font and replace it with a `\0`. This delimits the font family from the font size. */
	gchar *family_size_delimiter = g_strrstr (font, " ");
	*family_size_delimiter = '\0';

	/* Retrieve the currently selected theme. */
	Theme *selected_theme = (Theme *)get_selected_theme_from_hash(user_data, user_data->gui_data->gui_data_theme->dropdown_theme);

	/* Save the selected font family and size into the theme's settings. */
	g_strlcpy ( selected_theme->font_name, font, MAX_PATH_LENGTH);
	selected_theme->font_size = g_ascii_strtoull (family_size_delimiter + 1, NULL, 10);

	selected_theme->font_size = gtk_font_chooser_get_font_size(GTK_FONT_CHOOSER(self)) / 1000;

}

/**
 * Fired when the user selects a new color for the font. The function does the following:
 * - Retrieves the color from the color picker.
 * - Saves the color in hex format to the theme.
 * - Displays the hex value in the GUI.
 * - Redraws the preview with the new text color.
 * @param self Pointer to the color chooser widget.
 * @param data Pointer to user data.
*/
void save_selected_font_color_to_theme(GtkColorButton *self, gpointer data)
{
	User_Data *user_data = (User_Data *)data;

	Theme *selected_theme = (Theme *)get_selected_theme_from_hash(user_data, user_data->gui_data->gui_data_theme->dropdown_theme);
	GdkRGBA text_color;
	
	gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(self), &text_color);
	convert_rgb_to_hex(selected_theme->text_color, &text_color);

	gtk_editable_set_text (GTK_EDITABLE(user_data->gui_data->gui_data_theme->entry_font_color), selected_theme->text_color);

	/* Go draw the theme preview. */
	gtk_widget_queue_draw(user_data->gui_data->gui_data_theme->drawing_balloon);
}

/**
 * Fired when the user selects a new color for the balloon fill. The function does the following:
 * - Retrieves the color from the color picker.
 * - Saves the color in hex format to the theme.
 * - Displays the hex value in the GUI.
 * - Redraws the preview with the new fill color.
 * @param self Pointer to the color chooser widget.
 * @param data Pointer to user data.
 */
void save_selected_balloon_fill_color_to_theme(GtkColorButton *self, gpointer data)
{
	User_Data *user_data = (User_Data *)data;
	Theme *selected_theme = (Theme *)get_selected_theme_from_hash(user_data, user_data->gui_data->gui_data_theme->dropdown_theme);
	GdkRGBA fill_color;

	gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(self), &fill_color);
	convert_rgb_to_hex(selected_theme->balloon_fill_color, &fill_color);

	gtk_editable_set_text (GTK_EDITABLE(user_data->gui_data->gui_data_theme->entry_fill_color), selected_theme->balloon_fill_color);

	/* Go draw the theme preview. */
	gtk_widget_queue_draw(user_data->gui_data->gui_data_theme->drawing_balloon);
}


/**
 * Fired when the user selects a new color for the balloon/vertex stroke. The function does the following:
 * - Retrieves the color from the color picker.
 * - Saves the color in hex format to the theme.
 * - Displays the hex value in the GUI.
 * - Redraws the preview with the new stroke color.
 * @param self Pointer to the color chooser widget.
 * @param data Pointer to user data.
 */
void save_selected_balloon_stroke_color_to_theme(GtkColorButton *self, gpointer data)
{
	User_Data *user_data = (User_Data *)data;
	Theme *selected_theme = (Theme *)get_selected_theme_from_hash(user_data, user_data->gui_data->gui_data_theme->dropdown_theme);
	GdkRGBA stroke_color;

	gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(self), &stroke_color);
	convert_rgb_to_hex(selected_theme->balloon_stroke_color, &stroke_color);

	gtk_editable_set_text (GTK_EDITABLE(user_data->gui_data->gui_data_theme->entry_stroke_color), selected_theme->balloon_stroke_color);

	/* Go draw the theme preview. */
	gtk_widget_queue_draw(user_data->gui_data->gui_data_theme->drawing_balloon);
}


/**
 * Fired when the user selects a new width for the balloon/vertex stroke. The function does the following:
 * - Retrieves the width from the spinner.
 * - Saves the color in hex format to the theme.
 * - Displays the hex value in the GUI.
 * - Redraws the preview with the new width.
  * @param self Pointer to the spin button.
 * @param data Pointer to user data.
*/
void save_selected_stroke_width_to_theme(GtkSpinButton *self, gpointer data)
{
	User_Data *user_data = (User_Data *)data;
	Theme *selected_theme = (Theme *)get_selected_theme_from_hash(user_data, user_data->gui_data->gui_data_theme->dropdown_theme);
	selected_theme->stroke_width = (gint64) gtk_spin_button_get_value(self);

	gtk_widget_queue_draw(user_data->gui_data->gui_data_theme->drawing_balloon);
}

/**
 * Fired when the user toggles the rounded corners checkbox in the **Themes** tab. The function saves the new setting in the theme, redraws the preview with or without rounded corners.
 * @param self Pointer to the checkbox.
 * @param data Pointer to user data.
 */
void redraw_rounded_corners( GtkCheckButton* self,  gpointer data) {
	User_Data *user_data = (User_Data *)data;
	Theme *selected_theme = (Theme *)get_selected_theme_from_hash(user_data, user_data->gui_data->gui_data_theme->dropdown_theme);
	selected_theme->rounded_corners = gtk_check_button_get_active(self);
	gtk_widget_queue_draw(user_data->gui_data->gui_data_theme->drawing_balloon);
}

/**
 * Fired when the user selects a new theme in the **Themes** tab. The function does one of two things:
 * - If the user selected an existing theme, retrieve the theme's settings and assign them to the widgets.
 * - If the user selected **(new)**, activate the text box for entering a the new theme's name. Implicitly the new theme inherits the settings of the currently selected theme.
 * @param self Pointer to the theme dropdown.
 * @param pspec Provided by GTK, not used.
 * @param data Pointer to user data.
 */
void theme_selection_changed(GObject *self, GParamSpec *pspec, gpointer data)
{
	User_Data *user_data = (User_Data *)data;

	Gui_Data_Theme *gui_data_theme = user_data->gui_data->gui_data_theme;

	guint selected_item = gtk_drop_down_get_selected(GTK_DROP_DOWN(gui_data_theme->dropdown_theme));

	GListModel *model_theme = gtk_drop_down_get_model(GTK_DROP_DOWN(gui_data_theme->dropdown_theme));

	gpointer temp = g_list_model_get_item (G_LIST_MODEL(model_theme), selected_item);
	const char *selected_theme_name = gtk_string_object_get_string (GTK_STRING_OBJECT(temp));

	int new_compare = g_strcmp0(NEW_THEME, selected_theme_name);

	/* If the user selected (new), enable the text entry for writing the new theme's name. */
	if (new_compare == 0){
		gtk_widget_set_sensitive(gui_data_theme->entry_new_theme, TRUE);
		gtk_widget_grab_focus(gui_data_theme->entry_new_theme);
		gtk_widget_set_sensitive(gui_data_theme->btn_delete,FALSE);
		return;
	}
	
	/* Otherwise, disable the entry box and set the controls to the values for the selected theme. */
	gtk_widget_set_sensitive(gui_data_theme->entry_new_theme, FALSE);
	gtk_widget_set_sensitive(gui_data_theme->btn_delete,TRUE);
	
	Theme *theme = (Theme *)g_hash_table_lookup(user_data->theme_hash, selected_theme_name);

	gtk_editable_set_text (GTK_EDITABLE(gui_data_theme->entry_font_color), theme->text_color);

	gtk_editable_set_text (GTK_EDITABLE(gui_data_theme->entry_fill_color), theme->balloon_fill_color);

	gtk_editable_set_text (GTK_EDITABLE(gui_data_theme->entry_stroke_color), theme->balloon_stroke_color);

	gtk_spin_button_set_value(GTK_SPIN_BUTTON(gui_data_theme->spin_stroke_width), theme->stroke_width);

	/* Remove current font picker from the grid; create a new one, connect a signal, and add it to the grid. */
	gtk_grid_remove(GTK_GRID(gui_data_theme->grid_text), gui_data_theme->btn_font_name_picker);
	gchar *font_label = g_strdup_printf("%s %ld", theme->font_name, theme->font_size);
	gui_data_theme->btn_font_name_picker = gtk_font_button_new();
	gtk_font_chooser_set_font(GTK_FONT_CHOOSER(gui_data_theme->btn_font_name_picker), font_label);

	gtk_font_button_set_use_font(GTK_FONT_BUTTON(gui_data_theme->btn_font_name_picker), FALSE);
	g_signal_connect(gui_data_theme->btn_font_name_picker, "font-set", G_CALLBACK(save_selected_font_to_theme), user_data);
	gtk_grid_attach(GTK_GRID(gui_data_theme->grid_text), gui_data_theme->btn_font_name_picker, 1, 1, 1, 1);
	g_free(font_label);

	/* Remove current font color picker from the grid; create a new one, connect a signal, and add it to the grid. */
	gtk_grid_remove(GTK_GRID(gui_data_theme->grid_text), gui_data_theme->btn_font_color_picker);
	GdkRGBA rgba;
	convert_hex_to_rgb(&rgba, theme->text_color);
	gui_data_theme->btn_font_color_picker = gtk_color_button_new_with_rgba(&rgba);
	g_signal_connect(gui_data_theme->btn_font_color_picker, "color-set", G_CALLBACK(save_selected_font_color_to_theme), user_data);
	gtk_grid_attach(GTK_GRID(gui_data_theme->grid_text), gui_data_theme->btn_font_color_picker, 2, 2, 1, 1);

	/* Remove current balloon fill color picker from the grid; create a new one, connect a signal, and add it to the grid. */
	gtk_grid_remove(GTK_GRID(gui_data_theme->grid_balloon), gui_data_theme->btn_balloon_fill_color_picker);
	convert_hex_to_rgb(&rgba, theme->balloon_fill_color);
	gui_data_theme->btn_balloon_fill_color_picker = gtk_color_button_new_with_rgba(&rgba);
	g_signal_connect(gui_data_theme->btn_balloon_fill_color_picker, "color-set", G_CALLBACK(save_selected_balloon_fill_color_to_theme), user_data);
	gtk_grid_attach(GTK_GRID(gui_data_theme->grid_balloon), gui_data_theme->btn_balloon_fill_color_picker, 2, 1, 1, 1);

	/* Remove current balloon stroke color picker from the grid; create a new one, connect a signal, and add it to the grid. */
	gtk_grid_remove(GTK_GRID(gui_data_theme->grid_balloon), gui_data_theme->btn_balloon_stroke_color_picker);
	convert_hex_to_rgb(&rgba, theme->balloon_stroke_color);
	gui_data_theme->btn_balloon_stroke_color_picker = gtk_color_button_new_with_rgba(&rgba);
	g_signal_connect(gui_data_theme->btn_balloon_stroke_color_picker, "color-set", G_CALLBACK(save_selected_balloon_stroke_color_to_theme), user_data);
	gtk_grid_attach(GTK_GRID(gui_data_theme->grid_balloon), gui_data_theme->btn_balloon_stroke_color_picker, 2, 2, 1, 1);

	gtk_check_button_set_active (GTK_CHECK_BUTTON(gui_data_theme->check_rounded_corners), theme->rounded_corners); 
	g_signal_connect(gui_data_theme->check_rounded_corners, "toggled", G_CALLBACK(redraw_rounded_corners), user_data);

	/* Go draw the theme preview. */
	gtk_widget_queue_draw(user_data->gui_data->gui_data_theme->drawing_balloon);

}

/**
 * Draws a preview of the selected theme in the Themes tab.
 * @param drawing_area Pointer to the preview's drawing area.
 * @param cr Pointer to the Cairo context associated with the preview.
 * @param width Width of the drawing area provided by GTK; not used.
 * @param height Height of the drawing area provided by GTK; not used.
 * @param data Pointer to user data.
 */
void draw_theme(GtkDrawingArea *drawing_area, cairo_t *cr,
				int width,
				int height,
				gpointer data)
{

	User_Data *user_data = (User_Data *)data;
	Theme_Geometry *theme_geometry = user_data->theme_geometry;
	Theme *selected_theme = (Theme *)get_selected_theme_from_hash(user_data, user_data->gui_data->gui_data_theme->dropdown_theme);

	user_data->gui_data->gui_data_theme->cr = cr;
	
	
	/* Draw balloon and fill */

	gint64 stroke_width = (gint64)gtk_spin_button_get_value(GTK_SPIN_BUTTON(user_data->gui_data->gui_data_theme->spin_stroke_width));

	GdkRGBA fill_rgb;
	const gchar *fill_hex = gtk_editable_get_text(GTK_EDITABLE(user_data->gui_data->gui_data_theme->entry_fill_color));
	convert_hex_to_rgb(&fill_rgb, fill_hex);
	cairo_set_source_rgb(cr, fill_rgb.red, fill_rgb.green, fill_rgb.blue);
	
	
	cairo_set_line_width(cr, stroke_width);

	cairo_new_path(cr);
	if (selected_theme->rounded_corners) { 

		Coordinates arc_center_top_left;
		arc_center_top_left.x = theme_geometry->balloon_top_left.x + PREVIEW_RADIUS;
		arc_center_top_left.y = theme_geometry->balloon_top_left.y + PREVIEW_RADIUS;

		Coordinates arc_center_top_right;
		arc_center_top_right.x = theme_geometry->balloon_bottom_right.x - PREVIEW_RADIUS;
		arc_center_top_right.y = theme_geometry->balloon_top_left.y + PREVIEW_RADIUS;

		Coordinates arc_center_bottom_right;
		arc_center_bottom_right.x = theme_geometry->balloon_bottom_right.x - PREVIEW_RADIUS;
		arc_center_bottom_right.y = theme_geometry->balloon_bottom_right.y - PREVIEW_RADIUS;

		Coordinates arc_center_bottom_left;
		arc_center_bottom_left.x = theme_geometry->balloon_top_left.x + PREVIEW_RADIUS;
		arc_center_bottom_left.y = theme_geometry->balloon_bottom_right.y - PREVIEW_RADIUS;

		cairo_move_to(cr, 
			theme_geometry->balloon_top_left.x + PREVIEW_RADIUS,
			theme_geometry->balloon_top_left.y);

		cairo_line_to(cr, 
			theme_geometry->balloon_bottom_right.x - PREVIEW_RADIUS,
			theme_geometry->balloon_top_left.y);


		 cairo_arc (cr,
			arc_center_top_right.x,
			arc_center_top_right.y,
			PREVIEW_RADIUS,
			1.5 * M_PI,
			2.0 * M_PI);

		cairo_line_to(cr, 
			theme_geometry->balloon_bottom_right.x,
			theme_geometry->balloon_bottom_right.y - PREVIEW_RADIUS);
		

		 cairo_arc(cr,
			arc_center_bottom_right.x,
			arc_center_bottom_right.y,
			PREVIEW_RADIUS,
			0.0 * M_PI,
			0.5 * M_PI); 

		
		cairo_line_to(cr, 
			theme_geometry->balloon_top_left.x + PREVIEW_RADIUS,
			theme_geometry->balloon_bottom_right.y);

		 cairo_arc (cr,
			arc_center_bottom_left.x,
			arc_center_bottom_left.y,
			PREVIEW_RADIUS,
			0.5 * M_PI,
			1.0 * M_PI);

		cairo_line_to(cr, 
			theme_geometry->balloon_top_left.x,
			theme_geometry->balloon_top_left.y + PREVIEW_RADIUS);

		cairo_arc (cr,
			arc_center_top_left.x,
			arc_center_top_left.y,
			PREVIEW_RADIUS,
			1.0 * M_PI,
			1.5 * M_PI);



		cairo_close_path(cr);

	} else {
		cairo_move_to(cr, theme_geometry->balloon_top_left.x, theme_geometry->balloon_top_left.y);
		cairo_line_to(cr, theme_geometry->balloon_bottom_right.x, theme_geometry->balloon_top_left.y);
		cairo_line_to(cr, theme_geometry->balloon_bottom_right.x, theme_geometry->balloon_bottom_right.y);
		cairo_line_to(cr, theme_geometry->balloon_top_left.x, theme_geometry->balloon_bottom_right.y);
		cairo_close_path(cr);
	}
	cairo_fill_preserve(cr);

	/* Stroke balloon */

	GdkRGBA stroke_rgb;
	const gchar *stroke_hex = gtk_editable_get_text(GTK_EDITABLE(user_data->gui_data->gui_data_theme->entry_stroke_color));
	convert_hex_to_rgb(&stroke_rgb, stroke_hex);
	cairo_set_source_rgb(cr, stroke_rgb.red, stroke_rgb.green, stroke_rgb.blue);
	cairo_stroke(cr);

	/* Draw vertex and fill */

	cairo_set_source_rgb(cr, fill_rgb.red, fill_rgb.green, fill_rgb.blue);

	cairo_move_to(cr, theme_geometry->vertex_left.x, theme_geometry->vertex_left.y);
	cairo_line_to(cr, theme_geometry->vertex_bottom.x, theme_geometry->vertex_bottom.y);
	cairo_line_to(cr, theme_geometry->vertex_right.x, theme_geometry->vertex_right.y);
	cairo_fill_preserve(cr);

	/* Stroke vertex */
	cairo_set_source_rgb(cr, stroke_rgb.red, stroke_rgb.green, stroke_rgb.blue);
	cairo_stroke(cr);

	/* Add text */
	/* In following line, sans-serif is hard coded because cairo_selet_font_face supports only
	the basic fonts sans-serif, serif, monospace. */
	cairo_select_font_face(cr, "sans-serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);

	GdkRGBA text_rgb;
	const gchar *text_hex = gtk_editable_get_text(GTK_EDITABLE(user_data->gui_data->gui_data_theme->entry_font_color));
	convert_hex_to_rgb(&text_rgb, text_hex);

	cairo_set_source_rgb(cr, text_rgb.red, text_rgb.green, text_rgb.blue);

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
	cairo_move_to(cr, theme_geometry->text_start.x, theme_geometry->text_start.y);
	cairo_show_text(cr, "THEME");
}

/**
 * Fired when the user changes the name in the new theme field. As the user types characters, the function displays a message if the new name already exists in the hash of themes. The new theme is actually saved when the user exits the entry field. See new_theme().
* @param self Pointer to the anonymous text box holding a new theme's name.
* @param data Pointer to user data.
 */
void get_new_theme_name(GtkWidget *self, gpointer data)
{
	User_Data *user_data = (User_Data *)data;

	const gchar *new_theme_name = gtk_editable_get_text(GTK_EDITABLE(self));

	gboolean already_exists = g_hash_table_contains(user_data->theme_hash, new_theme_name);
	if (already_exists)
	{
		populate_status_bar(user_data->gui_data->status_bar, "A theme named %s already exists, not saving", new_theme_name);
	}
	else
	{
		populate_status_bar(user_data->gui_data->status_bar, "Creating new theme %s when exiting the field", new_theme_name);
	}
}

/**
 * Fired when the user exits the field for adding a new theme. The function does the following:
 * -# Verifies the new theme name does not exist in the hash of themes.
 * -# Allocates memory for a new theme.
 * -# Populates the new theme's fields with values from the currently displayed theme.
 * -# Adds the new theme to the hash.
 * -# Adds the new theme's name to the model populating the theme dropdown.
 * @param self Pointer to the anonymous text box holding a new theme's name.
 * @param data Pointer to user data.
 */
void new_theme(GtkEventControllerFocus *self, gpointer data)
{

	User_Data *user_data = (User_Data *)data;
	GHashTable *theme_hash = user_data->theme_hash;
	Gui_Data_Theme *gui_data_theme = user_data->gui_data->gui_data_theme;

	const gchar *new_theme_name = gtk_editable_get_text(GTK_EDITABLE(user_data->gui_data->gui_data_theme->entry_new_theme));

	/* If the field is empty, return. */
	glong length = g_utf8_strlen(new_theme_name, -1);
	if (length == 0)
		return;

	/* If the entered theme name already exists in the hash, return. */
	gboolean already_exists = g_hash_table_contains(theme_hash, new_theme_name);
	if (already_exists)
		return;

	/* Allocate memory for the new theme's settings. */
	Theme *new_theme = (Theme *)g_malloc(sizeof(Theme));

	/* Retrieve values from the widgets, and store them in the theme's settings. */
	g_strlcpy(new_theme->name, new_theme_name, 100);

	GtkWidget *temp = gui_data_theme->entry_font_color;
	g_strlcpy(new_theme->text_color, gtk_editable_get_text(GTK_EDITABLE(temp)), 8);

	temp = gui_data_theme->btn_font_name_picker;
	const gchar *current_font = gtk_font_chooser_get_font(GTK_FONT_CHOOSER(temp));

	gchar *font_name_size_delimiter = g_strrstr(current_font, " ");
	g_utf8_strncpy(new_theme->font_name, current_font, font_name_size_delimiter - current_font);

	new_theme->font_size = g_ascii_strtoull(font_name_size_delimiter + 1, NULL, 10);

	temp = gui_data_theme->spin_stroke_width;
	new_theme->stroke_width = (gint64)gtk_spin_button_get_value(GTK_SPIN_BUTTON(temp));

	/* The GtkColorChooser widget returns colors as RGB triplets from 1-100. We store the colors as hex strings. For each color chooser, convert the value to hex and then save in the theme's settings. */
	temp = gui_data_theme->btn_balloon_fill_color_picker;
	GdkRGBA color;
	gchar color_holder[55];
	gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(gui_data_theme->btn_balloon_fill_color_picker), &color);
	convert_rgb_to_hex(color_holder, &color);
	g_strlcpy(new_theme->balloon_fill_color, color_holder, 8);

	temp = gui_data_theme->btn_balloon_stroke_color_picker;
	gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(gui_data_theme->btn_balloon_stroke_color_picker), &color);
	convert_rgb_to_hex(color_holder, &color);
	g_strlcpy(new_theme->balloon_stroke_color, color_holder, 8);

	/* Add the new theme to the hash of themes. */
	g_hash_table_insert(theme_hash, new_theme->name, new_theme);

	/* Get the theme dropdown's model, and insert the new theme into that model. */
	GListModel *model_theme = gtk_drop_down_get_model(GTK_DROP_DOWN(gui_data_theme->dropdown_theme));
	g_list_store_insert_sorted(user_data->list_store_themes, gtk_string_object_new(new_theme->name), comparestrings, NULL);

	guint new_theme_position = g_list_model_get_n_items (model_theme);

	/* We are going to select the new theme in the dropdown. We want to block the signal notify::selected on that dropdown so that we don't trigger the callback theme_selection_changed(). */
	GQuark detail = g_quark_from_string (NULL);
	gulong handler_id = g_signal_handler_find (gui_data_theme->dropdown_theme, G_SIGNAL_MATCH_FUNC, 0, detail, NULL, theme_selection_changed, NULL);
	g_signal_handler_block (gui_data_theme->dropdown_theme, handler_id);	
	
	/* Set the new name, which is the last item in the model, to the selected theme.*/
	gtk_drop_down_set_selected (GTK_DROP_DOWN(gui_data_theme->dropdown_theme), new_theme_position - 1); 
	
	/* Unblock the notify::selected signal. */
	g_signal_handler_unblock (gui_data_theme->dropdown_theme, handler_id);

	/* Disable the text field, delete any text in the text field, and move focus to the dropdown */
	gtk_widget_set_sensitive(gui_data_theme->entry_new_theme, FALSE);
	gtk_editable_delete_text (GTK_EDITABLE(gui_data_theme->entry_new_theme), 0, -1);
	gtk_widget_grab_focus(gui_data_theme->dropdown_theme);

	/* Display a message in the status bar. */
	populate_status_bar(user_data->gui_data->status_bar, "Added %s to the list of themes.", new_theme->name);
}

/**
 * Fired when the user clicks the **Delete** button. The function does the following:
 * -# Acquires the name of the currently selected theme.
 * -# Removes the theme from the hash of themes.
 * -# Frees memory allocated to the theme.
 * -# Removes the theme from the list model populating the dropdown.
 * -# Selects the next available theme in the dropdown.
 * @param self Pointer to the **Delete** button.
 * @param data Pointer to user data. */
void delete_theme(GtkButton *self, gpointer data)
{

	User_Data *user_data = (User_Data *)data;
	GHashTable *theme_hash = user_data->theme_hash;
	Gui_Data_Theme *gui_data_theme = user_data->gui_data->gui_data_theme;

	guint selected_theme_position = gtk_drop_down_get_selected(GTK_DROP_DOWN(gui_data_theme->dropdown_theme));

	GListModel *model_theme = gtk_drop_down_get_model(GTK_DROP_DOWN(gui_data_theme->dropdown_theme));

	gpointer temp = g_list_model_get_item (G_LIST_MODEL(model_theme), selected_theme_position);
	const char *deleted_theme_name = gtk_string_object_get_string (GTK_STRING_OBJECT(temp));

	gpointer *deleted_theme = g_hash_table_lookup(theme_hash, deleted_theme_name);

	if (deleted_theme != NULL)
	{
		/* theme_hash was created with g_hash_table_new_full, so the key and value are freed automatically. */
		g_hash_table_remove(theme_hash, deleted_theme_name);
		g_list_store_remove (user_data->list_store_themes, selected_theme_position);
		/* Select the first theme in the dropdown.*/
		gtk_drop_down_set_selected (GTK_DROP_DOWN(gui_data_theme->dropdown_theme), 0); 
	}

}
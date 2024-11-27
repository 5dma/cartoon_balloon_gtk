#include "../headers.h"
#include <ctype.h>

/**
 * @file build_controllers_theme.c
 * @brief Contains functions for adding callbacks to the themes window.
 */

/**
 * Converts a passed hexadecimal character to its corresponding integer.
 */
gint convert_hex_to_int(const gchar digit)
{

	switch (toupper(digit))
	{
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
void convert_hex_to_rgb(GdkRGBA *rgb, gchar *hex)
{

	gchar *r_hex = g_strndup(hex + 1, 2);
	gchar *g_hex = g_strndup(hex + 3, 2);
	gchar *b_hex = g_strndup(hex + 5, 2);

	/* Scale red */
	int trash1 = convert_hex_to_int(r_hex[0]);
	int trash2 = convert_hex_to_int(r_hex[1]);
	int trash = 16 * trash1 + trash2;
	rgb->red = (float)trash / 256;

	/* Scale green */
	trash1 = convert_hex_to_int(g_hex[0]);
	trash2 = convert_hex_to_int(g_hex[1]);
	trash = 16 * trash1 + trash2;
	rgb->green = (float)trash / 256;

	/* Scale blue */
	trash1 = convert_hex_to_int(b_hex[0]);
	trash2 = convert_hex_to_int(b_hex[1]);
	trash = 16 * trash1 + trash2;
	rgb->blue = (float)trash / 256;

	rgb->alpha = 1.0;

	g_free(r_hex);
	g_free(g_hex);
	g_free(b_hex);
}

/**
 *Converts a `GdkRGBA` struct to a hexadecimal color.
 */
void convert_rgb_to_hex(gchar *hex, GdkRGBA *rgb)
{

	hex[0] = '#';

	/* Convert red */
	guint scaled_red = rgb->red * 256;
	g_snprintf(hex + 1, 3, "%X", scaled_red);

	/* Convert green */
	guint scaled_green = rgb->green * 256;
	g_snprintf(hex + 3, 3, "%X", scaled_green);

	/* Convert blue */
	guint scaled_blue = rgb->blue * 256;
	g_snprintf(hex + 5, 3, "%X", scaled_blue);
}

/**
 * Called when the user selects a font. The function does the following:
 * - ingests the selected font, which includes the font's family, face and size. For example, for `DejaVu Sans Mono Bold 12`:
 *   - `DejaVu Sans Mono` is the font family.
 *   - `Bold` is the font face.
 *   - `12` is the font size.
 * - Saves the font family and face in the theme's `font_name` field.
 * - Saves the font size in the theme's `font_size` field.
 */
void save_selected_font_to_theme(GtkButton *self, gpointer data)
{

	User_Data *user_data = (User_Data *)data;

	PangoFontFace *pango_font_face = gtk_font_chooser_get_font_face(GTK_FONT_CHOOSER(self));
	const gchar *face_name = pango_font_face_get_face_name(pango_font_face);

	PangoFontFamily *pango_font_family = pango_font_face_get_family(pango_font_face);
	const gchar *font_family = pango_font_family_get_name(pango_font_family);

	g_snprintf(user_data->theme_preview->selected_theme->font_name, MAX_PATH_LENGTH, "%s %s", font_family, face_name);

	g_print("The actual font retrieved is %s\n", gtk_font_chooser_get_font(GTK_FONT_CHOOSER(self)));

	user_data->theme_preview->selected_theme->font_size = gtk_font_chooser_get_font_size(GTK_FONT_CHOOSER(self)) / 1000;

	g_print("The new theme font is %s, size %ld\n", user_data->theme_preview->selected_theme->font_name, user_data->theme_preview->selected_theme->font_size);
}

/**
 * Called when the user selects a new color for the font. The function does the following:
 * - Retrieves the color from the color picker.
 * - Saves the color in hex format to the theme.
 * - Displays the hex value in the GUI.
 * - Redraws the preview with the new text color.
 */
void save_selected_font_color_to_theme(GtkColorButton *self, gpointer data)
{
	User_Data *user_data = (User_Data *)data;

	gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(self), &user_data->theme_preview->text_rgb);
	convert_rgb_to_hex(user_data->theme_preview->selected_theme->text_color, &user_data->theme_preview->text_rgb);
	g_print("Hex string for new text color: %s\n", user_data->theme_preview->selected_theme->text_color);
	GtkEntryBuffer *entry_buffer = gtk_entry_get_buffer(GTK_ENTRY(user_data->gui_data->gui_data_theme->entry_font_color));
	gtk_entry_buffer_set_text(entry_buffer, user_data->theme_preview->selected_theme->text_color, -1);

	/* Go draw the theme preview. */
	gtk_widget_queue_draw(user_data->gui_data->gui_data_theme->drawing_balloon);
}

/**
 * Called when the user selects a new color for the balloon fill. The function does the following:
 * - Retrieves the color from the color picker.
 * - Saves the color in hex format to the theme.
 * - Displays the hex value in the GUI.
 * - Redraws the preview with the new text color.
 */
void save_selected_balloon_fill_color_to_theme(GtkColorButton *self, gpointer data)
{
	User_Data *user_data = (User_Data *)data;

	gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(self), &user_data->theme_preview->fill_rgb);
	convert_rgb_to_hex(user_data->theme_preview->selected_theme->balloon_fill_color, &user_data->theme_preview->fill_rgb);
	g_print("Hex string for new fill: %s\n", user_data->theme_preview->selected_theme->balloon_fill_color);
	GtkEntryBuffer *entry_buffer = gtk_entry_get_buffer(GTK_ENTRY(user_data->gui_data->gui_data_theme->entry_fill_color));
	gtk_entry_buffer_set_text(entry_buffer, user_data->theme_preview->selected_theme->balloon_fill_color, -1);

	/* Go draw the theme preview. */
	gtk_widget_queue_draw(user_data->gui_data->gui_data_theme->drawing_balloon);
}

/**
 * Called when the user selects a new color for the balloon stroke. The function does the following:
 * - Retrieves the color from the color picker.
 * - Saves the color in hex format to the theme.
 * - Displays the hex value in the GUI.
 * - Redraws the preview with the new text color.
 */
void save_selected_balloon_stroke_color_to_theme(GtkColorButton *self, gpointer data)
{
	User_Data *user_data = (User_Data *)data;

	gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(self), &user_data->theme_preview->stroke_rgb);
	convert_rgb_to_hex(user_data->theme_preview->selected_theme->balloon_stroke_color, &user_data->theme_preview->stroke_rgb);
	g_print("Hex string for new fill: %s\n", user_data->theme_preview->selected_theme->balloon_stroke_color);
	GtkEntryBuffer *entry_buffer = gtk_entry_get_buffer(GTK_ENTRY(user_data->gui_data->gui_data_theme->entry_stroke_color));
	gtk_entry_buffer_set_text(entry_buffer, user_data->theme_preview->selected_theme->balloon_stroke_color, -1);

	/* Go draw the theme preview. */
	gtk_widget_queue_draw(user_data->gui_data->gui_data_theme->drawing_balloon);
}

/**
 * Called when the user selects a new color for the balloon stroke. The function does the following:
 * - Retrieves the color from the color picker.
 * - Saves the color in hex format to the theme.
 * - Displays the hex value in the GUI.
 * - Redraws the preview with the new text color.
 */
void save_selected_stroke_width_to_theme(GtkSpinButton *self, gpointer data)
{
	User_Data *user_data = (User_Data *)data;
	gtk_widget_queue_draw(user_data->gui_data->gui_data_theme->drawing_balloon);
}

/**
 * Called when the user selects a new theme in the Themes tab. The function displays the selected theme's settings.
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

	GtkEntryBuffer *entry_buffer = gtk_entry_get_buffer(GTK_ENTRY(gui_data_theme->entry_font_color));
	gtk_entry_buffer_set_text(entry_buffer, theme->text_color, -1);

	entry_buffer = gtk_entry_get_buffer(GTK_ENTRY(gui_data_theme->entry_fill_color));
	gtk_entry_buffer_set_text(entry_buffer, theme->balloon_fill_color, -1);

	entry_buffer = gtk_entry_get_buffer(GTK_ENTRY(gui_data_theme->entry_stroke_color));
	gtk_entry_buffer_set_text(entry_buffer, theme->balloon_stroke_color, -1);

	gtk_spin_button_set_value(GTK_SPIN_BUTTON(gui_data_theme->spin_stroke_width), theme->stroke_width);

	/* Remove current font picker from the grid; create a new one, connect a signal, and add it to the grid. */
	gtk_grid_remove(GTK_GRID(gui_data_theme->grid_text), gui_data_theme->btn_font_name_picker);
	gchar *font_label = g_strdup_printf("%s %ld", theme->font_name, theme->font_size);
	gui_data_theme->btn_font_name_picker = gtk_font_button_new_with_font(font_label);
	gtk_font_chooser_set_font(GTK_FONT_CHOOSER(gui_data_theme->btn_font_name_picker), font_label);

	gtk_font_button_set_use_font(GTK_FONT_BUTTON(gui_data_theme->btn_font_name_picker), TRUE);
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

	/* Save values in the theme_preview structure as we will be passing them to the function that draws the preview. */
	Theme_Preview *theme_preview = user_data->theme_preview;
	theme_preview->selected_theme = theme;

	convert_hex_to_rgb(&(theme_preview->fill_rgb), theme->balloon_fill_color);
	convert_hex_to_rgb(&(theme_preview->stroke_rgb), theme->balloon_stroke_color);
	convert_hex_to_rgb(&(theme_preview->text_rgb), theme->text_color);
	g_stpcpy(theme_preview->font, theme->font_name);

	/* Go draw the theme preview. */
	gtk_widget_queue_draw(user_data->gui_data->gui_data_theme->drawing_balloon);

}

/**
 * Draws a preview of the selected theme in the Themes tab.
 */
void draw_theme(GtkDrawingArea *drawing_area, cairo_t *cr,
				int width,
				int height,
				gpointer data)
{
	g_print("Draw\n");

	User_Data *user_data = (User_Data *)data;
	Theme_Preview *theme_preview = user_data->theme_preview;

	user_data->gui_data->gui_data_theme->cr = cr;
	/* Draw balloon and fill */

	gint64 stroke_width = (gint64)gtk_spin_button_get_value(GTK_SPIN_BUTTON(user_data->gui_data->gui_data_theme->spin_stroke_width));
	cairo_set_source_rgb(cr, theme_preview->fill_rgb.red, theme_preview->fill_rgb.green, theme_preview->fill_rgb.blue);
	cairo_set_line_width(cr, stroke_width);
	cairo_new_path(cr);
	cairo_move_to(cr, theme_preview->balloon_top_left.x, theme_preview->balloon_top_left.y);
	cairo_line_to(cr, theme_preview->balloon_bottom_right.x, theme_preview->balloon_top_left.y);
	cairo_line_to(cr, theme_preview->balloon_bottom_right.x, theme_preview->balloon_bottom_right.y);
	cairo_line_to(cr, theme_preview->balloon_top_left.x, theme_preview->balloon_bottom_right.y);
	cairo_close_path(cr);
	cairo_fill_preserve(cr);

	/* Stroke balloon */

	cairo_set_source_rgb(cr, theme_preview->stroke_rgb.red, theme_preview->stroke_rgb.green, theme_preview->stroke_rgb.blue);
	cairo_stroke(cr);

	/* Draw vertex and fill */

	cairo_set_source_rgb(cr, theme_preview->fill_rgb.red, theme_preview->fill_rgb.green, theme_preview->fill_rgb.blue);

	cairo_move_to(cr, theme_preview->vertex_left.x, theme_preview->vertex_left.y);
	cairo_line_to(cr, theme_preview->vertex_bottom.x, theme_preview->vertex_bottom.y);
	cairo_line_to(cr, theme_preview->vertex_right.x, theme_preview->vertex_right.y);
	cairo_fill_preserve(cr);

	/* Stroke vertex */
	cairo_set_source_rgb(cr, theme_preview->stroke_rgb.red, theme_preview->stroke_rgb.green, theme_preview->stroke_rgb.blue);
	cairo_stroke(cr);

	/* Add text */
	/* In following line, sans-serif is hard coded because cairo_selet_font_face supports only
	the basic fonts sans-serif, serif, monospace. */
	cairo_select_font_face(cr, "sans-serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_source_rgb(cr, theme_preview->text_rgb.red, theme_preview->text_rgb.green, theme_preview->text_rgb.blue);

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

/**
 * Called when the user changes the name in the new theme field. As the user types characters, the function displays a message if the new name already exists in the hash of themes.
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
 * Called when the user exits the field for adding a new theme. The function does the following:
 * - Verifies the new theme name does not exist in the hash of themes.
 * - Allocates memory for a new theme.
 * - Populates the new theme's fields with values from the currently displayed theme.
 * - Adds the new theme to the hash.
 * - Adds the new theme's name to the model populating the theme dropdown.
 */
void new_theme(GtkEventControllerFocus *self, gpointer data)
{

	User_Data *user_data = (User_Data *)data;
	GHashTable *theme_hash = user_data->theme_hash;
	Gui_Data_Theme *gui_data_theme = user_data->gui_data->gui_data_theme;

	const gchar *new_theme_name = gtk_editable_get_text(GTK_EDITABLE(user_data->gui_data->gui_data_theme->entry_new_theme));

	glong length = g_utf8_strlen(new_theme_name, -1);
	if (length == 0)
		return;

	gboolean already_exists = g_hash_table_contains(theme_hash, new_theme_name);
	if (already_exists)
		return;


	Theme *new_theme = (Theme *)g_malloc(sizeof(Theme));
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

	g_hash_table_insert(theme_hash, new_theme->name, new_theme);

	GListModel *model_theme = gtk_drop_down_get_model(GTK_DROP_DOWN(gui_data_theme->dropdown_theme));

	g_list_store_insert_sorted(user_data->list_store_themes, gtk_string_object_new(new_theme->name), comparestrings, NULL);

	guint new_theme_position = g_list_model_get_n_items (model_theme);


	/* Block the signal notify::select on the dropdown, allowing us to change the selected item in the dropdown without calling the callback.*/
	gulong handler_id = g_signal_handler_find (gui_data_theme->dropdown_theme, G_SIGNAL_MATCH_FUNC, 0, 0, NULL, theme_selection_changed, NULL);
	g_signal_handler_block (gui_data_theme->dropdown_theme, handler_id);

	/* Set the new name, which is the last item in the model, to the selected theme.*/
	gtk_drop_down_set_selected (GTK_DROP_DOWN(gui_data_theme->dropdown_theme), new_theme_position - 1); 
	
	/* Unblock the notify::select signal on the dropdown. */
	g_signal_handler_unblock (gui_data_theme->dropdown_theme, handler_id);


	/* Disable the text field, delete any text in the text field, and move focus to the dropdown */
	gtk_widget_set_sensitive(gui_data_theme->entry_new_theme, FALSE);
	gtk_editable_delete_text (GTK_EDITABLE(gui_data_theme->entry_new_theme), 0, -1);
	gtk_widget_grab_focus(gui_data_theme->dropdown_theme);

	populate_status_bar(user_data->gui_data->status_bar, "Added %s to the list of themes.", new_theme->name);
}

/**
 * Called when the user clicks the Delete button. The function does the following:
 * - Acquires the name of the currently selected theme.
 * - Removes the theme from the hash of themes.
 * - Frees memory allocated to the theme.
 * - Removes the theme from the list model populating the dropdown.
 * - Displays the next available theme.
 */
void delete_theme(GtkButton *self, gpointer data)
{

	g_print("Clicked~\n");

	User_Data *user_data = (User_Data *)data;
	GHashTable *theme_hash = user_data->theme_hash;
	Gui_Data_Theme *gui_data_theme = user_data->gui_data->gui_data_theme;

	guint selected_theme_position = gtk_drop_down_get_selected(GTK_DROP_DOWN(gui_data_theme->dropdown_theme));

	GListModel *model_theme = gtk_drop_down_get_model(GTK_DROP_DOWN(gui_data_theme->dropdown_theme));
	const gchar *deleted_theme_name = gtk_string_list_get_string(GTK_STRING_LIST(model_theme), selected_theme_position);
	g_print("The selected theme is %d %s\n", selected_theme_position, deleted_theme_name);

	gpointer *deleted_theme = g_hash_table_lookup(theme_hash, deleted_theme_name);

	if (deleted_theme != NULL)
	{
		g_print("Found the theme, trashing in\n");
		/* theme_hash was created with g_hash_table_new_full, so the key and value are freed automatically. */
		g_hash_table_remove(theme_hash, deleted_theme_name);
		gtk_string_list_remove(GTK_STRING_LIST(model_theme), selected_theme_position);
		g_print("Removed the theme\n");
	}

}

/**
Assigns callbacks to controls in the theme tab
 */
void build_controllers_theme(User_Data *user_data)
{

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
	g_signal_connect(gui_data_theme->btn_font_name_picker, "font-set", G_CALLBACK(save_selected_font_to_theme), user_data);
	g_signal_connect(gui_data_theme->spin_stroke_width, "value-changed", G_CALLBACK(save_selected_stroke_width_to_theme), user_data);

	/* Create a controller for exiting the new theme field. */
	GtkEventController *new_theme_controller_focus = gtk_event_controller_focus_new();
	g_signal_connect(new_theme_controller_focus, "leave", G_CALLBACK(new_theme), user_data);
	gtk_widget_add_controller(gui_data_theme->entry_new_theme, new_theme_controller_focus);

	g_signal_connect(GTK_EDITABLE(gui_data_theme->entry_new_theme), "changed", G_CALLBACK(get_new_theme_name), user_data);
	g_signal_connect(GTK_BUTTON(gui_data_theme->btn_delete), "clicked", G_CALLBACK(delete_theme), user_data);
}

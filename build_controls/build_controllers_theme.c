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

/**
Assigns callbacks to controls in the theme tab
 */
void build_controllers_theme(User_Data *user_data) {
	Gui_Data_Theme *gui_data_theme = user_data->gui_data->gui_data_theme;

	g_signal_connect(gui_data_theme->dropdown_theme, "notify::selected", G_CALLBACK(theme_selection_changed), user_data);
}

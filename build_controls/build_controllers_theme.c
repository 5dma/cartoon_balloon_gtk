#include "../headers.h"


/**
 * @file build_controllers_theme.c
 * @brief Contains functions for adding callbacks to the themes window.
 */



void theme_selection_changed (GObject *self, GParamSpec *pspec, gpointer data) {

	Gui_Data_Theme *gui_data_theme = (Gui_Data_Theme *) data;
	guint selected_item = gtk_drop_down_get_selected (GTK_DROP_DOWN(gui_data_theme->dropdown_theme));

g_print("Selection: %d\n",selected_item);
}


/**
Assigns callbacks to controls in the theme tab
 */
void build_controllers_theme(User_Data *user_data) {

	Gui_Data_Theme *gui_data_theme = user_data->gui_data->gui_data_theme;

	g_signal_connect(gui_data_theme->dropdown_theme, "notify::selected", G_CALLBACK(theme_selection_changed), gui_data_theme);


}

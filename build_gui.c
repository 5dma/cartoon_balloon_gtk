#include <gtk/gtk.h>
#include "headers.h"


/**
 * @file build_gui.c
 * @brief Contains functions for building the GUI.
 */


/**
Fires when user clicks the **Annotation** button, and displays the controls in the annotations tab.
 */
void show_annotation_tab(GtkWidget *widget, gpointer data) {
	Gui_Data *gui_data = (Gui_Data *)data;

	gtk_css_provider_load_from_path(gui_data->provider, "/home/abba/programming/c_programs/cartoon_balloon_gtk/styles.css");
	gtk_widget_set_visible(gui_data->box_annotation, TRUE);
	gtk_widget_set_visible(gui_data->box_theme, FALSE);
	gtk_widget_set_visible(gui_data->gui_data_configuration.box_configuration, FALSE);
}

/**
Fires when user clicks the **Theme** button, and displays the controls in the theme tab.
 */
void show_theme_tab(GtkWidget *widget, gpointer data) {
	Gui_Data *gui_data = (Gui_Data *)data;
	gtk_widget_set_visible(gui_data->box_annotation, FALSE);
	gtk_widget_set_visible(gui_data->box_theme, TRUE);
	gtk_widget_set_visible(gui_data->gui_data_configuration.box_configuration, FALSE);
}

/**
Fires when user clicks the **Configuration** button, and displays the controls in the configuration tab.
 */
void show_configuration_tab(GtkWidget *widget, gpointer data) {
	Gui_Data *gui_data = (Gui_Data *)data;
	gtk_widget_set_visible(gui_data->box_annotation, FALSE);
	gtk_widget_set_visible(gui_data->box_theme, FALSE);
	gtk_widget_set_visible(gui_data->gui_data_configuration.box_configuration, TRUE);
}


/**
Parent function for building the GTK GUI.
 */
void activate(GtkApplication *app, gpointer data) {
	User_Data *user_data = (User_Data *)data;
	user_data->gui_data = (Gui_Data *) g_malloc(sizeof(Gui_Data));

	user_data->gui_data->provider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(user_data->gui_data->provider, "/home/abba/programming/c_programs/cartoon_balloon_gtk/styles.css");

	GtkWidget *window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Speech Balloon");
	gtk_window_set_default_size(GTK_WINDOW(window), 640, 575);

	GtkWidget *btn_annotation = gtk_button_new_with_label("Annotation");
	GtkWidget *btn_theme = gtk_button_new_with_label("Theme");
	GtkWidget *btn_configuration = gtk_button_new_with_label("Configuration");

	g_signal_connect(btn_annotation, "clicked", G_CALLBACK(show_annotation_tab), user_data->gui_data);
	g_signal_connect(btn_theme, "clicked", G_CALLBACK(show_theme_tab), user_data->gui_data);
	g_signal_connect(btn_configuration, "clicked", G_CALLBACK(show_configuration_tab), user_data->gui_data);

	GtkWidget *header_bar = gtk_header_bar_new();

	gtk_header_bar_pack_start(GTK_HEADER_BAR(header_bar), btn_annotation);
	gtk_header_bar_pack_start(GTK_HEADER_BAR(header_bar), btn_theme);
	gtk_header_bar_pack_start(GTK_HEADER_BAR(header_bar), btn_configuration);
	gtk_window_set_titlebar(GTK_WINDOW(window), header_bar);

	GtkWidget *box_top = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_halign(box_top, GTK_ALIGN_CENTER);
	gtk_widget_set_valign(box_top, GTK_ALIGN_CENTER);
	gtk_widget_set_hexpand(box_top, TRUE);

	GtkWidget *box_annotation = build_box_annotation();
	GtkWidget *box_theme = build_box_theme();
	GtkWidget *box_configuration = build_box_configuration(user_data->gui_data);

	user_data->gui_data->box_annotation = box_annotation;
	user_data->gui_data->box_theme = box_theme;
	user_data->gui_data->gui_data_configuration.box_configuration = box_configuration;

	user_data->gui_data->box_top = box_top;

	GtkWidget *status_bar = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(status_bar), "Ready...");
	gtk_widget_set_sensitive(status_bar, FALSE);
	gtk_widget_set_hexpand(status_bar, TRUE);

	gtk_box_append(GTK_BOX(box_top), box_annotation);
	gtk_box_append(GTK_BOX(box_top), box_theme);
	gtk_box_append(GTK_BOX(box_top), box_configuration);

	gtk_box_append(GTK_BOX(box_top), status_bar);

	gtk_style_context_add_provider_for_display(
		gtk_widget_get_display(GTK_WIDGET(window)),
		GTK_STYLE_PROVIDER(user_data->gui_data->provider),
		GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

	gtk_window_set_child(GTK_WINDOW(window), box_top);

	/* CSS*/
	gtk_widget_set_name(box_top, "box_top");
	gtk_widget_set_name(status_bar, "status_bar");

	gtk_widget_add_css_class(box_annotation, "tab");
	gtk_widget_add_css_class(header_bar, "headerbutton");
	gtk_widget_add_css_class(btn_annotation, "headerbutton");
	gtk_widget_add_css_class(btn_theme, "headerbutton");
	gtk_widget_add_css_class(btn_configuration, "headerbutton");
	gtk_widget_add_css_class(status_bar, "statusbar");

	/* Apply values read from settings.json to the GUI. */
	initialize_gui(user_data);

	gtk_window_present(GTK_WINDOW(window));
}
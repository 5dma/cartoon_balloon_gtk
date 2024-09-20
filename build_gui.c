#include <gtk/gtk.h>
#include "headers.h"

void reapply(GtkWidget *widget, gpointer data) {
	g_print("START\n");
	GtkCssProvider *provider = GTK_CSS_PROVIDER(data);
	gtk_css_provider_load_from_path (provider,"/home/abba/programming/c_programs/cartoon_balloon_gtk/styles.css");
	g_print("END\n");
}

void activate(GtkApplication *app, gpointer user_data) {

	GtkCssProvider *provider = gtk_css_provider_new ();
	gtk_css_provider_load_from_path (provider,"/home/abba/programming/c_programs/cartoon_balloon_gtk/styles.css");


	GtkWidget *window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Speech Balloon");
	//gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);


	GtkWidget * btn_annotation = gtk_button_new_with_label ("Annotation");
	GtkWidget * btn_theme = gtk_button_new_with_label ("Theme");
	GtkWidget * btn_configuration = gtk_button_new_with_label ("Configuration");



	g_signal_connect(btn_annotation,"clicked",G_CALLBACK(reapply), provider);

	GtkWidget * header_bar =  gtk_header_bar_new ();


	gtk_header_bar_pack_start ( GTK_HEADER_BAR (header_bar), btn_annotation);
	gtk_header_bar_pack_start (GTK_HEADER_BAR (header_bar), btn_theme);
	gtk_header_bar_pack_start (GTK_HEADER_BAR (header_bar), btn_configuration);
	gtk_window_set_titlebar ( GTK_WINDOW (window), header_bar);


	GtkWidget *box_top = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_halign(box_top, GTK_ALIGN_CENTER);
	gtk_widget_set_valign(box_top, GTK_ALIGN_CENTER);
	gtk_widget_set_hexpand (box_top, TRUE);
  
	GtkWidget * box_annotation = build_box_annotation();
	GtkWidget * box_theme = build_box_theme();

	GtkWidget *status_bar = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(status_bar), "Ready...");
	gtk_widget_set_sensitive (status_bar, FALSE);
	gtk_widget_set_hexpand (status_bar, TRUE);


//	gtk_box_append(GTK_BOX(box_top), box_annotation);
	gtk_box_append(GTK_BOX(box_top), box_theme);

	gtk_box_append(GTK_BOX(box_top), status_bar);


	gtk_style_context_add_provider_for_display (
				gtk_widget_get_display (GTK_WIDGET (window)),
				GTK_STYLE_PROVIDER (provider),
				GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

	gtk_window_set_child(GTK_WINDOW(window), box_top);


	/* CSS*/
	gtk_widget_set_name ( box_top, "box_top" );
	gtk_widget_set_name (status_bar, "status_bar");


	gtk_widget_add_css_class ( box_annotation, "tab" );
	gtk_widget_add_css_class (header_bar, "headerbutton");
	gtk_widget_add_css_class (btn_annotation, "headerbutton");
	gtk_widget_add_css_class (btn_theme, "headerbutton");
	gtk_widget_add_css_class (btn_configuration, "headerbutton");
	gtk_widget_add_css_class (status_bar, "statusbar");


	gtk_window_present(GTK_WINDOW(window));
}
#include <gtk/gtk.h>

void activate(GtkApplication *app, gpointer user_data) {
	GtkWidget *window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Window");
	gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);



	GtkWidget * btn_annotation = gtk_button_new_with_label ("Annotation");
	GtkWidget * btn_theme = gtk_button_new_with_label ("Theme");
	GtkWidget * btn_configuration = gtk_button_new_with_label ("Configuration");

	GtkWidget * header_bar =  gtk_header_bar_new ();

	gtk_header_bar_pack_start ( GTK_HEADER_BAR (header_bar), btn_annotation);
	gtk_header_bar_pack_start (GTK_HEADER_BAR (header_bar), btn_theme);
	gtk_header_bar_pack_start (GTK_HEADER_BAR (header_bar), btn_configuration);


	gtk_window_set_titlebar ( GTK_WINDOW (window), header_bar);


	GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
	gtk_widget_set_valign(box, GTK_ALIGN_CENTER);

	gtk_window_set_child(GTK_WINDOW(window), box);

	GtkWidget *status_bar = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(status_bar), "Ready...");
	gtk_widget_set_can_focus(status_bar, TRUE);

	gtk_box_append(GTK_BOX(box), status_bar);

	gtk_window_present(GTK_WINDOW(window));
}
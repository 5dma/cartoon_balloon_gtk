#include <gtk/gtk.h>


GAsyncReadyCallback assign_file_name_to_entry() {
	g_print("OMG");
	return NULL;
}

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


	GtkWidget *box_top = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_halign(box_top, GTK_ALIGN_CENTER);
	gtk_widget_set_valign(box_top, GTK_ALIGN_CENTER);


	GtkWidget * box_annotation  = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	GtkWidget * grid_annotation = gtk_grid_new ();

	GtkWidget * lbl_input_image = gtk_label_new ("Input image:");
	GtkWidget * entry_input_image = gtk_entry_new();
	GtkWidget * btn_file_open = gtk_button_new_with_label ("Browse…");

	GCancellable * file_open_cancel = g_cancellable_new ();
	GtkFileDialog * file_open_dialog = gtk_file_dialog_new ();

	//GtkWidget * btn_file_open = gtk_file_dialog_open (file_open_dialog, window, file_open_cancel, assign_file_name_to_entry, NULL);


	gtk_grid_attach ( GTK_GRID(grid_annotation), lbl_input_image, 0, 0, 2, 1);
	gtk_grid_attach ( GTK_GRID(grid_annotation), entry_input_image, 0, 1, 1, 1);
	gtk_grid_attach ( GTK_GRID(grid_annotation), btn_file_open, 1, 1, 1, 1);

	gtk_box_append(GTK_BOX(box_annotation), grid_annotation);


	GtkWidget *status_bar = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(status_bar), "Ready...");
	gtk_widget_set_can_focus(status_bar, TRUE);

	gtk_box_append(GTK_BOX(box_top), box_annotation);

	gtk_box_append(GTK_BOX(box_top), status_bar);


	gtk_window_set_child(GTK_WINDOW(window), box_top);

	gtk_window_present(GTK_WINDOW(window));
}
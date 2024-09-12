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


	/* Build the box containing annotation controls. */
	GtkWidget * box_annotation  = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	GtkWidget * grid_annotation = gtk_grid_new ();

	/* Controls for selecting the input image. */
	GtkWidget * lbl_input_image = gtk_label_new ("Input image:");
	GtkWidget * entry_input_image = gtk_entry_new();
	GtkWidget * btn_file_open = gtk_button_new_with_label ("Browse…");

	GCancellable * file_open_cancel = g_cancellable_new ();
	GtkFileDialog * file_open_dialog = gtk_file_dialog_new ();

	gtk_grid_attach ( GTK_GRID(grid_annotation), lbl_input_image, 0, 0, 2, 1);
	gtk_grid_attach ( GTK_GRID(grid_annotation), entry_input_image, 0, 1, 1, 1);
	gtk_grid_attach ( GTK_GRID(grid_annotation), btn_file_open, 1, 1, 1, 1);


	/* Controls for setting the coordinates. */

	GtkWidget * grid_coordinates = gtk_grid_new ();

	GtkWidget * lbl_text_bottom_left = gtk_label_new ("Text bottom left");
	GtkWidget * lbl_vertex = gtk_label_new ("Vertex");
	GtkWidget * lbl_coordinates_x = gtk_label_new ("x:");
	GtkWidget * lbl_coordinates_y = gtk_label_new ("y:");

	GtkAdjustment * adjustment_coordinates = gtk_adjustment_new (100, 0, 2000, 1, 10, 0);

	GtkWidget * spin_text_bottom_left_x = gtk_spin_button_new (adjustment_coordinates, 2, 4);
	GtkWidget * spin_text_bottom_left_y = gtk_spin_button_new (adjustment_coordinates, 2, 4);
	GtkWidget * spin_vertex_x = gtk_spin_button_new (adjustment_coordinates, 2, 4);
	GtkWidget * spin_vertex_y = gtk_spin_button_new (adjustment_coordinates, 2, 4);
	GtkWidget * btn_point_text_bottom = gtk_button_new_with_label("Point");
	GtkWidget * btn_point_vertex = gtk_button_new_with_label("Point");

	/* Row 0*/
	gtk_grid_attach ( GTK_GRID(grid_coordinates), lbl_text_bottom_left, 1, 0, 1, 1);
	gtk_grid_attach ( GTK_GRID(grid_coordinates), lbl_vertex, 2, 0, 1, 1);
	/* Row 1 */
	gtk_grid_attach ( GTK_GRID(grid_coordinates), lbl_coordinates_x, 0, 1, 1, 1);
	gtk_grid_attach ( GTK_GRID(grid_coordinates), spin_text_bottom_left_x, 1, 1, 1, 1);
	gtk_grid_attach ( GTK_GRID(grid_coordinates), spin_vertex_x, 2, 1, 1, 1);
	/* Row 2 */
	gtk_grid_attach ( GTK_GRID(grid_coordinates), lbl_coordinates_y, 0, 2, 1, 1);
	gtk_grid_attach ( GTK_GRID(grid_coordinates), spin_text_bottom_left_y, 1, 2, 1, 1);
	gtk_grid_attach ( GTK_GRID(grid_coordinates), spin_vertex_y, 2, 2, 1, 1);
	/* Row 3 */
	gtk_grid_attach ( GTK_GRID(grid_coordinates), btn_point_text_bottom, 1, 3, 1, 1);
	gtk_grid_attach ( GTK_GRID(grid_coordinates), btn_point_vertex, 2, 3, 1, 1);


	gtk_box_append(GTK_BOX(box_annotation), grid_annotation);
	gtk_box_append(GTK_BOX(box_annotation), grid_coordinates);

	GtkWidget *status_bar = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(status_bar), "Ready...");
	gtk_widget_set_can_focus(status_bar, TRUE);

	gtk_box_append(GTK_BOX(box_top), box_annotation);

	gtk_box_append(GTK_BOX(box_top), status_bar);


	gtk_window_set_child(GTK_WINDOW(window), box_top);

	gtk_window_present(GTK_WINDOW(window));
}
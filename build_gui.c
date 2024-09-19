#include <gtk/gtk.h>


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
  


	/* Build the box containing annotation controls. */
	GtkWidget * box_annotation  = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	GtkWidget * grid_annotation = gtk_grid_new ();

	/* Controls for selecting the input image. */
	GtkWidget * lbl_input_image = gtk_label_new ("Input image:");
	gtk_widget_set_halign (lbl_input_image, GTK_ALIGN_START);

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

	gtk_widget_set_halign (lbl_text_bottom_left, GTK_ALIGN_START);
	gtk_widget_set_halign (lbl_vertex, GTK_ALIGN_START);
	gtk_widget_set_halign (lbl_coordinates_x, GTK_ALIGN_START);
	gtk_widget_set_halign (lbl_coordinates_y, GTK_ALIGN_START);


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

	/* Controls for exported image's width and theme selection. */

	GtkWidget * box_width_theme  = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	GtkWidget * lbl_new_width = gtk_label_new ("New width:");
	GtkWidget * lbl_theme = gtk_label_new ("Theme:");
	
	gtk_widget_set_halign (lbl_new_width, GTK_ALIGN_START);
	gtk_widget_set_halign (lbl_theme, GTK_ALIGN_START);

	GtkWidget * spin_new_width = gtk_spin_button_new (adjustment_coordinates, 2, 4);

	const char boy[] = "Boy";
	const char girl[] = "Girl";
	const char * theme_names[] = {boy, girl, NULL};
 	GtkWidget * dropdown_theme = gtk_drop_down_new_from_strings (theme_names);


	/* Controls for text string and export button. */

	GtkWidget * grid_text_string_export = gtk_grid_new ();
	GtkWidget * lbl_text_string = gtk_label_new ("Text string:");
	GtkWidget * entry_text_string = gtk_entry_new();
	GtkWidget * btn_export = gtk_button_new_with_label("Export");

	gtk_grid_attach ( GTK_GRID(grid_text_string_export), lbl_text_string, 0,0,1,2);
	gtk_grid_attach ( GTK_GRID(grid_text_string_export), entry_text_string, 0,1,1,1);
	gtk_grid_attach ( GTK_GRID(grid_text_string_export), btn_export, 1,1,1,1);

	gtk_box_append(GTK_BOX(box_width_theme), lbl_new_width);
	gtk_box_append(GTK_BOX(box_width_theme), spin_new_width);
	gtk_box_append(GTK_BOX(box_width_theme), lbl_theme);
	gtk_box_append(GTK_BOX(box_width_theme), dropdown_theme);

	GtkWidget* picture_preview = gtk_picture_new_for_filename ("/home/abba/Ronen_Letters/graphic_quotes/knesset.png");

	gtk_box_append(GTK_BOX(box_annotation), grid_annotation);
	gtk_box_append(GTK_BOX(box_annotation), grid_coordinates);
	gtk_box_append(GTK_BOX(box_annotation), box_width_theme);
	gtk_box_append(GTK_BOX(box_annotation), grid_text_string_export);
	gtk_box_append(GTK_BOX(box_annotation), picture_preview);


	GtkWidget *status_bar = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(status_bar), "Ready...");
	gtk_widget_set_sensitive (status_bar, FALSE);
	gtk_widget_set_hexpand (status_bar, TRUE);


	gtk_box_append(GTK_BOX(box_top), box_annotation);

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

	gtk_widget_add_css_class (lbl_coordinates_x, "horizontal_field_label");
	gtk_widget_add_css_class (lbl_coordinates_y, "horizontal_field_label");
	gtk_widget_add_css_class (lbl_new_width, "horizontal_field_label");
	gtk_widget_add_css_class (lbl_theme, "horizontal_field_label");
	gtk_widget_add_css_class (lbl_theme, "horizontal_field_label_interior");

	gtk_widget_add_css_class(grid_coordinates,"grid_coordinates");
	gtk_widget_add_css_class(box_width_theme,"grid_coordinates");
	gtk_widget_add_css_class(grid_text_string_export,"grid_coordinates");





	gtk_window_present(GTK_WINDOW(window));
}
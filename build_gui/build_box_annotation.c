#include <gtk/gtk.h>



GtkWidget * build_box_annotation() {

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

	gtk_widget_add_css_class (box_annotation, "tab" );

	gtk_widget_add_css_class (lbl_coordinates_x, "horizontal_field_label");
	gtk_widget_add_css_class (lbl_coordinates_y, "horizontal_field_label");
	gtk_widget_add_css_class (lbl_new_width, "horizontal_field_label");
	gtk_widget_add_css_class (lbl_theme, "horizontal_field_label");
	gtk_widget_add_css_class (lbl_theme, "horizontal_field_label_interior");

	gtk_widget_add_css_class(grid_coordinates,"grid_coordinates");
	gtk_widget_add_css_class(box_width_theme,"grid_coordinates");
	gtk_widget_add_css_class(grid_text_string_export,"grid_coordinates");

	return box_annotation;

}
#include <gtk/gtk.h>
#include <headers.h>
/**
 * @file build_box_annotation.c
 * @brief Contains a function for building the GUI tab `box_annotation`.
 */

/**
 * Builds the box containing annotation controls.
 @param user_data Pointer to user data.
 @return Widget with the annotation controls.
 */
GtkWidget *build_box_annotation(User_Data *user_data) {

	/* Appears in the top button bar*/
	GtkWidget *btn_annotation = gtk_button_new_with_label("Annotation");

	GtkWidget *box_annotation  = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	GtkWidget *grid_annotation = gtk_grid_new ();
	GtkWidget *box_previews  = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	GtkWidget *box_annotation_controls  = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);

	/* Controls for selecting the input image. */
	GtkWidget *lbl_input_image = gtk_label_new ("Input image:");
	gtk_widget_set_halign (lbl_input_image, GTK_ALIGN_START);


	GtkEntryBuffer *buffer_input_image = gtk_entry_buffer_new (NULL, -1);
	GtkWidget *entry_input_image = gtk_entry_new();
	gtk_entry_set_buffer (GTK_ENTRY(entry_input_image), buffer_input_image);

	GtkWidget *btn_file_open = gtk_button_new_with_label ("Browse…");

	gtk_grid_attach ( GTK_GRID(grid_annotation), lbl_input_image, 0, 0, 2, 1);
	gtk_grid_attach ( GTK_GRID(grid_annotation), entry_input_image, 0, 1, 1, 1);
	gtk_grid_attach ( GTK_GRID(grid_annotation), btn_file_open, 1, 1, 1, 1);


	/* Controls for setting the coordinates. */

	GtkWidget *grid_coordinates = gtk_grid_new ();

	GtkWidget *lbl_text_bottom_left = gtk_label_new ("Text bottom left");
	GtkWidget *lbl_vertex = gtk_label_new ("Vertex");
	GtkWidget *lbl_coordinates_x = gtk_label_new ("x:");
	GtkWidget *lbl_coordinates_y = gtk_label_new ("y:");

	gtk_widget_set_halign (lbl_text_bottom_left, GTK_ALIGN_START);
	gtk_widget_set_halign (lbl_vertex, GTK_ALIGN_START);
	gtk_widget_set_halign (lbl_coordinates_x, GTK_ALIGN_START);
	gtk_widget_set_halign (lbl_coordinates_y, GTK_ALIGN_START);


	GtkAdjustment *adjustment_text_bottom_left_x = gtk_adjustment_new (100, 0, 2000, 1, 10, 5);
	GtkAdjustment *adjustment_text_bottom_left_y = gtk_adjustment_new (100, 0, 2000, 1, 10, 5);
	GtkAdjustment *adjustment_vertex_x = gtk_adjustment_new (100, 0, 2000, 1, 10, 5);
	GtkAdjustment *adjustment_vertex_y = gtk_adjustment_new (100, 0, 2000, 1, 10, 5);

	GtkWidget *spin_text_bottom_left_x = gtk_spin_button_new (adjustment_text_bottom_left_x, 2, 0);
	GtkWidget *spin_text_bottom_left_y = gtk_spin_button_new (adjustment_text_bottom_left_y, 2, 0);
	GtkWidget *spin_vertex_x = gtk_spin_button_new (adjustment_vertex_x, 2, 0);
	GtkWidget *spin_vertex_y = gtk_spin_button_new (adjustment_vertex_y, 2, 0);
	GtkWidget *btn_point_text_bottom = gtk_button_new_with_label("Point");
	GtkWidget *btn_point_vertex = gtk_button_new_with_label("Point");

	gtk_widget_set_halign (btn_point_text_bottom, GTK_ALIGN_START);


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

	GtkWidget *box_width_theme  = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	GtkWidget *lbl_new_width = gtk_label_new ("New width:");
	GtkWidget *lbl_theme = gtk_label_new ("Theme:");
	
	gtk_widget_set_halign (lbl_new_width, GTK_ALIGN_START);
	gtk_widget_set_halign (lbl_theme, GTK_ALIGN_START);

	GtkAdjustment *adjustment_new_width = gtk_adjustment_new (100, 0, 2000, 1, 10, 5);
	GtkWidget *spin_new_width = gtk_spin_button_new (adjustment_new_width, 2, 0);

	GtkWidget *dropdown_theme = gtk_drop_down_new (NULL, NULL);

	/* Controls for text string and export button. */

	GtkWidget *grid_text_string_export = gtk_grid_new ();
	GtkWidget *lbl_text_string = gtk_label_new ("Text string:");

	GtkEntryBuffer *buffer_text_string = gtk_entry_buffer_new ("I will barf", -1);
	GtkWidget *entry_text_string = gtk_entry_new();
	gtk_entry_set_buffer (GTK_ENTRY(entry_text_string), buffer_text_string);

	GtkWidget *btn_export = gtk_button_new_with_label("Export");

	gtk_grid_attach ( GTK_GRID(grid_text_string_export), lbl_text_string, 0,0,1,2);
	gtk_grid_attach ( GTK_GRID(grid_text_string_export), entry_text_string, 0,1,1,1);
	gtk_grid_attach ( GTK_GRID(grid_text_string_export), btn_export, 1,1,1,1);

	gtk_box_append(GTK_BOX(box_width_theme), lbl_new_width);
	gtk_box_append(GTK_BOX(box_width_theme), spin_new_width);
	gtk_box_append(GTK_BOX(box_width_theme), lbl_theme);
	gtk_box_append(GTK_BOX(box_width_theme), dropdown_theme);

	/* Control for the image preview. */
	GtkWidget *original_preview = gtk_picture_new();
	GtkWidget *annotated_preview = gtk_drawing_area_new();
	gtk_box_append(GTK_BOX(box_previews), original_preview);
	gtk_box_append(GTK_BOX(box_previews), annotated_preview);
	gtk_widget_set_size_request (original_preview, 200, -1);
	//gtk_widget_set_size_request (annotated_preview, 200, -1);
	gtk_drawing_area_set_content_height (GTK_DRAWING_AREA(annotated_preview), 120);
	gtk_drawing_area_set_content_width (GTK_DRAWING_AREA(annotated_preview), 200);
	
	gtk_box_append(GTK_BOX(box_annotation_controls), grid_annotation);
	gtk_box_append(GTK_BOX(box_annotation_controls), grid_coordinates);
	gtk_box_append(GTK_BOX(box_annotation_controls), box_width_theme);
	gtk_box_append(GTK_BOX(box_annotation_controls), grid_text_string_export);

	gtk_box_append(GTK_BOX(box_annotation), box_annotation_controls);
	gtk_box_append(GTK_BOX(box_annotation), box_previews);

	gtk_widget_add_css_class (box_annotation, "tab" );
	gtk_widget_add_css_class (box_annotation_controls, "tab" );
	gtk_widget_add_css_class (box_previews, "tab" );

	gtk_widget_add_css_class (lbl_text_bottom_left, "horizontal_field_label");
	gtk_widget_add_css_class (lbl_coordinates_x, "horizontal_field_label");
	gtk_widget_add_css_class (lbl_coordinates_y, "horizontal_field_label");
	gtk_widget_add_css_class (lbl_new_width, "horizontal_field_label");
	gtk_widget_add_css_class (lbl_theme, "horizontal_field_label");
	gtk_widget_add_css_class (lbl_theme, "horizontal_field_label_interior");

	gtk_widget_add_css_class (spin_text_bottom_left_x, "horizontal_field_label");
	gtk_widget_add_css_class (spin_text_bottom_left_y, "horizontal_field_label");

	gtk_widget_add_css_class(grid_coordinates,"grid_coordinates");
	gtk_widget_add_css_class(box_width_theme,"grid_coordinates");
	gtk_widget_add_css_class(grid_text_string_export,"grid_coordinates");

	gtk_widget_add_css_class(original_preview,"preview");
	gtk_widget_add_css_class(annotated_preview,"preview");

	gtk_editable_set_alignment (GTK_EDITABLE(spin_text_bottom_left_x), 1.0);
	gtk_editable_set_alignment (GTK_EDITABLE(spin_text_bottom_left_y), 1.0);
	gtk_editable_set_alignment (GTK_EDITABLE(spin_vertex_x), 1.0); 
	gtk_editable_set_alignment (GTK_EDITABLE(spin_vertex_y), 1.0);
	gtk_editable_set_alignment(GTK_EDITABLE(spin_new_width), 1.0);

	/* 
		Create filters applied to the GtkFileChooser opened in select_input_file(). 
		The filters are sunk to file choosers when they are created, and destroyed along
		with the file chooser when closed.
	*/
	GtkFileFilter *file_filter = gtk_file_filter_new ();
	gtk_file_filter_add_suffix (file_filter, "png");
	gtk_file_filter_add_suffix (file_filter, "jpg");
	gtk_file_filter_add_suffix (file_filter, "gif");

	/* Save widgets in User_Data struct. */
	Gui_Data_Annotation *gui_data_annotation = user_data->gui_data->gui_data_annotation;
	gui_data_annotation->btn_annotation = btn_annotation;
	gui_data_annotation->entry_input_image = entry_input_image;
	gui_data_annotation->btn_file_open = btn_file_open;
	gui_data_annotation->spin_text_bottom_left_x = spin_text_bottom_left_x;
	gui_data_annotation->spin_text_bottom_left_y = spin_text_bottom_left_y;
	gui_data_annotation->spin_vertex_x = spin_vertex_x;
	gui_data_annotation->spin_vertex_y = spin_vertex_y;
	gui_data_annotation->btn_point_vertex = btn_point_vertex;
	gui_data_annotation->btn_point_text_bottom = btn_point_text_bottom;
	gui_data_annotation->spin_new_width = spin_new_width;
	gui_data_annotation->dropdown_theme = dropdown_theme;
	gui_data_annotation->entry_text_string = entry_text_string;
	gui_data_annotation->btn_export = btn_export;
	gui_data_annotation->original_preview = original_preview;
	gui_data_annotation->annotated_preview = annotated_preview;
	gui_data_annotation->file_filter = file_filter;

	/* At program start, the annotation tab is visible. */
	gtk_widget_set_visible(box_annotation, TRUE);

	return box_annotation;

}
#include <gtk/gtk.h>
#include <headers.h>

/**
 * @file build_box_configuration.c
 * @brief Contains a function for building the GUI tab `box_configuration`.
 */

/**
 * Builds the box containing configuration controls, and returns the associated widget.
 */
GtkWidget *build_box_configuration(User_Data *user_data) {

	/* Instantiate the box containing configuration controls. */
	GtkWidget *box_configuration  = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);

	/* Adjustments for the various spin boxes. */

	GtkAdjustment *adjustment_max_annotation_length = gtk_adjustment_new (125, 0, 256, 1, 10, 0);
	GtkAdjustment *adjustment_padding = gtk_adjustment_new (125, 0, 256, 1, 10, 0);
	GtkAdjustment *adjustment_elevation = gtk_adjustment_new (125, 0, 256, 1, 10, 0);
	GtkAdjustment *adjustment_space = gtk_adjustment_new (125, 0, 256, 1, 10, 0);
	GtkAdjustment *adjustment_top_margin = gtk_adjustment_new (125, 0, 256, 1, 10, 0);
	GtkAdjustment *adjustment_rounding_radius = gtk_adjustment_new (125, 0, 256, 1, 10, 0);

	/* Instantiate labels. */
	GtkWidget *lbl_max_annotation_length = gtk_label_new ("Maximal annotation length:");
	GtkWidget *lbl_padding = gtk_label_new ("Padding:");
	GtkWidget *lbl_elevation = gtk_label_new ("Elevation:");
	GtkWidget *lbl_space = gtk_label_new ("Space:");
	GtkWidget *lbl_top_margin = gtk_label_new ("Top margin:");
	GtkWidget *lbl_rounding_radius = gtk_label_new ("Rounding radius:");

	/* Instantiate spin buttons. */
	GtkWidget *spin_max_annotation_length = gtk_spin_button_new (adjustment_max_annotation_length, 2, 0);
	GtkWidget *spin_padding = gtk_spin_button_new (adjustment_padding, 2, 0);
	GtkWidget *spin_elevation = gtk_spin_button_new (adjustment_elevation, 2, 0);
	GtkWidget *spin_space = gtk_spin_button_new (adjustment_space, 2, 0);
	GtkWidget *spin_top_margin = gtk_spin_button_new (adjustment_top_margin, 2, 0);
	GtkWidget *spin_rounding_radius = gtk_spin_button_new (adjustment_rounding_radius, 2, 0);

	gtk_widget_set_halign (lbl_padding, GTK_ALIGN_START);
	gtk_widget_set_halign (lbl_elevation, GTK_ALIGN_START);
	gtk_widget_set_halign (lbl_space, GTK_ALIGN_START);
	gtk_widget_set_halign (lbl_top_margin, GTK_ALIGN_START);
	gtk_widget_set_halign (lbl_rounding_radius, GTK_ALIGN_START);

	

	/* Grid for the configuration controls. */
	
	GtkWidget *grid_configuration = gtk_grid_new ();

	/* Row 0*/
	gtk_grid_attach ( GTK_GRID(grid_configuration), lbl_max_annotation_length, 0, 0, 1, 1);
	gtk_grid_attach ( GTK_GRID(grid_configuration), spin_max_annotation_length, 1, 0, 1, 1);

	/* Row 1*/
	gtk_grid_attach ( GTK_GRID(grid_configuration), lbl_padding, 0, 1, 1, 1);
	gtk_grid_attach ( GTK_GRID(grid_configuration), spin_padding, 1, 1, 1, 1);


	/* Row 2 */
	gtk_grid_attach ( GTK_GRID(grid_configuration), lbl_elevation, 0, 2, 1, 1);
	gtk_grid_attach ( GTK_GRID(grid_configuration), spin_elevation, 1, 2, 1, 1);

	/* Row 3 */
	gtk_grid_attach ( GTK_GRID(grid_configuration), lbl_space, 0, 3, 1, 1);
	gtk_grid_attach ( GTK_GRID(grid_configuration), spin_space, 1, 3, 1, 1);

	/* Row 4 */
	gtk_grid_attach ( GTK_GRID(grid_configuration), lbl_top_margin, 0, 4, 1, 1);
	gtk_grid_attach ( GTK_GRID(grid_configuration), spin_top_margin, 1, 4, 1, 1);

	/* Row 5 */
	gtk_grid_attach ( GTK_GRID(grid_configuration), lbl_rounding_radius, 0, 5, 1, 1);
	gtk_grid_attach ( GTK_GRID(grid_configuration), spin_rounding_radius, 1, 5, 1, 1);

	gtk_box_append(GTK_BOX(box_configuration), grid_configuration);


	gtk_widget_add_css_class (box_configuration, "tab" );
	gtk_widget_add_css_class (lbl_max_annotation_length, "horizontal_field_label");
	gtk_widget_add_css_class (lbl_padding, "horizontal_field_label");
	gtk_widget_add_css_class (lbl_elevation, "horizontal_field_label");
	gtk_widget_add_css_class (lbl_space, "horizontal_field_label");
	gtk_widget_add_css_class (lbl_top_margin, "horizontal_field_label");

	gtk_editable_set_alignment(GTK_EDITABLE(spin_max_annotation_length), 1.0);
	gtk_editable_set_alignment(GTK_EDITABLE(spin_padding), 1.0);
	gtk_editable_set_alignment(GTK_EDITABLE(spin_elevation), 1.0);
	gtk_editable_set_alignment(GTK_EDITABLE(spin_space), 1.0);
	gtk_editable_set_alignment(GTK_EDITABLE(spin_top_margin), 1.0);
	gtk_editable_set_alignment(GTK_EDITABLE(spin_rounding_radius), 1.0);

	/* Allow a maximum of five digits (99,999 characters) to specify an annotation's length. */
	gtk_editable_set_max_width_chars (GTK_EDITABLE(spin_max_annotation_length), 5);

	gtk_widget_add_css_class(grid_configuration,"grid_coordinates");

	/* At program start, the configuration tab is invisible. */
	gtk_widget_set_visible(box_configuration, FALSE);


	/* Save widgets in User_Data struct. */
	Gui_Data_Configuration *gui_data_configuration = user_data->gui_data->gui_data_configuration;
	gui_data_configuration->spin_max_annotation_length = spin_max_annotation_length;
	gui_data_configuration->spin_padding = spin_padding;
	gui_data_configuration->spin_elevation = spin_elevation;
	gui_data_configuration->spin_space = spin_space;
	gui_data_configuration->spin_top_margin = spin_top_margin;
	gui_data_configuration->spin_rounding_radius = spin_rounding_radius;

	return box_configuration;

}
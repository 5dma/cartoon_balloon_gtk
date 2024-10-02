#include <gtk/gtk.h>
#include "../headers.h"

/**
 * @file build_box_configuration.c
 * @brief Builds the GUI tab `box_configuration`.
 */

/**
* Builds the box containing configuration controls, and returns the associated widget.
*/
GtkWidget *build_box_configuration(User_Data *user_data) {

	/* Build the box containing configuration controls. */
	GtkWidget *box_configuration  = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);

	/* Controls for configuring the theme. */

	GtkAdjustment *adjustment_max_annotation_length = gtk_adjustment_new (125, 0, 256, 1, 10, 0);
	GtkAdjustment *adjustment_padding = gtk_adjustment_new (125, 0, 256, 1, 10, 0);
	GtkAdjustment *adjustment_elevation = gtk_adjustment_new (125, 0, 256, 1, 10, 0);
	GtkAdjustment *adjustment_space = gtk_adjustment_new (125, 0, 256, 1, 10, 0);
	GtkAdjustment *adjustment_top_margin = gtk_adjustment_new (125, 0, 256, 1, 10, 0);


	GtkWidget *lbl_max_annotation_length = gtk_label_new ("Maximal annotation length:");
	GtkWidget *lbl_padding = gtk_label_new ("Padding:");
	GtkWidget *lbl_elevation = gtk_label_new ("Elevation:");
	GtkWidget *lbl_space = gtk_label_new ("Space:");
	GtkWidget *lbl_top_margin = gtk_label_new ("Top margin:");


	GtkWidget *spin_max_annotation_length = gtk_spin_button_new (adjustment_max_annotation_length, 2, 0);
	GtkWidget *spin_padding = gtk_spin_button_new (adjustment_padding, 2, 0);
	GtkWidget *spin_elevation = gtk_spin_button_new (adjustment_elevation, 2, 0);
	GtkWidget *spin_space = gtk_spin_button_new (adjustment_space, 2, 0);
	GtkWidget *spin_top_margin = gtk_spin_button_new (adjustment_top_margin, 2, 0);

	gtk_widget_set_halign (lbl_padding, GTK_ALIGN_START);
	gtk_widget_set_halign (lbl_elevation, GTK_ALIGN_START);
	gtk_widget_set_halign (lbl_space, GTK_ALIGN_START);
	gtk_widget_set_halign (lbl_top_margin, GTK_ALIGN_START);

	

	/* Grid for styling the text */
	
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

	
	/* Controls for saving the configuration */
	GtkWidget *btn_save = gtk_button_new_with_label("Save");
	gtk_widget_set_hexpand (btn_save, FALSE);
	gtk_widget_set_halign (btn_save, GTK_ALIGN_START);


	gtk_box_append(GTK_BOX(box_configuration), grid_configuration);
	gtk_box_append(GTK_BOX(box_configuration), btn_save);


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

	gtk_editable_set_max_width_chars (GTK_EDITABLE(spin_max_annotation_length), 5);

	gtk_widget_add_css_class(grid_configuration,"grid_coordinates");
	gtk_widget_set_visible(box_configuration, FALSE);

	user_data->gui_data->gui_data_configuration->spin_max_annotation_length = spin_max_annotation_length;
	user_data->gui_data->gui_data_configuration->spin_padding = spin_padding;
	user_data->gui_data->gui_data_configuration->spin_elevation = spin_elevation;
	user_data->gui_data->gui_data_configuration->spin_space = spin_space;
	user_data->gui_data->gui_data_configuration->spin_top_margin = spin_top_margin;


	return box_configuration;

}
#include <gtk/gtk.h>
#include "../headers.h"

/**
 * @file build_box_theme.c
 * @brief Builds the GUI tab `box_theme`.
 */

/**
 * Builds the box containing theme controls, and returns the associated widget.
 */
GtkWidget *build_box_theme(User_Data *user_data) {

	/* Build the box containing theme controls. */
	GtkWidget *box_theme  = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);

	/* Controls for selecting the theme. */

	GtkWidget *lbl_name = gtk_label_new ("Name:");
	GtkWidget *dropdown_theme = gtk_drop_down_new (NULL, NULL);
	GtkWidget *entry_new_theme = gtk_entry_new ();

	GtkWidget *box_theme_selector  = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	
	gtk_box_append(GTK_BOX(box_theme_selector), lbl_name);
	gtk_box_append(GTK_BOX(box_theme_selector), dropdown_theme);
	gtk_box_append(GTK_BOX(box_theme_selector), entry_new_theme);

	/* Controls for styling the text. */

	GtkWidget *lbl_text = gtk_label_new ("Text");
	GtkWidget *lbl_font = gtk_label_new ("Font:");
	GtkWidget *lbl_color = gtk_label_new ("Color:");
	GtkWidget *lbl_size = gtk_label_new ("Size:");

	gtk_widget_set_halign (lbl_text, GTK_ALIGN_START);
	gtk_widget_set_halign (lbl_font, GTK_ALIGN_START);
	gtk_widget_set_halign (lbl_color, GTK_ALIGN_START);
	gtk_widget_set_halign (lbl_size, GTK_ALIGN_START);

	GtkAdjustment *adjustment_font_size = gtk_adjustment_new (18, 0, 96, 1, 10, 0);

	GtkWidget *entry_font_name = gtk_entry_new();
	GtkWidget *entry_font_color = gtk_entry_new();
	GtkWidget *spin_font_size = gtk_spin_button_new (adjustment_font_size, 2, 0);
	

	GtkWidget *btn_font_name_picker = gtk_button_new_with_label("Choose…");
	GtkWidget *btn_font_color_picker = gtk_button_new_with_label("Choose…");

	/* Grid for styling the text */
	GtkWidget *grid_text = gtk_grid_new ();

	/* Row 1*/
	gtk_grid_attach ( GTK_GRID(grid_text), lbl_text, 0, 0, 3, 1);

	/* Row 1*/
	gtk_grid_attach ( GTK_GRID(grid_text), lbl_font, 0, 1, 1, 1);
	gtk_grid_attach ( GTK_GRID(grid_text), entry_font_name, 1, 1, 1, 1);
	gtk_grid_attach ( GTK_GRID(grid_text), btn_font_name_picker, 2, 1, 1, 1);

	/* Row 2 */
	gtk_grid_attach ( GTK_GRID(grid_text), lbl_color, 0, 2, 1, 1);
	gtk_grid_attach ( GTK_GRID(grid_text), entry_font_color, 1, 2, 1, 1);
	gtk_grid_attach ( GTK_GRID(grid_text), btn_font_color_picker, 2, 2, 1, 1);

	/* Row 3 */
	gtk_grid_attach ( GTK_GRID(grid_text), lbl_size, 0, 3, 1, 1);
	gtk_grid_attach ( GTK_GRID(grid_text), spin_font_size, 1, 3, 1, 1);



	/* Controls for styling the balloon. */

	GtkWidget *lbl_balloon = gtk_label_new ("Balloon");
	GtkWidget *lbl_fill_color = gtk_label_new ("Fill color:");
	GtkWidget *lbl_stroke_color = gtk_label_new ("Stroke color:");
	GtkWidget *lbl_stroke_width = gtk_label_new ("Stroke width:");

	gtk_widget_set_halign (lbl_balloon, GTK_ALIGN_START);
	gtk_widget_set_halign (lbl_fill_color, GTK_ALIGN_START);
	gtk_widget_set_halign (lbl_stroke_color, GTK_ALIGN_START);
	gtk_widget_set_halign (lbl_stroke_width, GTK_ALIGN_START);

	GtkAdjustment *adjustment_stroke_width = gtk_adjustment_new (5, 0, 10, 1, 5, 0);

	GtkWidget *entry_fill_color = gtk_entry_new();
	GtkWidget *entry_stroke_color = gtk_entry_new();
	GtkWidget *spin_stroke_width = gtk_spin_button_new (adjustment_stroke_width, 2, 0);

	GtkWidget *btn_balloon_color_picker = gtk_button_new_with_label("Choose…");
	GtkWidget *btn_stroke_color_picker = gtk_button_new_with_label("Choose…");


	/* Grid for styling the balloon */
	GtkWidget *grid_balloon = gtk_grid_new ();

	/* Row 1*/
	gtk_grid_attach ( GTK_GRID(grid_balloon), lbl_balloon, 0, 0, 3, 1);

	/* Row 1*/
	gtk_grid_attach ( GTK_GRID(grid_balloon), lbl_fill_color, 0, 1, 1, 1);
	gtk_grid_attach ( GTK_GRID(grid_balloon), entry_fill_color, 1, 1, 1, 1);
	gtk_grid_attach ( GTK_GRID(grid_balloon), btn_balloon_color_picker, 2, 1, 1, 1);

	/* Row 2 */
	gtk_grid_attach ( GTK_GRID(grid_balloon), lbl_stroke_color, 0, 2, 1, 1);
	gtk_grid_attach ( GTK_GRID(grid_balloon), entry_stroke_color, 1, 2, 1, 1);
	gtk_grid_attach ( GTK_GRID(grid_balloon), btn_stroke_color_picker, 2, 2, 1, 1);

	/* Row 3 */
	gtk_grid_attach ( GTK_GRID(grid_balloon), lbl_stroke_width, 0, 3, 1, 1);
	gtk_grid_attach ( GTK_GRID(grid_balloon), spin_stroke_width, 1, 3, 1, 1);

	GtkWidget*picture_balloon = gtk_picture_new_for_filename ("/home/abba/.cartoon_balloon/balloon_preview.png");

	/* Controls for save, copy, and delete theme */
	GtkWidget *btn_save = gtk_button_new_with_label("Save");
	GtkWidget *btn_copy = gtk_button_new_with_label("Copy");
	GtkWidget *btn_delete = gtk_button_new_with_label("Delete");

	GtkWidget *box_save_copy_delete  = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	
	gtk_box_append(GTK_BOX(box_save_copy_delete), btn_save);
	gtk_box_append(GTK_BOX(box_save_copy_delete), btn_copy);
	gtk_box_append(GTK_BOX(box_save_copy_delete), btn_delete);


	/* Grid for font controls, balloon controls, and preview */
	GtkWidget *grid_font_balloon_preview = gtk_grid_new();
	gtk_grid_attach ( GTK_GRID(grid_font_balloon_preview), grid_text, 0, 0, 1, 1);
	gtk_grid_attach ( GTK_GRID(grid_font_balloon_preview), grid_balloon, 0, 1, 1, 1);
	gtk_grid_attach ( GTK_GRID(grid_font_balloon_preview), picture_balloon, 1, 0, 1, 2);

	gtk_box_append(GTK_BOX(box_theme), box_theme_selector);
	gtk_box_append(GTK_BOX(box_theme), grid_font_balloon_preview);
	gtk_box_append(GTK_BOX(box_theme), box_save_copy_delete);



	gtk_widget_add_css_class (box_theme, "tab" );
	gtk_widget_add_css_class (dropdown_theme, "horizontal_field_label");
	
	gtk_widget_add_css_class (lbl_name, "horizontal_field_label");
	gtk_widget_add_css_class (lbl_font, "horizontal_field_label");
	gtk_widget_add_css_class (lbl_color, "horizontal_field_label");
	gtk_widget_add_css_class (lbl_size, "horizontal_field_label");

	gtk_widget_add_css_class (lbl_fill_color, "horizontal_field_label");
	gtk_widget_add_css_class (lbl_stroke_color, "horizontal_field_label");
	gtk_widget_add_css_class (lbl_stroke_width, "horizontal_field_label");


	gtk_widget_add_css_class(grid_text,"grid_coordinates");
	gtk_widget_add_css_class(grid_balloon ,"grid_coordinates");

	gtk_editable_set_alignment(GTK_EDITABLE(spin_font_size), 1.0);
	gtk_editable_set_alignment(GTK_EDITABLE(spin_stroke_width), 1.0);

	gtk_widget_set_sensitive (entry_new_theme, FALSE);


	gtk_widget_set_visible(box_theme, FALSE);

	user_data->gui_data->gui_data_theme->dropdown_theme = dropdown_theme;
	user_data->gui_data->gui_data_theme->entry_new_theme = entry_new_theme;
	user_data->gui_data->gui_data_theme->entry_font_name = entry_font_name;
	user_data->gui_data->gui_data_theme->entry_font_color = entry_font_color;
	user_data->gui_data->gui_data_theme->entry_fill_color = entry_fill_color;
	user_data->gui_data->gui_data_theme->spin_font_size = spin_font_size;
	user_data->gui_data->gui_data_theme->entry_font_color = entry_font_color;
	user_data->gui_data->gui_data_theme->entry_stroke_color = entry_stroke_color;
	user_data->gui_data->gui_data_theme->spin_stroke_width = spin_stroke_width;

	return box_theme;

}
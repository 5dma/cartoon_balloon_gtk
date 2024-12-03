#include <headers.h>
/**
 * @file annotation_tab_callbacks.c
 * @brief Contains callback functions for controls in the **Annotations** tab.
 */

/**
Fired when user clicks the **Annotation** button, and displays the **Annotations** tab. This function shows the **Annotation** tab and hides the other two tabs.
 */
void show_annotation_tab(GtkWidget *widget, gpointer data)
{
	Gui_Data *gui_data = (Gui_Data *)data;

	gtk_widget_set_visible(gui_data->gui_data_annotation->box_annotation, TRUE);
	gtk_widget_set_visible(gui_data->box_theme, FALSE);
	gtk_widget_set_visible(gui_data->gui_data_configuration->box_configuration, FALSE);
}

/**
Fired when the user selects a file in the file open dialog box. The processing includes the following:
* - Storing the path of the selected file.
* - Displaying the path in the GUI.
* - Displaying the file in the picture preview widget.
* - Storing the image's width and height.
*/
static void on_open_response(GtkDialog *dialog, int response, gpointer data)
{

	User_Data *user_data = (User_Data *)data;

	if (response == GTK_RESPONSE_ACCEPT)
	{
		GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
		GFile *file = gtk_file_chooser_get_file(chooser);

		gchar *file_name = g_file_get_parse_name(file);

		gtk_editable_set_text (GTK_EDITABLE(user_data->gui_data->gui_data_annotation->entry_input_image), file_name);

		gtk_picture_set_file(GTK_PICTURE(user_data->gui_data->gui_data_annotation->picture_preview), file);

		gdk_pixbuf_get_file_info(g_file_get_parse_name(file), &(user_data->annotation->dimensions_original_image.width), &(user_data->annotation->dimensions_original_image.height));

		g_object_unref(file);
		g_free(file_name);
	}

	gtk_window_destroy(GTK_WINDOW(dialog));
}

/**
 * Fired when the user enters the image preview with the mouse. When the mouse enters the preview widget, we know the following measurements:
* - The dimensions of the preview widget.
* - The dimensions of the original image.
* Using these two dimensions, we can compute the ratio for scaling the original image so that it fits in the preview. In particular, the ratio is the preview widget's height divided by the original image's height. This bounding box is used in on_mouse_motion_image().
 */
void on_mouse_enter_image(GtkEventControllerMotion *self, gdouble x, gdouble y, gpointer data)
{

	User_Data *user_data = (User_Data *)data;
	GtkWidget *picture_preview = user_data->gui_data->gui_data_annotation->picture_preview;
	Dimensions *dimensions_picture_preview_widget = &(user_data->annotation->dimensions_picture_preview_widget);

	dimensions_picture_preview_widget->width = gtk_widget_get_width(picture_preview);
	dimensions_picture_preview_widget->height = gtk_widget_get_height(picture_preview);

	Annotation *annotation = user_data->annotation;
	Dimensions image_preview;

	image_preview.height = dimensions_picture_preview_widget->height;
	image_preview.width = ((float)annotation->dimensions_original_image.width /
						   annotation->dimensions_original_image.height) *
						  dimensions_picture_preview_widget->height;

	annotation->coordinates_scaled_image_top_left.x = (dimensions_picture_preview_widget->width - image_preview.width) / 2;
	annotation->coordinates_scaled_image_top_left.y = 0;

	annotation->coordinates_scaled_image_bottom_right.x = annotation->coordinates_scaled_image_top_left.x + image_preview.width;
	annotation->coordinates_scaled_image_bottom_right.y = image_preview.height;
}

/**
* Fired when there is mouse motion on the widget containing the image preview. This function has two purposes:
* - Changing the cursor to a crosshair as the mouse hovers over the image preview. When outside the image preview, the cursor changes back to the default.
* - Updating the value of the spin boxes, depending on the currently depressed **Point** button.
 */
void on_mouse_motion_image(GtkEventControllerMotion *self, gdouble x, gdouble y, gpointer data)
{

	User_Data *user_data = (User_Data *)data;
	Annotation *annotation = user_data->annotation;
	Gui_Data_Annotation *gui_data_annotation = user_data->gui_data->gui_data_annotation;

	if ((x >= annotation->coordinates_scaled_image_top_left.x) &&
		(x <= annotation->coordinates_scaled_image_bottom_right.x))
	{
		gtk_widget_set_cursor(gui_data_annotation->picture_preview, user_data->annotation->crosshair_cursor);

		if (annotation->is_selecting_vertex_point)
		{

			gtk_spin_button_set_value(GTK_SPIN_BUTTON(gui_data_annotation->spin_vertex_x), (int)x - annotation->coordinates_scaled_image_top_left.x);
			gtk_spin_button_set_value(GTK_SPIN_BUTTON(gui_data_annotation->spin_vertex_y), (int)y);
		}
		else if (annotation->is_selecting_text_bottom_left_point)
		{
			gtk_spin_button_set_value(GTK_SPIN_BUTTON(gui_data_annotation->spin_text_bottom_left_x), (int)x - annotation->coordinates_scaled_image_top_left.x);
			gtk_spin_button_set_value(GTK_SPIN_BUTTON(gui_data_annotation->spin_text_bottom_left_y), (int)y);
		}
	}
	else
	{
		gtk_widget_set_cursor(user_data->gui_data->gui_data_annotation->picture_preview, NULL);
	}
}

/**
* Fired when the mouse is clicked on the preview.
* - If the user is pointing to the text bottom left, then the clicked point is stored as the text bottom left.
* - If the user is pointing to the vertex, then the clicked point is stored as the vertex.
* - In either case, prepare a log message.
 */
void preview_clicked(GtkGestureClick *self, gint n_press, gdouble x, gdouble y, gpointer data)
{
	User_Data *user_data = (User_Data *)data;
	Annotation *annotation = user_data->annotation;
	gchar log_message[256];

	/* If pointing to text bottom left, save the value appearing in the appropriate spin boxes. */
	if ((annotation->is_selecting_vertex_point == FALSE) &&
		(annotation->is_selecting_text_bottom_left_point = TRUE))
	{
	
		/* Turn off tracking the mouse's position inside the image. */
		annotation->is_selecting_text_bottom_left_point = FALSE;

		g_snprintf(log_message, MAX_INPUT, "Text bottom left clicked at x: %d, y: %d", (guint) x, (guint) y);

		/* If pointing to the vertex, save the value appearing in the appropriate spin boxes. */
	}
	else if ((annotation->is_selecting_vertex_point == TRUE) &&
			 (annotation->is_selecting_text_bottom_left_point == FALSE))
	{
		/* Turn off tracking the mouse's position inside the image. */
		annotation->is_selecting_vertex_point = FALSE;

		g_snprintf(log_message, MAX_INPUT, "Vertex clicked at x: %d, y: %d", (guint) x, (guint) y);
	}
	logger(G_LOG_LEVEL_INFO, log_message, user_data);
}

/**
* Fired when the user clicks on the **Point** button for pointing to the vertex. The function sets flags indicating the user wants to set that coordinate. See preview_clicked().
 */
void on_btn_vertex_clicked(GtkWidget *widget, gpointer data)
{
	User_Data *user_data = (User_Data *)data;
	user_data->annotation->is_selecting_vertex_point = TRUE;
	user_data->annotation->is_selecting_text_bottom_left_point = FALSE;
}

/**
 * Fired when the user clicks on the **Point** button for pointing to the balloon's bottom-left corner. The function sets flags indicating the user wants to set that coordinate. See preview_clicked().
 */
void on_btn_text_bottom_clicked(GtkWidget *widget, gpointer data)
{
	User_Data *user_data = (User_Data *)data;
	user_data->annotation->is_selecting_vertex_point = FALSE;
	user_data->annotation->is_selecting_text_bottom_left_point = TRUE;
}

/**
* Fired when the user clicks the **Browse** button to select an input image. The GtkFileChooser is filtered for png, jpg, and gif as defined in build_box_annotation().
 */
void select_input_file(GtkWidget *widget, gpointer data)
{

	User_Data *user_data = (User_Data *)data;

	/* The following object is destroyed in on_open_response(). */

	GtkWidget *file_dialog = gtk_file_chooser_dialog_new(
		"Choose a file",
		GTK_WINDOW(user_data->gui_data->window),
		GTK_FILE_CHOOSER_ACTION_OPEN,
		"Cancel",
		GTK_RESPONSE_CANCEL,
		"Open",
		GTK_RESPONSE_ACCEPT,
		NULL);

	gtk_file_chooser_set_filter (GTK_FILE_CHOOSER(file_dialog), user_data->gui_data->gui_data_annotation->file_filter );

	gtk_window_present(GTK_WINDOW(file_dialog));
	g_signal_connect(file_dialog, "response",
					 G_CALLBACK(on_open_response),
					 data);
}

/**
* Fired when the user clicks the **Export** button. It launches the image processing function process_image().
 */
void launch_processing(GtkWidget *widget, gpointer data)
{

	User_Data *user_data = (User_Data *)data;
	process_image(user_data);
}

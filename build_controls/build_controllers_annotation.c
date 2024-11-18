#include "../headers.h"

/**
 * @file build_controllers_annotation.c
 * @brief Contains functions for adding callbacks to controls.
 */

/**
Fired when user clicks the **Annotation** button, and displays the controls in the annotations tab.
 */
void show_annotation_tab(GtkWidget *widget, gpointer data)
{
	Gui_Data *gui_data = (Gui_Data *)data;

	gtk_css_provider_load_from_path(gui_data->provider, "/home/abba/programming/c_programs/cartoon_balloon_gtk/styles.css");
	gtk_widget_set_visible(gui_data->gui_data_annotation->box_annotation, TRUE);
	gtk_widget_set_visible(gui_data->box_theme, FALSE);
	gtk_widget_set_visible(gui_data->gui_data_configuration->box_configuration, FALSE);
}

/**
This function is fired when the user selects a file in the file open dialog box. The processing includes the following:
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

		g_strlcpy(user_data->annotation->input_image, file_name, MAX_PATH_LENGTH);

		GtkEntryBuffer *file_name_buffer = gtk_entry_get_buffer(GTK_ENTRY(user_data->gui_data->gui_data_annotation->entry_input_image));

		gtk_entry_buffer_set_text(file_name_buffer, file_name, MAX_PATH_LENGTH);

		gtk_picture_set_file(GTK_PICTURE(user_data->gui_data->gui_data_annotation->picture_preview), file);

		gdk_pixbuf_get_file_info(g_file_get_parse_name(file), &(user_data->annotation->dimensions_original_image.width), &(user_data->annotation->dimensions_original_image.height));
		g_object_unref(file);
		g_free(file_name);
	}

	gtk_window_destroy(GTK_WINDOW(dialog));
}

/**
Determines the bounding box of the image in the preview. When the mouse enters the preview widget, we know the following measurements:
* - The dimensions of the preview widget.
* - The dimensions of the original image.
* The image in the preview is a scaled version of the original image. It is scaled by the ratio of the preview widget's height divided by the original image's height. This ratio provides enough information to image preview's bounding box. This bounding box is used in on_mouse_motion_image().
 */
void on_mouse_enter_image(GtkEventControllerMotion *self, gdouble x, gdouble y, gpointer data)
{
	// GdkCursor *cursor_crosshair = gdk_cursor_new_from_name ("crosshair", NULL );
	//  g_object_unref(cursor_crosshair);
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
This function is fired when there is mouse motion on the widget containing the image preview. This function has two purposes:
* - Changing the cursor to a crosshair as the mouse hovers over the image preview. When outside the image preview, the cursor changes back to the default.
* - Update the value of the spin boxes, depending on the depressed **Point** button.
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
This function is fired when the mouse is clicked on the preview.
* -If the user is pointing to the text bottom left, then the clicked point is stored as the text bottom left.
* - If the user is pointing to the vertex, then the clicked point is stored as the vertex.
* - In either case, prepare a log message.
 */
void preview_clicked(GtkGestureClick *self, gint n_press, gdouble x, gdouble y, gpointer data)
{
	User_Data *user_data = (User_Data *)data;
	Annotation *annotation = user_data->annotation;
	Gui_Data_Annotation *gui_data_annotation = user_data->gui_data->gui_data_annotation;
	gchar log_message[256];

	/* If pointing to text bottom left, save the value appearing in the appropriate spin boxes. */
	if ((annotation->is_selecting_vertex_point == FALSE) &&
		(annotation->is_selecting_text_bottom_left_point = TRUE))
	{
		annotation->text_bottom_left.x = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(gui_data_annotation->spin_text_bottom_left_x));
		annotation->text_bottom_left.y = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(gui_data_annotation->spin_text_bottom_left_y));
		/* Turn off tracking the mouse's position inside the image. */
		annotation->is_selecting_text_bottom_left_point = FALSE;

		g_snprintf(log_message, MAX_INPUT, "Text bottom left clicked at x: %ld, y: %ld", annotation->text_bottom_left.x, annotation->text_bottom_left.y);

		/* If pointing to the vertex, save the value appearing in the appropriate spin boxes. */
	}
	else if ((annotation->is_selecting_vertex_point == TRUE) &&
			 (annotation->is_selecting_text_bottom_left_point == FALSE))
	{

		annotation->vertex.x = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(gui_data_annotation->spin_vertex_x));
		annotation->vertex.y = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(gui_data_annotation->spin_vertex_y));

		/* Turn off tracking the mouse's position inside the image. */
		annotation->is_selecting_vertex_point = FALSE;

		g_snprintf(log_message, MAX_INPUT, "Vertex clicked at x: %ld, y: %ld", annotation->vertex.x, annotation->vertex.y);
	}
	logger(G_LOG_LEVEL_INFO, log_message, user_data);
}

/**
 * This function is fired when the user clicks on the **Point** button for pointing to the vertex.
 */
void on_btn_vertex_clicked(GtkWidget *widget, gpointer data)
{
	User_Data *user_data = (User_Data *)data;
	user_data->annotation->is_selecting_vertex_point = TRUE;
	user_data->annotation->is_selecting_text_bottom_left_point = FALSE;
}

/**
 * This function is fired when the user clicks on the **Point** button for pointing to the text bottom left.
 */
void on_btn_text_bottom_clicked(GtkWidget *widget, gpointer data)
{
	User_Data *user_data = (User_Data *)data;
	user_data->annotation->is_selecting_vertex_point = FALSE;
	user_data->annotation->is_selecting_text_bottom_left_point = TRUE;
}

/**
This function is fired when the user clicks the Browse button to select an image.
 */
void select_input_file(GtkWidget *widget, gpointer data)
{

	User_Data *user_data = (User_Data *)data;

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
This function is fired when the user clicks the **Export** button. It launches the image processing function process_image().
 */
void launch_processing(GtkWidget *widget, gpointer data)
{

	User_Data *user_data = (User_Data *)data;
	user_data->annotation->new_width = (gint64)gtk_spin_button_get_value(GTK_SPIN_BUTTON(user_data->gui_data->gui_data_annotation->spin_new_width));
	process_image(user_data);
}
/**
Assigns callbacks to controls in the Annotation tab.
 */
void build_controllers_annotation(User_Data *user_data)
{

	Gui_Data_Annotation *gui_data_annotation = user_data->gui_data->gui_data_annotation;
	GtkWidget *picture_preview = user_data->gui_data->gui_data_annotation->picture_preview;

	/* Add clicked signal to show the annotation tab. */
	g_signal_connect(gui_data_annotation->btn_annotation, "clicked", G_CALLBACK(show_annotation_tab), user_data->gui_data);

	/* Add clicked signal to show the file open dialog. */
	g_signal_connect(gui_data_annotation->btn_file_open, "clicked", G_CALLBACK(select_input_file), user_data);

	/* Add clicked signal for the **Point** buttons. */
	g_signal_connect(gui_data_annotation->btn_point_vertex, "clicked", G_CALLBACK(on_btn_vertex_clicked), user_data);
	g_signal_connect(gui_data_annotation->btn_point_text_bottom, "clicked", G_CALLBACK(on_btn_text_bottom_clicked), user_data);

	/* Add motion controller to picture preview */
	GtkEventController *eventMouseMotion = gtk_event_controller_motion_new();
	gtk_event_controller_set_propagation_phase(eventMouseMotion, GTK_PHASE_CAPTURE);
	g_signal_connect(eventMouseMotion, "enter", G_CALLBACK(on_mouse_enter_image), user_data);
	g_signal_connect(eventMouseMotion, "motion", G_CALLBACK(on_mouse_motion_image), user_data);
	gtk_widget_add_controller(picture_preview, GTK_EVENT_CONTROLLER(eventMouseMotion));

	/* Add gesture controller (mouse clicked) to picture preview */
	GtkGesture *gesture_click_preview = gtk_gesture_click_new();
	g_signal_connect(gesture_click_preview, "pressed", G_CALLBACK(preview_clicked), user_data);
	gtk_widget_add_controller(picture_preview, GTK_EVENT_CONTROLLER(gesture_click_preview));

	/* Add clicked signal to export the annotated image */
	g_signal_connect(gui_data_annotation->btn_export, "clicked", G_CALLBACK(launch_processing), user_data);
}
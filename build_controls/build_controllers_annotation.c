#include "../headers.h"


/**
 * @file build_controls_annotation.c
 * @brief Contains functions for adding callbacks to controls.
 */


/**
Fires when user clicks the **Annotation** button, and displays the controls in the annotations tab.
 */
void show_annotation_tab(GtkWidget *widget, gpointer data) {
	Gui_Data *gui_data = (Gui_Data *)data;

	//gtk_css_provider_load_from_path(gui_data->provider, "/home/abba/programming/c_programs/cartoon_balloon_gtk/styles.css");
	gtk_widget_set_visible(gui_data->gui_data_annotation->box_annotation , TRUE);
	gtk_widget_set_visible(gui_data->box_theme, FALSE);
	gtk_widget_set_visible(gui_data->gui_data_configuration->box_configuration, FALSE);
}

static void on_open_response (GObject *source, GAsyncResult *result, gpointer data)
{

	User_Data *user_data = (User_Data *)data;
	GtkFileDialog *dialog = GTK_FILE_DIALOG (source);
  
	GFile *file = gtk_file_dialog_open_finish (dialog, result, NULL);

  if (file != NULL) {


	gchar  *file_name = g_file_get_parse_name (file);
	g_strlcpy(user_data->annotation->input_image, g_file_get_parse_name (file), MAX_PATH_LENGTH);
	GtkEntryBuffer *file_name_buffer = gtk_entry_get_buffer (GTK_ENTRY (user_data->gui_data->gui_data_annotation->entry_input_image));

	gtk_entry_buffer_set_text (file_name_buffer, g_file_get_parse_name (file), MAX_PATH_LENGTH);

	gtk_picture_set_file (GTK_PICTURE(user_data->gui_data->gui_data_annotation->picture_preview), file);

	GdkPixbufFormat *pbformat = gdk_pixbuf_get_file_info ( g_file_get_parse_name (file), &(user_data->annotation->dimensions_original_image.width), &(user_data->annotation->dimensions_original_image.height));

	g_free(file_name);
  }

}

/**
Determines the dimensions of the widget containing the image preview. See on_mouse_motion_image().
 */
void on_mouse_enter_image(GtkEventControllerMotion* self, gdouble x,  gdouble y, gpointer data) {
	//GdkCursor *cursor_crosshair = gdk_cursor_new_from_name ("crosshair", NULL );
	// g_object_unref(cursor_crosshair);
	User_Data *user_data = (User_Data *)data;
	GtkWidget *picture_preview = user_data->gui_data->gui_data_annotation->picture_preview;
	Dimensions *dimensions_picture_preview_widget = &(user_data->annotation->dimensions_picture_preview_widget);

	dimensions_picture_preview_widget->width = gtk_widget_get_width (picture_preview);
	dimensions_picture_preview_widget->height = gtk_widget_get_height (picture_preview);


	Annotation *annotation = user_data->annotation;
	Dimensions image_preview;

	image_preview.height = dimensions_picture_preview_widget->height;
	image_preview.width = ( 
		(float) annotation->dimensions_original_image.width / 
		annotation->dimensions_original_image.height) * 
		dimensions_picture_preview_widget->height;

	annotation->coordinates_scaled_image_top_left.x =  (dimensions_picture_preview_widget->width  - image_preview.width) / 2;
	annotation->coordinates_scaled_image_top_left.y = 0;

	annotation->coordinates_scaled_image_bottom_right.x = annotation->coordinates_scaled_image_top_left.x + image_preview.width;
	annotation->coordinates_scaled_image_bottom_right.y = image_preview.height;

}

/**
This function is fired when there is mouse motion on the widget containing the image preview. 
 */
void on_mouse_motion_image(GtkEventControllerMotion* self, gdouble x,  gdouble y, gpointer data) {

	User_Data *user_data = (User_Data *)data;
	Annotation *annotation = user_data->annotation;

	if ((x >= annotation->coordinates_scaled_image_top_left.x) &&
	(x <= annotation->coordinates_scaled_image_bottom_right.x)) {
		gtk_widget_set_cursor (user_data->gui_data->gui_data_annotation->picture_preview, user_data->annotation->crosshair_cursor);
	} else {
		gtk_widget_set_cursor (user_data->gui_data->gui_data_annotation->picture_preview, NULL);
	}
}

void select_input_file(GtkWidget *widget, gpointer data) {
	g_print("Got here\n");
	
	GCancellable *cancellable = g_cancellable_new ();
	GtkFileDialog *file_dialog = gtk_file_dialog_new();
	
	gtk_file_dialog_open (file_dialog, NULL, cancellable, on_open_response, data);
	g_object_unref(file_dialog);
	g_object_unref(cancellable);
	g_print("Got there\n");
}

/**
Assigns callbacks to controls in the Annotation tab
 */
void build_controllers_annotation(User_Data *user_data) {

	Gui_Data_Annotation *gui_data_annotation = user_data->gui_data->gui_data_annotation;
	GtkWidget *picture_preview = user_data->gui_data->gui_data_annotation->picture_preview;
	
	g_signal_connect(gui_data_annotation->btn_annotation, "clicked", G_CALLBACK(show_annotation_tab), user_data->gui_data);
	g_signal_connect(user_data->gui_data->gui_data_annotation->btn_file_open, "clicked", G_CALLBACK(select_input_file), user_data);

	/* Add motion controller to picture preview */
	GtkEventController *eventMouseMotion = gtk_event_controller_motion_new ();
	gtk_event_controller_set_propagation_phase(eventMouseMotion, GTK_PHASE_CAPTURE);
	g_signal_connect(eventMouseMotion, "enter", G_CALLBACK( on_mouse_enter_image ), user_data);
	g_signal_connect(eventMouseMotion, "motion", G_CALLBACK( on_mouse_motion_image ), user_data);
	gtk_widget_add_controller (picture_preview, GTK_EVENT_CONTROLLER (eventMouseMotion));
	

}
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


	GError *error;
	const GdkPixbuf *pb = gdk_pixbuf_new_from_file ( g_file_get_parse_name (file),  &error);
	gint width;
	gint height;
	GdkPixbufFormat *pbformat = gdk_pixbuf_get_file_info ( g_file_get_parse_name (file), &width, &height);

	g_free(file_name);
  }

}

void on_mouse_enter_image(GtkEventControllerMotion* self, gdouble x,  gdouble y, gpointer data) {
	//GdkCursor *cursor_crosshair = gdk_cursor_new_from_name ("crosshair", NULL );
	// g_object_unref(cursor_crosshair);
	g_print("ENTERED  IMAGE at %f %f\n", x, y);

/* 
	GdkEventType event_type = gdk_event_get_event_type (
  GdkEvent* event
) */

}

void on_mouse_leave_image(GtkEventControllerMotion* self, gdouble x,  gdouble y, gpointer data) {
	//GdkCursor *cursor_crosshair = gdk_cursor_new_from_name ("crosshair", NULL );
	// g_object_unref(cursor_crosshair);
	g_print("LEFT  IMAGE\n");
/* 
	GdkEventType event_type = gdk_event_get_event_type (
  GdkEvent* event
) */

}

void on_mouse_motion_image(GtkEventControllerMotion* self, gdouble x,  gdouble y, gpointer data) {
	//GdkCursor *cursor_crosshair = gdk_cursor_new_from_name ("crosshair", NULL );
	// g_object_unref(cursor_crosshair);
		g_print("TRAVERSING IMAGE AT %f %f\n", x, y);
/* 
	GdkEventType event_type = gdk_event_get_event_type (
  GdkEvent* event
) */

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
	
	g_signal_connect(gui_data_annotation->btn_annotation, "clicked", G_CALLBACK(show_annotation_tab), user_data->gui_data);
	g_signal_connect(user_data->gui_data->gui_data_annotation->btn_file_open, "clicked", G_CALLBACK(select_input_file), user_data);

	/* Add motion controller to picture preview */
	GtkEventController *eventMouseMotion = gtk_event_controller_motion_new ();
	gtk_event_controller_set_propagation_phase(eventMouseMotion, GTK_PHASE_CAPTURE);
	g_signal_connect(eventMouseMotion, "enter", G_CALLBACK( on_mouse_enter_image ), user_data->gui_data->gui_data_annotation->picture_preview);
	g_signal_connect(eventMouseMotion, "leave", G_CALLBACK( on_mouse_leave_image ), user_data->gui_data->gui_data_annotation->picture_preview);
	g_signal_connect(eventMouseMotion, "motion", G_CALLBACK( on_mouse_motion_image ), user_data->gui_data->gui_data_annotation->picture_preview);
	gtk_widget_add_controller (user_data->gui_data->gui_data_annotation->picture_preview, GTK_EVENT_CONTROLLER (eventMouseMotion));
	

}
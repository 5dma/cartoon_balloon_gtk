#include <headers.h>
#include <gtk/gtk.h>
#include <controls.h>
/**
 * @file build_controllers_annotation.c
 * @brief Contains a function for assigning callbacks to controls in the Annotations tab.
 */


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


	/* Add changed signals to spin buttons. All this is unnecessary after removing the UI fields from the Annotation structure. */
	g_signal_connect(gui_data_annotation->spin_text_bottom_left_x, "value-changed", G_CALLBACK(on_annotation_spinner_changed), user_data);

	g_signal_connect(gui_data_annotation->spin_text_bottom_left_y, "value-changed", G_CALLBACK(on_annotation_spinner_changed), user_data);

	g_signal_connect(gui_data_annotation->spin_vertex_x, "value-changed", G_CALLBACK(on_annotation_spinner_changed), user_data);

	g_signal_connect(gui_data_annotation->spin_vertex_y, "value-changed", G_CALLBACK(on_annotation_spinner_changed), user_data);

	g_signal_connect(gui_data_annotation->spin_new_width, "value-changed", G_CALLBACK(on_annotation_spinner_changed), user_data);



}
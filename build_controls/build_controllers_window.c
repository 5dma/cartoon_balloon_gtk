#include "../headers.h"


/**
 * @file build_controls_window.c
 * @brief Contains functions for adding callbacks to the application window.
 */


void get_click_coordinates(GdkSurface* self, GdkEvent* event, gpointer data) {
	User_Data * user_data = (User_Data *)data; 
	g_print("here\n");

	GtkWidget *picture_preview = user_data->gui_data->gui_data_annotation->picture_preview;
	int preview_height = gtk_widget_get_height (picture_preview);
	int preview_width = gtk_widget_get_width (picture_preview);
	int preview_margin = gtk_widget_get_margin_top (picture_preview);


	graphene_rect_t out_bounds;

	GtkNative *native = gtk_widget_get_native (user_data->gui_data->gui_data_annotation->picture_preview);

	gboolean trash =  gtk_widget_compute_bounds ( user_data->gui_data->gui_data_annotation->picture_preview, user_data->gui_data->window, &out_bounds);

	trash =  gtk_widget_compute_bounds ( user_data->gui_data->gui_data_annotation->picture_preview, user_data->gui_data->gui_data_annotation->box_annotation, &out_bounds);

	trash =  gtk_widget_compute_bounds ( user_data->gui_data->gui_data_annotation->picture_preview, GTK_WIDGET (native), &out_bounds);

	GtkWidget *parent = gtk_widget_get_parent (user_data->gui_data->gui_data_annotation->picture_preview);

trash =  gtk_widget_compute_bounds ( user_data->gui_data->gui_data_annotation->picture_preview, parent, &out_bounds);

GtkWidget *image = gtk_image_new_from_file ("/home/abba/Ronen_Letters/graphic_quotes/knesset.png");

	trash =  gtk_widget_compute_bounds (image, user_data->gui_data->window, &out_bounds);

	trash =  gtk_widget_compute_bounds (image, user_data->gui_data->gui_data_annotation->picture_preview, &out_bounds);

//trash =  gtk_widget_compute_bounds ( user_data->gui_data->gui_data_annotation->picture_preview, user_data->gui_data->gui_data_annotation->picture_preview, &out_bounds);


	g_print("height: %d", preview_height);
	

}

/**
Assigns callbacks to controls in the application window
 */
void build_controllers_window(User_Data *user_data) {

	GtkGesture *gesture = gtk_gesture_click_new();
	gtk_gesture_single_set_button(GTK_GESTURE_SINGLE(gesture), 0);
	gtk_widget_add_controller(user_data->gui_data->window, (GTK_EVENT_CONTROLLER(gesture)));
	g_signal_connect (gesture, "pressed", G_CALLBACK (get_click_coordinates), user_data);

}

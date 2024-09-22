#include <stdio.h>
#include <glib.h>
#include <glib-object.h>
#include "headers.h"
#include <gtk/gtk.h>
#include "wand/MagickWand.h"
/**
 * @file main.c
 * @brief Starts the application.
 */

/*! \mainpage Speech Balloon
 *
 * This GTK application is a small graphics editor for adding speech balloons to images. 
 *
 * \section motivation Motivation
 * Full-feature graphics editors, such as GIMP or LibreOffice Draw, have the functionality for adding speech balloons. For someone doing a lot of this graphical work, there are many steps involved and the repetitive effort can become a burden. This small application reduces the number of steps and corresponding time to add speech balloons.
 * 
 * \section architecture Architecture
 * This application runs on GTK and incorporates commands from the ImageMagick C API.
 * 
 * \section documentation Documentation
 * To generate this code documentation, run `doxygen Doxyfile`. The output is in the `doc/html/` directory of this source code.
 *
*/

/**
 * Starts the program and makes function calls representing a drawing process with the following steps:
 * -# Read in the image
 * -# Scale the image to the maximum width specified by the user.
 * -# Determine properties of the text, such as its final bounding box.
 * -# Draw a balloon sized to contain the text.
 * -# Draw the text.
 * -# Draw a path from user-specified point to the speech balloon.
 * -# Write the image.
 */
int main(int argc, char *argv[]) {

	GtkApplication *app;
	int status;

	Settings * settings = read_json();
	if (settings == NULL) {
		return 0;
	}

	settings->log_file_pointer = get_log_file_pointer(settings);

	Annotation * annotation = read_annotation(settings);
	if (annotation == NULL) {
		return 0;
	}

	GHashTable * theme_hash = read_themes(settings);
	

	Gui_Data * gui_data = (Gui_Data *) g_malloc(sizeof(Gui_Data));

	User_Data * user_data = (User_Data *) g_malloc(sizeof(User_Data));
	user_data->gui_data = gui_data;
	user_data->annotation = annotation;
	user_data->settings = settings;

	app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect (app, "activate", G_CALLBACK (activate), user_data);
	status = g_application_run (G_APPLICATION (app), argc, argv);
 
	/* Decrease reference count because assigning it in on_app_activate */
	g_object_unref(app);



	apply_theme(theme_hash, annotation, &settings);

	process_image(settings, annotation);

	
	g_hash_table_destroy(theme_hash);
	fclose(settings->log_file_pointer);
	g_free(user_data);
	g_free(gui_data);
	g_free(settings);
	g_free(annotation);

	
	return status;
}

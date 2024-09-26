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

	User_Data * user_data = (User_Data *) g_malloc(sizeof(User_Data));

	read_configuration(user_data);
	read_annotation(user_data);
	read_themes(user_data);

	logger(G_LOG_LEVEL_INFO, "Started", user_data);
	log_configuration_values(user_data);


	app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect (app, "activate", G_CALLBACK (activate), user_data);
	status = g_application_run (G_APPLICATION (app), argc, argv);
 
	/* Decrease reference count because assigning it in on_app_activate */
	g_object_unref(app);

	//apply_theme(theme_hash, annotation, &settings);

	process_image(user_data->configuration, user_data->theme_hash, user_data->annotation);

		/* Clean up */
	
	g_object_unref(user_data->parser);
	g_object_unref(user_data->reader);

	g_hash_table_destroy(user_data->theme_hash);
	fclose(user_data->configuration->log_file_pointer);
	g_free(user_data->gui_data);
	g_free(user_data->configuration);
	g_free(user_data->annotation);
	g_free(user_data);
	
	
	return status;
}

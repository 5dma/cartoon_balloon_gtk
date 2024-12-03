#include <stdio.h>
#include <glib.h>
#include <glib-object.h>
#include <headers.h>
#include <gtk/gtk.h>
#include <wand/MagickWand.h>
/**
 * @file main.c
 * @brief Starts the application.
 */

/*! \mainpage Speech Balloon
 *
 * This GTK application is a small graphics editor for adding speech balloons to images. 
 *
 * \section motivation Motivation
 * Full-feature graphics editors, such as GIMP or LibreOffice Draw, have the functionality for adding speech balloons. There are many steps involved with these graphics editors, so for someone doing a lot of these annotations the repetitive effort can become a burden. This small application reduces the number of steps and corresponding time to add speech balloons.
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
 * -# Allocate memory for the structures.
 * -# Run the application.
 * -# Free allocated memory.
 */
int main(int argc, char *argv[]) {

	GtkApplication *app;
	int status;

	/* Allocate memory for the structures (and sub-structures) with root structure User_Data.*/
	User_Data *user_data = allocate_structures();

	app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect (app, "activate", G_CALLBACK (activate), user_data);
	status = g_application_run (G_APPLICATION (app), argc, argv);
 
	/* Decrease reference count because assigning it in activate() */
	g_object_unref(app);

	/* Free allocated memory */
	cleanup(user_data, TRUE);

	return status;
}

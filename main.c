#include <stdio.h>
#include <glib.h>
#include <glib-object.h>

#include "MagickWand/MagickWand.h"
#include "headers.h"
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

	Settings * settings = read_json();
	if (settings == NULL) {
		return 0;
	}

	Annotation * annotation = read_annotation(settings);
	if (annotation == NULL) {
		return 0;
	}

	GHashTable * theme_hash = read_themes(settings);

	apply_theme(theme_hash, annotation, &settings);

	MagickWandGenesis();

	MagickWand *m_wand = NewMagickWand();

	MagickBooleanType result = MagickReadImage(m_wand, annotation->original_image_path);

	if (result == MagickFalse) {
		g_print("Could not read the image %s. Exiting\n", annotation->original_image_path);
		return -1;
	}


	/* Scale the image to a max of 520 pixels wide. */
	scale_image(m_wand, settings, annotation);

	/* Determine height of the annotation, and compute other measurements. */
	Text_Analysis *text_analysis = analyze_text(m_wand, settings, annotation);

	/* Extend the image vertically to accommodate the balloon. */
	resize_image(m_wand, settings, annotation, text_analysis);

	/* Add the balloon. */
	add_balloon(m_wand, settings, annotation, text_analysis);

	/* Add the text inside the balloon. */
	add_text(m_wand, settings, annotation, text_analysis);

	/* Add the path to the balloon. */
	add_path(m_wand, annotation, settings, text_analysis);

	/* Write the new image */
	MagickWriteImage(m_wand, settings->new_image_path);

	g_print("The new image is at %s\n", settings->new_image_path);

	/* Clean up */
	DestroyMagickWand(m_wand);
	MagickWandTerminus();
	
	g_hash_table_destroy(theme_hash);
	g_free(text_analysis);
	g_free(settings);
	g_free(annotation);
	
	return 0;
}
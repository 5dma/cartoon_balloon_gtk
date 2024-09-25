#include <stdio.h>
#include <glib.h>
#include <glib-object.h>

#include "wand/MagickWand.h"
#include "headers.h"
/**
 * @file process_image.c
 * @brief Processes the image based on the current settings for annotation and configuration.
 */


/**
 * Makes function calls representing a drawing process with the following steps:
 * -# Read in the image
 * -# Scale the image to the maximum width specified by the user.
 * -# Determine properties of the text, such as its final bounding box.
 * -# Draw a balloon sized to contain the text.
 * -# Draw the text.
 * -# Draw a path from user-specified point to the speech balloon.
 * -# Write the image.
 */
void process_image(Configuration *configuration, GHashTable *theme_hash, Annotation *annotation) {


	MagickWandGenesis();

	MagickWand *m_wand = NewMagickWand();

	MagickBooleanType result = MagickReadImage(m_wand, annotation->input_image);

	if (result == MagickFalse) {
		g_print("Could not read the image %s. Exiting\n", annotation->input_image);
		return;
	}

	Theme * theme = (Theme *) g_hash_table_lookup (theme_hash, "boy");


	/* Scale the image to a max of 520 pixels wide. */
	scale_image(m_wand, annotation);

	/* Determine height of the annotation, and compute other measurements. */
	Text_Analysis *text_analysis = analyze_text(m_wand, configuration, theme, annotation);

	/* Extend the image vertically to accommodate the balloon. */
	resize_image(m_wand,annotation, configuration, theme, text_analysis);

	/* Add the balloon. */
	add_balloon(m_wand, configuration, theme, annotation, text_analysis);

	/* Add the text inside the balloon. */
	add_text(m_wand, configuration,theme, annotation,text_analysis);

	/* Add the path to the balloon. */
	add_path(m_wand, annotation, configuration, theme, text_analysis);

	/* Write the new image */
	MagickWriteImage(m_wand, configuration->new_image_path);

	g_print("The new image is at %s\n", configuration->new_image_path);

	/* Clean up */
	DestroyMagickWand(m_wand);
	MagickWandTerminus();
	g_free(text_analysis);
}
#include <stdio.h>

#include "MagickWand/MagickWand.h"
#include "glib.h"
#include "headers.h"


int main(int argc, char *argv[]) {
	Settings * settings = read_json();
	if (settings == NULL) {
		return 0;
	}


	Annotation * annotation = read_annotation(settings);
	if (annotation == NULL) {
		return 0;
	}

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
	resize_image(m_wand, settings, text_analysis);

	/* Add the balloon. */
	add_balloon(m_wand, settings, annotation, text_analysis);

	/* Add the text inside the balloon. */
	add_text(m_wand, settings, annotation, text_analysis);

	/* Add the path to the balloon. */
	add_path(m_wand, annotation, settings, text_analysis);

	/* Write the new image */
	MagickWriteImage(m_wand, settings->new_image_path);

	/* Clean up */
	DestroyMagickWand(m_wand);
	MagickWandTerminus();
	
	g_free(text_analysis);
	g_free(settings);
	g_free(annotation);
	
	g_print("The new image is at %s\n", settings->new_image_path);
	
	return 0;
}
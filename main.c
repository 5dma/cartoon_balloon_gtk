#include <stdio.h>

#include "MagickWand/MagickWand.h"
#include "glib.h"
#include "headers.h"

/* https://imagemagick.org/api/magick-image.php */
/* https://imagemagick.org/api/drawing-wand.php */
/* https://imagemagick.org/api/pixel-wand.php */
int main(int argc, char *argv[]) {
	Settings *settings;
	settings = read_json();
	if (settings == NULL) {
		return 0;
	}

	Annotation *annotation;
	annotation = read_annotation(settings);
	if (annotation == NULL) {
		return 0;
	}

	MagickWand *m_wand = NULL;

	MagickWandGenesis();
	m_wand = NewMagickWand();

	MagickBooleanType result = MagickReadImage(m_wand, annotation->original_image_path);

	if (result == MagickFalse) {
		g_print("Could not read the image %s. Exiting\n", annotation->original_image_path);
		return -1;
	}

	g_print("The annotation text is %s\n", annotation->text_string);

	/* Resize the image */
	resize(m_wand, settings, annotation);

	add_balloon(m_wand, settings, annotation);

	add_text(m_wand, settings, annotation);

	/* Write the new image */
	MagickWriteImage(m_wand, settings->new_image_path);

	/* Clean up */

	if (m_wand)
		m_wand = DestroyMagickWand(m_wand);

	MagickWandTerminus();
	g_print("The new image is at %s\n", settings->new_image_path);
	g_free(settings);
	g_free(annotation);

	return 0;
}
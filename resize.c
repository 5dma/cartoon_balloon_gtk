#include <stdlib.h>
#include "headers.h"
#include <glib.h>
#include <wand/MagickWand.h>

/**
 * @file resize.c
 * @brief Scales and resizes the image.
 */

/**
Scales the original image to no wider than the user-specified width found in `annotation->new_width`.
 */
void scale_image(MagickWand *m_wand, Annotation *annotation)
{
	gint64 old_width = MagickGetImageWidth(m_wand);
	gint64 old_height = MagickGetImageHeight(m_wand);

	gint64 new_height = (annotation->new_width * old_height) / old_width;
 
	/* Previously used the LanczosFilter and similar, I got only black images. Need to find the best filter. See the available filters at /usr/include/ImageMagick-6/Magick++/Include.h */
	MagickResizeImage(m_wand, annotation->new_width, new_height, BoxFilter, 0);

	annotation->resize_proportion_x = (float) annotation->new_width / old_width;
	annotation->resize_proportion_y = (float) new_height / old_height;
}


/**
  Resizes the image vertically so that it can accommodate any overflow from the text, balloon, padding, and top margin.
 */
void resize_image(MagickWand *m_wand, Annotation *annotation, Configuration *configuration, Theme *theme, Text_Analysis *text_analysis) {

	text_analysis->overflow = \
		text_analysis->bottom_offset - \
		text_analysis->text_height - \
		configuration->padding - \
		theme->stroke_width -\
		configuration->top_margin;

	unsigned long current_image_height = MagickGetImageHeight(m_wand);

	if (text_analysis->overflow < 0) {

			MagickExtentImage(m_wand, \
			annotation->new_width, \
			current_image_height - text_analysis->overflow, \
			0, \
			text_analysis->overflow);
		} else {
			text_analysis->overflow = 0;
		}

	
}

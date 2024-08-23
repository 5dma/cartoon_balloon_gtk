#include <stdlib.h>
#include "headers.h"
#include "glib.h"
#include "MagickWand/MagickWand.h"

/* Scales the original image to no wider than the user-specified width (520 px for twitter, 740 for WordPress.)*/
void scale_image(MagickWand *m_wand, Settings *settings, Annotation *annotation)
{

	gint64 old_width, old_height;

	old_width = MagickGetImageWidth(m_wand);
	old_height = MagickGetImageHeight(m_wand);

	gint64 new_height;
	new_height = (settings->new_width * old_height) / old_width;

	MagickResizeImage(m_wand, settings->new_width, new_height, LanczosFilter);

	annotation->resize_proportion_x = (float) settings->new_width / old_width;

	annotation->resize_proportion_y = (float) new_height / old_height;
}

/* Extends the original image upward to accommodate the text and balloon as necessary. */

void resize_image(MagickWand *m_wand, Settings *settings, Text_Analysis * text_analysis) {

	text_analysis->overflow = \
		text_analysis->bottom_offset - \
		text_analysis->text_height - \
		settings->padding - \
		settings->stroke_width -\
		settings->top_margin;

	unsigned long current_image_height = MagickGetImageHeight(m_wand);

	if (text_analysis->overflow < 0) {

			MagickExtentImage(m_wand, \
			settings->new_width, \
			current_image_height - text_analysis->overflow, \
			0, \
			text_analysis->overflow);
		}

	
}
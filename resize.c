#include <stdlib.h>
#include "headers.h"
#include "glib.h"
#include <wand/magick_wand.h>

void resize (MagickWand *m_wand, Settings * settings, Annotation * annotation ) {

	gint64 old_width, old_height;
	
	old_width = MagickGetImageWidth(m_wand);
	old_height = MagickGetImageHeight(m_wand);

	gint64 new_height;
	new_height = (settings->new_width * old_height ) / old_width;

	// Resize the image using the Lanczos filter
	// The blur factor is a "double", where > 1 is blurry, < 1 is sharp

	MagickResizeImage(m_wand, settings->new_width ,new_height,LanczosFilter,1);

	annotation -> resize_proportion_x = settings->new_width / old_width;

	annotation -> resize_proportion_y = new_height / old_height;
	
}



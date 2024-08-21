#include <stdlib.h>
#include "headers.h"
#include "glib.h"
#include "MagickWand/MagickWand.h"

void resize(MagickWand *m_wand, Settings *settings, Annotation *annotation)
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

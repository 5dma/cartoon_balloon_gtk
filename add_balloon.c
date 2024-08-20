#include <stdlib.h>
#include "headers.h"
#include "MagickWand/MagickWand.h"



void add_balloon(MagickWand *m_wand, DrawingWand *d_wand, Settings *settings, Annotation *annotation)
{

	gint64 left = annotation->text_bottom_left.x * annotation->resize_proportion_x - settings->padding;
	gint64 top = annotation->text_bottom_left.y * annotation->resize_proportion_y - 20; //- annotation->

	/*gint64 excess_spacing = text_height - (text_analysis->number_text_lines * settings->font_size );
	gint64 partial_excess_spacing = excess_spacing * 0.75;
	gint64 baseline = \
		(annotation->text_bottom_left.y * annotation->resize_proportion_y) - \
		(text_analysis->number_text_lines * settings->font_size) - \
		partial_excess_spacing;

	

*/

	DrawRectangle(d_wand, left, top, 400, 400);

/*	gint64 left_offset;
	left_offset = annotation->text_bottom_left.x * annotation->resize_proportion_x;

	MagickBooleanType result = MagickAnnotateImage(m_wand, d_wand, left_offset, baseline + offset, 0, text_analysis->split_string);*/
	return;

}

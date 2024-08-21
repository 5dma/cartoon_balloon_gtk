#include <stdlib.h>
#include "headers.h"
#include "MagickWand/MagickWand.h"



void add_balloon(MagickWand *m_wand, Settings *settings, Annotation *annotation, Text_Analysis *text_analysis)
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

	DrawingWand *d_wand = NewDrawingWand();
	PixelWand *p_wand = NewPixelWand();
	PixelSetColor(p_wand, settings->balloon_stroke_color);

	PixelSetAlpha(p_wand, 1.0);

	DrawSetStrokeColor(d_wand, p_wand);
	DrawSetStrokeWidth(d_wand, settings->stroke_width);
	DrawSetStrokeOpacity(d_wand, 1.0);
	DrawSetFillColor(d_wand, p_wand);

	gint64 top_left_x = text_analysis->left_offset;
	gint64 top_left_y = annotation->text_bottom_left.y - text_analysis->text_height;
	gint64 bottom_right_x = top_left_x + text_analysis->text_width;
	gint64 bottom_right_y = top_left_y + text_analysis->text_height;
	DrawRectangle(d_wand, top_left_x, top_left_y, bottom_right_x, bottom_right_y);
	MagickDrawImage(m_wand, d_wand);

	DestroyPixelWand(p_wand);
	DestroyDrawingWand(d_wand);
	return;

}

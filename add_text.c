#include <stdlib.h>
#include "headers.h"
#include "glib.h"
#include <wand/magick_wand.h>
#include <wand/drawing-wand.h>

Text_Analysis *drawing_with_split_text(MagickWand *m_wand, DrawInfo *draw_info, Settings *settings, gint64 left_offset, char *text_string)
{

	Text_Analysis *text_analysis;
	text_analysis = (Text_Analysis *)g_malloc(sizeof(Text_Analysis));
	gint64 max_width;
	max_width = settings->new_width - left_offset - settings->padding - settings->stroke_width;
	gboolean is_multiline = FALSE;

	PixelWand *p_wand = NewPixelWand();
	PixelSetColor(p_wand, "#0000ff");
	PixelSetAlpha(p_wand, 1.0);

	DrawingWand *my_wand = NewDrawingWand();
	MagickBooleanType test = DrawSetFont(my_wand, settings->font);
	DrawSetFillColor(my_wand, p_wand);
	DrawSetFontSize(my_wand, settings->font_size);
	DrawSetGravity(my_wand, NorthWestGravity);

	TypeMetric *metrics;
	Image *my_image;

	my_image = GetImageFromMagickWand(m_wand);
	double *text_width;
	text_width = MagickQueryFontMetrics(m_wand, my_wand, text_string);

	text_analysis->text_wand = my_wand;
	strlcpy(text_analysis->split_string, text_string, 256);
	text_analysis->metrics = metrics;
	text_analysis->number_text_lines = 1;

	return text_analysis;
}

MagickBooleanType add_text(MagickWand *m_wand, DrawingWand *d_wand, Settings *settings, Annotation *annotation)
{

	/* Get analysis of text, retain width and height, free memory for returned metrics.*/
	double *metrics = MagickQueryFontMetrics(m_wand, d_wand, annotation->text_string);
	double text_width = metrics[4];
	double text_height = metrics[5];

	RelinquishMagickMemory(metrics);

	gint64 left_offset;
	left_offset = annotation->text_bottom_left.x * annotation->resize_proportion_x;

	MagickBooleanType result = MagickAnnotateImage(m_wand, d_wand, 50, 120, 0, annotation->text_string);

	return result;
}

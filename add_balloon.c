#include <stdlib.h>

#include "MagickWand/MagickWand.h"
#include "headers.h"

void add_balloon(MagickWand *m_wand, Settings *settings, Annotation *annotation, Text_Analysis *text_analysis) {
	DrawingWand *d_wand = NewDrawingWand();
	PixelWand *p_wand = NewPixelWand();
	PixelSetColor(p_wand, settings->balloon_stroke_color);

	PixelSetAlpha(p_wand, 1.0);

	DrawSetStrokeColor(d_wand, p_wand);
	DrawSetStrokeWidth(d_wand, settings->stroke_width);
	DrawSetStrokeOpacity(d_wand, 1.0);
	DrawSetFillColor(d_wand, p_wand);

	gint64 top_left_x =
		text_analysis->left_offset -
		settings->padding -
		settings->stroke_width;

	gint64 top_left_y =
		annotation->text_bottom_left.y * annotation->resize_proportion_y -
		text_analysis->text_height -
		settings->padding -
		settings->stroke_width -
		text_analysis->overflow;

	gint64 bottom_right_x = top_left_x +
							text_analysis->text_width +
							settings->padding * 2 +
							settings->stroke_width * 2;

	gint64 bottom_right_y =
		top_left_y +
		text_analysis->text_height +
		settings->padding * 2 +
		settings->stroke_width * 2;

	DrawRectangle(d_wand, top_left_x, top_left_y, bottom_right_x, bottom_right_y);
	MagickDrawImage(m_wand, d_wand);

	DestroyPixelWand(p_wand);
	DestroyDrawingWand(d_wand);
	return;
}

void add_path(MagickWand *m_wand, Settings *settings) {
	DrawingWand *d_wand = NewDrawingWand();
	PixelWand *p_wand = NewPixelWand();
	PixelSetColor(p_wand, settings->balloon_stroke_color);

	PixelSetAlpha(p_wand, 1.0);

	DrawSetStrokeColor(d_wand, p_wand);
	DrawSetStrokeWidth(d_wand, settings->stroke_width);
	DrawSetStrokeOpacity(d_wand, 1.0);
	DrawSetFillOpacity(d_wand, 0.0);
	//DrawSetFillColor(d_wand, p_wand);

	PointInfo p1;
	PointInfo p2;
	PointInfo p3;
	p1.x = 100;
	p1.y = 100;
	p2.x = 300;
	p2.y = 300;
	p3.x = 500;
	p3.y = 100;

	PointInfo  barf[3] = {p1, p2, p3};

	DrawPolyline(d_wand, 3, barf);


	MagickDrawImage(m_wand, d_wand);

	DestroyPixelWand(p_wand);
	DestroyDrawingWand(d_wand);
}
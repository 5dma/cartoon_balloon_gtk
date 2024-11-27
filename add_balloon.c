#include <stdlib.h>
#include <wand/MagickWand.h>
#include <headers.h>

/**
 * @file add_balloon.c
 * @brief Adds the speech balloon and the path to the balloon.
 */

/**
 * Draws a balloon large enough to accommodate the text, and in an appropriate location.
 *  
 * ImageMagick's <a href="https://imagemagick.org/api/drawing-wand.php#DrawRectangle">DrawRectangle</a> command requires providing four points representing the top-left and bottom-right corners. See the specification for detail about how those points are computed.
 */
void add_balloon(MagickWand *m_wand, Configuration *configuration, Theme *theme, Annotation *annotation, Text_Analysis *text_analysis) {

	DrawingWand *d_wand = NewDrawingWand();
	PixelWand *p_wand = NewPixelWand();
	
	/* Set up pixel and draw wands for the balloon's fill. */
	PixelSetColor(p_wand, theme->balloon_fill_color);
	PixelSetAlpha(p_wand, 1.0);
	DrawSetFillColor(d_wand, p_wand);
	

	/* Set up pixel and draw wands for the balloon's stroke. */
	PixelSetColor(p_wand, theme->balloon_stroke_color);
	DrawSetStrokeColor(d_wand,p_wand);
	DrawSetStrokeWidth(d_wand, theme->stroke_width);
	DrawSetStrokeOpacity(d_wand, 1.0);
	
	/* Compute the four coordinates of the balloon. */
	gint64 top_left_x =
		text_analysis->left_offset -
		configuration->padding -
		theme->stroke_width;

	gint64 top_left_y =
		annotation->text_bottom_left.y * 
		annotation->preview_scale * 
		annotation->resize_proportion_y -
		text_analysis->text_height -
		configuration->padding -
		theme->stroke_width -
		text_analysis->overflow;

	gint64 bottom_right_x = top_left_x +
							text_analysis->text_width +
							configuration->padding * 2 +
							theme->stroke_width * 2;

	gint64 bottom_right_y =
		top_left_y +
		text_analysis->text_height +
		configuration->padding * 2 +
		theme->stroke_width * 2;

	/* Save the midpoint and bottom edge for drawing the path. */
	text_analysis->balloon_midpoint =  (bottom_right_x - top_left_x)/2 + top_left_x;
	text_analysis->balloon_bottom = bottom_right_y;

	/* Draw the balloon. */
	DrawRectangle(d_wand, top_left_x, top_left_y, bottom_right_x, bottom_right_y);
	MagickDrawImage(m_wand, d_wand);

	/* Clean up */
	DestroyPixelWand(p_wand);
	DestroyDrawingWand(d_wand);
	return;
}

/**
 * Adds the path to the image. The path is polyline of three points. The vertex is supplied by the user, and the other two points jut into the balloon. See the specification for detail about how those points are computed.
 */
void add_path(MagickWand *m_wand, Annotation *annotation, Configuration *configuration, Theme *theme, Text_Analysis *text_analysis) {

	DrawingWand *d_wand = NewDrawingWand();
	PixelWand *p_wand = NewPixelWand();

	/* Set up pixel and draw wands with colors for drawing the path's stroke. */
	PixelSetColor(p_wand, theme->balloon_stroke_color);
	PixelSetAlpha(p_wand, 1.0);
	DrawSetStrokeColor(d_wand, p_wand);
	DrawSetStrokeWidth(d_wand, theme->stroke_width);
	DrawSetStrokeOpacity(d_wand, 1.0);

	/* Set up pixel and draw wands with colors for drawing the path's fill. */
	PixelSetColor(p_wand, theme->balloon_fill_color);
	DrawSetFillOpacity(d_wand, 1.0);
	DrawSetFillColor(d_wand, p_wand);

	PointInfo p1;
	PointInfo vertex;
	PointInfo p3;
	
	/* Compute the positions of the path. */
	p1.x = text_analysis->balloon_midpoint - configuration->space;
	p1.y = text_analysis->balloon_bottom - configuration->elevation;
	vertex.x =  annotation->vertex.x * annotation->resize_proportion_x * annotation->preview_scale;
	vertex.y = annotation->vertex.y  * annotation->resize_proportion_y * annotation->preview_scale - text_analysis->overflow;
	p3.x = text_analysis->balloon_midpoint + configuration->space;
	p3.y = text_analysis->balloon_bottom - configuration->elevation;

	PointInfo  path_points[3] = {p1, vertex, p3};

	/* Draw the path. */
	DrawPolyline(d_wand, 3, path_points);
	MagickDrawImage(m_wand, d_wand);

	/* Clean up. */
	DestroyPixelWand(p_wand);
	DestroyDrawingWand(d_wand);
}
#include <stdlib.h>

#include "MagickWand/MagickWand.h"
#include "glib.h"
#include "headers.h"

/* Adds text to the image. */
void add_text(MagickWand *m_wand, Settings *settings, Annotation *annotation, Text_Analysis *text_analysis) {
	
	DrawingWand *d_wand = NewDrawingWand();
	PixelWand *p_wand = NewPixelWand();

	/* Set up pixel and drawing wands for adding the text. */
	PixelSetColor(p_wand, settings->balloon_fill_color);
	PixelSetColor(p_wand, settings->text_color);
	PixelSetAlpha(p_wand, 1.0);
	DrawSetFillColor(d_wand, p_wand);
	DrawSetGravity(d_wand, NorthWestGravity);
	DrawSetFontSize(d_wand, settings->font_size);


	//DrawSetStrokeColor(d_wand, p_wand);
	//DrawSetStrokeOpacity(d_wand, 1.0);

	/* Add the text to the image. */
	MagickAnnotateImage(m_wand, d_wand, \
		text_analysis->left_offset, \
		text_analysis->bottom_offset  - text_analysis->text_height - text_analysis->overflow, \
		0, \
		text_analysis->split_string);

	MagickDrawImage(m_wand, d_wand);

	/* Clean up. */
	DestroyPixelWand(p_wand);
	DestroyDrawingWand(d_wand);
	return;
} 

/* Process and analyze the text. */
Text_Analysis *analyze_text(MagickWand *m_wand, Settings *settings, Annotation *annotation) {
	
	Text_Analysis *text_analysis;
	text_analysis = (Text_Analysis *)g_malloc(sizeof(Text_Analysis));
	
	/* Compute locations where text will be placed. */
	text_analysis->left_offset = annotation->text_bottom_left.x * annotation->resize_proportion_x;
	text_analysis->bottom_offset = annotation->text_bottom_left.y * annotation->resize_proportion_y;
	text_analysis->text_width = 0;
	text_analysis->text_height = 0;
	text_analysis->overflow = 0;
	text_analysis->balloon_midpoint = 0;
	text_analysis->balloon_bottom = 0;


	/* Determine the maximal width of the text. */
	gint64 max_text_width = settings->new_width - \
		text_analysis->left_offset - \
		settings->padding * 2 - \
		settings->stroke_width * 2;

	/* Set up wand for drawing text. */
	DrawingWand *d_wand = NewDrawingWand();
	DrawSetFont(d_wand, settings->font);
	DrawSetFontSize(d_wand, settings->font_size);


	gdouble *text_metrics;
	gchar *rightmost_space;

	/* Parse the annotation, placing newlines in places where the string exceeds max_text_width. */
	gchar *token = strtok(annotation->text_string, " ");
	g_strlcpy(text_analysis->split_string, token, settings->max_annotation_length);
	while ((token = strtok(NULL, " ")) != NULL) {
		g_strlcat(text_analysis->split_string, " ", settings->max_annotation_length);
		g_strlcat(text_analysis->split_string, token, settings->max_annotation_length);
		text_metrics = MagickQueryMultilineFontMetrics(m_wand, d_wand, text_analysis->split_string);
		if (text_metrics[4] > max_text_width) {
			rightmost_space = g_strrstr(text_analysis->split_string, " ");
			*rightmost_space = '\n';
		}
		RelinquishMagickMemory(text_metrics);
	}

	/* Save the text's height and width. These will be used to determine the balloon's height and width. */
	text_metrics = MagickQueryMultilineFontMetrics(m_wand, d_wand, text_analysis->split_string);
	text_analysis->text_height = text_metrics[5]; //This may change to + text_metrics[2]
	text_analysis->text_width = text_metrics[4] - text_metrics[6]; //This may change to + text_metrics[2]
	
	/* Clean up */
	RelinquishMagickMemory(text_metrics);
	DestroyDrawingWand(d_wand);
	return text_analysis;
}

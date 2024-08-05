#include <stdlib.h>
#include "headers.h"
#include "glib.h"
#include <wand/magick_wand.h>
#include <wand/drawing-wand.h>

Text_Analysis * drawing_with_split_text(MagickWand *m_wand, Settings *settings,  Annotation *annotation)
{

	gint64 left_offset;
	left_offset = annotation->text_bottom_left.x * annotation->resize_proportion_x;

	gint64 max_width;
	max_width = settings->new_width - left_offset - settings->padding - settings->stroke_width;
	gboolean is_multiline = TRUE;

	PixelWand *p_wand = NewPixelWand();
	PixelSetColor(p_wand, "#0000ff");
	PixelSetAlpha(p_wand, 1.0);

	DrawingWand *my_wand = NewDrawingWand();
	MagickBooleanType test = DrawSetFont(my_wand, settings->font);
	DrawSetFillColor(my_wand, p_wand);
	DrawSetFontSize(my_wand, settings->font_size);
	DrawSetGravity(my_wand, NorthWestGravity);

	char * current_text;

	gsize cat_result;
	double *text_metrics;
	double text_width;
	gchar * rightmost_space;
	
	char * token = strtok(annotation->text_string , " ");
	cat_result = strlcpy(current_text, token, settings->max_annotation_length);
	gint64 number_text_lines = 1;
	while( (token = strtok(NULL, " ")) != NULL ) {
		printf( "%s\n", token );
		cat_result = strlcat(current_text, " ", settings->max_annotation_length);
		cat_result = strlcat(current_text, token, settings->max_annotation_length);
		text_metrics = MagickQueryMultilineFontMetrics(m_wand, my_wand, current_text);
		text_width = text_metrics[4];
		RelinquishMagickMemory(text_metrics);
		if (text_width > max_width) {
			rightmost_space = g_strrstr (current_text, " ");
			*rightmost_space = '\n';
			number_text_lines++;
		}
   }
	TypeMetric *type_metrics;
	type_metrics = (TypeMetric *)g_malloc(sizeof(TypeMetric));

   g_print( "After loop: %s\n", current_text );
	text_metrics = MagickQueryMultilineFontMetrics(m_wand, my_wand, current_text);
	   g_print( "After MagickQueryMultilineFontMetrics\n");
	Text_Analysis * text_analysis;
	text_analysis = (Text_Analysis *) g_malloc(sizeof(Text_Analysis));
	g_print("After malloc\n");
	text_analysis->text_wand = my_wand;
	strlcpy(text_analysis->split_string, current_text, settings->max_annotation_length);
	text_analysis->number_text_lines = number_text_lines;
	text_analysis->y = 50;
	text_analysis->metrics = NULL;

	g_print("After inner relinquish\n");
	return text_analysis;
}

MagickBooleanType add_text(MagickWand *m_wand, DrawingWand *d_wand, Settings *settings, Annotation *annotation)
{

	Text_Analysis * text_analysis;
	text_analysis = drawing_with_split_text(m_wand, settings,  annotation);
	g_print("After analysis\n");

	/* Get analysis of text, retain width and height, free memory for returned metrics.*/
	double *metrics = MagickQueryFontMetrics(m_wand, d_wand, annotation->text_string);
	double text_width = metrics[4];
	double text_height = metrics[5];
	g_print("After metrics\n");

	RelinquishMagickMemory(metrics);
	g_print("After Relinquish\n");
	MagickBooleanType result = MagickAnnotateImage(m_wand, d_wand, 50, 120, 0, annotation->text_string);
	g_print("After annotate\n");
	g_free(text_analysis);
		g_print("After g_free\n");
	return result;
}

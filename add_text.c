#include <stdlib.h>
#include "headers.h"
#include "glib.h"
#include "MagickWand/MagickWand.h"


void drawing_with_split_text(MagickWand *m_wand, Settings *settings, Annotation *annotation, Text_Analysis **text_analysis)
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

	char current_text[settings->max_annotation_length];

	gsize cat_result;
	double *text_metrics;
	double text_width;
	gchar *rightmost_space;

	char *token = strtok(annotation->text_string, " ");
	cat_result = g_strlcpy(current_text, token, settings->max_annotation_length);
	gint64 number_text_lines = 1;
	while ((token = strtok(NULL, " ")) != NULL)
	{
		cat_result = g_strlcat(current_text, " ", settings->max_annotation_length);
		cat_result = g_strlcat(current_text, token, settings->max_annotation_length);
		text_metrics = MagickQueryMultilineFontMetrics(m_wand, my_wand, current_text);
		text_width = text_metrics[4];
		RelinquishMagickMemory(text_metrics);
		if (text_width > max_width)
		{
			rightmost_space = g_strrstr(current_text, " ");
			*rightmost_space = '\n';
			number_text_lines++;
		}
	}
	TypeMetric *type_metrics;
	type_metrics = (TypeMetric *)g_malloc(sizeof(TypeMetric));

	text_metrics = MagickQueryMultilineFontMetrics(m_wand, my_wand, current_text);

	//temp = (Text_Analysis *)g_malloc(sizeof(Text_Analysis));
	//temp->text_height = text_metrics[5];

	*text_analysis = (Text_Analysis *)g_malloc(sizeof(Text_Analysis));
	Text_Analysis *temp = *text_analysis;
	temp->text_wand = my_wand;
	g_aligned_alloc(temp->split_string, current_text, settings->max_annotation_length);
	temp->number_text_lines = number_text_lines;
	temp->y = 0;
	temp->metrics = NULL;
	temp->text_height = text_metrics[5];
	//(*text_analysis)->text_height = text_metrics[5];


	RelinquishMagickMemory(text_metrics);
}

gboolean add_text(MagickWand *m_wand, DrawingWand *d_wand, Settings *settings, Annotation *annotation)
{

	Text_Analysis *text_analysis;
	drawing_with_split_text(m_wand, settings, annotation, &text_analysis);

	/* Get analysis of text, retain width and height, free memory for returned metrics.*/
	double *metrics = MagickQueryFontMetrics(m_wand, d_wand, text_analysis->split_string);
	double text_width = metrics[4];
	double text_height = metrics[5];


	gint64 excess_spacing = text_height - (text_analysis->number_text_lines * settings->font_size );
	gint64 partial_excess_spacing = excess_spacing * 0.75;
	gint64 baseline = \
		(annotation->text_bottom_left.y * annotation->resize_proportion_y) - \
		(text_analysis->number_text_lines * settings->font_size) - \
		partial_excess_spacing;

	gint64 offset = 0;
	if (baseline < 0) {
		offset = abs((int)baseline) + settings->extra_offset;
		// ADD CANVASE ENLARGEMENT HERE
		//new_image.extent(None,new_height + offset ,None,None, 'south')
	}

	gint64 left_offset;
	left_offset = annotation->text_bottom_left.x * annotation->resize_proportion_x;

	MagickBooleanType result = MagickAnnotateImage(m_wand, d_wand, left_offset, baseline + offset, 0, text_analysis->split_string);

	RelinquishMagickMemory(metrics);
	g_print("Hi\n");
	g_free((Text_Analysis *)text_analysis);
		g_print("Bye\n");
	return result;
}

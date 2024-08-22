#include <stdlib.h>

#include "MagickWand/MagickWand.h"
#include "glib.h"
#include "headers.h"

/*void drawing_with_split_text(Settings *settings, Annotation *annotation, Text_Analysis **text_analysis) {
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
	while ((token = strtok(NULL, " ")) != NULL) {
		cat_result = g_strlcat(current_text, " ", settings->max_annotation_length);
		cat_result = g_strlcat(current_text, token, settings->max_annotation_length);
		text_metrics = MagickQueryMultilineFontMetrics(m_wand, my_wand, current_text);
		text_width = text_metrics[4];
		RelinquishMagickMemory(text_metrics);
		if (text_width > max_width) {
			rightmost_space = g_strrstr(current_text, " ");
			*rightmost_space = '\n';
			number_text_lines++;
		}
	}

	TypeMetric *type_metrics = (TypeMetric *)g_malloc(sizeof(TypeMetric));

	text_metrics = MagickQueryMultilineFontMetrics(m_wand, my_wand, current_text);

	// temp = (Text_Analysis *)g_malloc(sizeof(Text_Analysis));
	// temp->text_height = text_metrics[5];

	*text_analysis = (Text_Analysis *)g_malloc(sizeof(Text_Analysis));

	//(*text_analysis)->text_height = text_metrics[5];

	RelinquishMagickMemory(text_metrics);
}*/

void add_text(MagickWand *m_wand, Settings *settings, Annotation *annotation, Text_Analysis *text_analysis) {
	
	DrawingWand *d_wand = NewDrawingWand();
	PixelWand *p_wand = NewPixelWand();

	PixelSetColor(p_wand, settings->balloon_fill_color);
	PixelSetColor(p_wand, settings->text_color);
	DrawSetFillColor(d_wand, p_wand);
	DrawSetGravity(d_wand, NorthWestGravity);

	PixelSetAlpha(p_wand, 1.0);

	//DrawSetStrokeColor(d_wand, p_wand);
	//DrawSetStrokeOpacity(d_wand, 1.0);
	DrawSetFontSize(d_wand, settings->font_size);

	MagickAnnotateImage(m_wand, d_wand, \
		text_analysis->left_offset, \
		text_analysis->bottom_offset  - text_analysis->text_height, \
		0, \
		text_analysis->split_string);

	MagickDrawImage(m_wand, d_wand);

	return;
} 

Text_Analysis *analyze_text(MagickWand *m_wand, Settings *settings, Annotation *annotation) {
	
	Text_Analysis *text_analysis;
	text_analysis = (Text_Analysis *)g_malloc(sizeof(Text_Analysis));
	
	text_analysis->left_offset = annotation->text_bottom_left.x * annotation->resize_proportion_x;
	text_analysis->bottom_offset = annotation->text_bottom_left.y * annotation->resize_proportion_y;
	text_analysis->text_width = 0;
	text_analysis->text_height = 0;

	gint64 max_text_width;
	max_text_width = settings->new_width - \
	text_analysis->left_offset - \
	settings->padding * 2 - \
	settings->stroke_width * 2;

	DrawingWand *d_wand = NewDrawingWand();
	DrawSetFont(d_wand, settings->font);
	DrawSetFontSize(d_wand, settings->font_size);


	gdouble *text_metrics;
	gchar *rightmost_space;

	gchar *token = strtok(annotation->text_string, " ");
	g_strlcpy(text_analysis->split_string, token, settings->max_annotation_length);
	text_analysis->number_text_lines = 1;
	while ((token = strtok(NULL, " ")) != NULL) {
		g_strlcat(text_analysis->split_string, " ", settings->max_annotation_length);
		g_strlcat(text_analysis->split_string, token, settings->max_annotation_length);
		text_metrics = MagickQueryMultilineFontMetrics(m_wand, d_wand, text_analysis->split_string);
		if (text_metrics[4] > max_text_width) {
			rightmost_space = g_strrstr(text_analysis->split_string, " ");
			*rightmost_space = '\n';
			(text_analysis->number_text_lines)++;
		}
		RelinquishMagickMemory(text_metrics);
	}

	text_metrics = MagickQueryMultilineFontMetrics(m_wand, d_wand, text_analysis->split_string);
	text_analysis->text_height = text_metrics[5]; //This may change to + text_metrics[2]
	text_analysis->text_width = text_metrics[4] - text_metrics[6]; //This may change to + text_metrics[2]
	RelinquishMagickMemory(text_metrics);
	return text_analysis;
}

#include <stdlib.h>

#include <wand/MagickWand.h>
#include <glib.h>
#include <headers.h>
/**
 * @file add_text.c
 * @brief Analyzes and places the text on the image.
 */

/**
  Adds text to the image.

  The ImageMagic command <a href="https://imagemagick.org/api/magick-image.php#MagickAnnotateImage">MagickAnnotateImage</a> requires points for placing the text.  See the specification for detail about how those points are computed.
 */
void add_text(MagickWand *m_wand, Theme *theme, User_Data *user_data) {
	
	Text_Analysis *text_analysis = user_data->text_analysis;

	DrawingWand *d_wand = NewDrawingWand();
	PixelWand *p_wand = NewPixelWand();

	/* Set up pixel and drawing wands for adding the text. */
	PixelSetColor(p_wand, theme->balloon_fill_color);
	PixelSetColor(p_wand, theme->text_color);
	PixelSetAlpha(p_wand, 1.0);
	DrawSetFillColor(d_wand, p_wand);
	DrawSetGravity(d_wand, NorthWestGravity);
	DrawSetFontSize(d_wand, theme->font_size);


	gchar *normalized_font_name = g_strdelimit (g_strdup (theme->font_name), " ", '-');

	DrawSetFont(d_wand,normalized_font_name);
	g_print("The font name for drawing is %s\n", theme->font_name);
	g_print("The noramlized font name for drawing is %s\n", normalized_font_name);
	g_free(normalized_font_name);

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
	
} 

/**
  Processes and analyzes the text.

  The user provides the lower-left corner of the text's position. In addition, there is a right margin on the image beyond which the text cannot flow. Using <a href="https://imagemagick.org/api/magick-wand.php#MagickQueryMultilineFontMetrics">MagickQueryMultilineFontMetrics</a>, this function examines the text word-by-word, and inserts newlines `\n` to prevent the text from extending past the margin.
 *
 * At the end of this function, this function saves the dimensions of the resulting text block. These dimenions are used for the following tasks:
 * - Compute the size of the balloon.
 * - Resize as necessary the image upward to contain the balloon.
 */
void analyze_text(MagickWand *m_wand, Theme *theme, User_Data *user_data) {

	Annotation *annotation = user_data->annotation;
	Gui_Data_Annotation *gui_data_annotation = user_data->gui_data->gui_data_annotation;
	Gui_Data_Configuration *gui_data_configuration = user_data->gui_data->gui_data_configuration;
	Text_Analysis *text_analysis = user_data->text_analysis;


	// Need to find another place for this assignment, should not be here. 
	annotation->preview_scale = (float) annotation->dimensions_original_image.height / annotation->dimensions_picture_preview_widget.height;
	
	/* Compute locations where text will be placed. */
	guint text_bottom_left_x = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(gui_data_annotation->spin_text_bottom_left_x));
	guint text_bottom_left_y = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(gui_data_annotation->spin_text_bottom_left_y));
	
	text_analysis->left_offset = 
		text_bottom_left_x * 
		annotation->preview_scale * 
		annotation->resize_proportion_x;
	text_analysis->bottom_offset = 
		text_bottom_left_y * 
		annotation->preview_scale *
		annotation->resize_proportion_y;
	text_analysis->text_width = 0;
	text_analysis->text_height = 0;
	text_analysis->overflow = 0;
	text_analysis->balloon_midpoint = 0;
	text_analysis->balloon_bottom = 0;


	/* Determine the maximal width of the text. */
	guint new_width = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(gui_data_annotation->spin_new_width));
	guint padding = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(gui_data_configuration->spin_padding ));

	gint64 max_text_width = new_width - \
		text_analysis->left_offset - \
		padding * 2 - \
		theme->stroke_width * 2;

	/* Set up wand for drawing text. */
	DrawingWand *d_wand = NewDrawingWand();
	DrawSetFont(d_wand, theme->font_name);
	DrawSetFontSize(d_wand, theme->font_size);


	gdouble *text_metrics;
	gchar *rightmost_space;

	/* Parse the annotation, placing newlines in places where the string exceeds max_text_width. */

	const gchar *text_string = gtk_editable_get_text (GTK_EDITABLE(user_data->gui_data->gui_data_annotation->entry_text_string));

	gchar *text_string_copy = g_strdup (text_string);

	guint max_annotation_length = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(gui_data_configuration->spin_max_annotation_length));

	gchar *token = strtok(text_string_copy, " ");
	g_strlcpy(text_analysis->split_string, token, max_annotation_length);
	while ((token = strtok(NULL, " ")) != NULL) {
		g_strlcat(text_analysis->split_string, " ", max_annotation_length);
		g_strlcat(text_analysis->split_string, token, max_annotation_length);
		text_metrics = MagickQueryMultilineFontMetrics(m_wand, d_wand, text_analysis->split_string);
		if (text_metrics[4] > max_text_width) {
			rightmost_space = g_strrstr(text_analysis->split_string, " ");
			*rightmost_space = '\n';
		}
		RelinquishMagickMemory(text_metrics);
	}


	g_free(text_string_copy);

	/* Save the text's height and width. These will be used to determine the balloon's height and width. */
	text_metrics = MagickQueryMultilineFontMetrics(m_wand, d_wand, text_analysis->split_string);
	text_analysis->text_height = text_metrics[5]; //This may change to + text_metrics[2]
	//The following line sometimes works with 
	//text_metrics[4] - text_metrics[6];
	//text_metrics[4] - text_metrics[6] + text_metrics[2] ;
	text_analysis->text_width = text_metrics[4]; //This may change to + text_metrics[2]
	
	/* Clean up */
	RelinquishMagickMemory(text_metrics);
	DestroyDrawingWand(d_wand);
}

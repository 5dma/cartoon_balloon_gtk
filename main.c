#include <stdio.h>
#include "glib.h"
#include "wand/magick_wand.h"
#include "headers.h"

/* https://imagemagick.org/api/magick-image.php */
/* https://imagemagick.org/api/drawing-wand.php */
/* https://imagemagick.org/api/pixel-wand.php */
int main(int argc, char *argv[])
{

	Settings *settings;
	settings = read_json();
	if (settings == NULL)
	{
		return 0;
	}

	MagickWand *m_wand = NULL;

	gint64 old_width, old_height;

	MagickWandGenesis();
	m_wand = NewMagickWand();

	MagickBooleanType result = MagickReadImage(m_wand, "/Users/mlautman/Documents/graphics/tolstoy_2.jpg");

	if (result == MagickFalse)
	{
		g_print("Could not read the image %s. Exiting\n", "/Users/mlautman/Documents/graphics/tolstoy_2.jpg");
		return -1;
	}

	Annotation *annotation;
	annotation = read_annotation(settings);
	if (annotation == NULL)
	{
		return 0;
	}
	g_print("The annotation text is %s\n", annotation->text_string);

	/* Resize the image */
	resize(m_wand, settings, annotation);

	DrawingWand *d_wand = NewDrawingWand();
	PixelWand *p_wand = NewPixelWand();
	PixelSetColor(p_wand, settings->balloon_stroke_color);
	
	PixelSetAlpha(p_wand, 1.0);

	DrawSetStrokeColor(d_wand, p_wand);
	DrawSetStrokeWidth(d_wand, settings->stroke_width);
	DrawSetStrokeOpacity(d_wand, 1.0);
	DrawSetFontSize(d_wand, settings->font_size );
	DrawSetFontFamily(d_wand, settings->font);

		//DrawLine(d_wand, 20, 20, 300, 100);

PixelWand *p_wand_text = NewPixelWand();
DrawingWand *d_wand_text = NewDrawingWand();
	PixelSetColor(p_wand_text, settings->balloon_stroke_color);
	
	PixelSetAlpha(p_wand_text, 1.0);

	DrawSetStrokeColor(d_wand_text, p_wand_text);
	DrawSetStrokeWidth(d_wand_text, settings->stroke_width);
	DrawSetStrokeOpacity(d_wand_text, 1.0);
	DrawSetFontSize(d_wand_text, settings->font_size );

	result = add_text(m_wand, d_wand_text, settings, annotation);
	
	result = MagickAnnotateImage(m_wand, d_wand_text, 300, 300, 0, "I REALLY AM GOING TO BARF");



PixelSetColor(p_wand, settings->balloon_fill_color);
	DrawSetFillColor(d_wand, p_wand);
	DrawRectangle(d_wand, 20, 20, 100, 100);

	result = PixelSetColor(p_wand,"#ff0000");
	DrawSetFillColor(d_wand, p_wand);
	add_balloon(m_wand, d_wand, settings, annotation);

//DrawingWand *d_wand_text = NewDrawingWand();

//	PixelWand *p_wand_text = NewPixelWand();
	PixelSetColor(p_wand_text, settings->balloon_stroke_color);
	
	PixelSetAlpha(p_wand_text, 1.0);

	DrawSetStrokeColor(d_wand_text, p_wand_text);
	DrawSetStrokeWidth(d_wand_text, settings->stroke_width);
	DrawSetStrokeOpacity(d_wand_text, 1.0);
	DrawSetFontSize(d_wand_text, settings->font_size );

	result = add_text(m_wand, d_wand_text, settings, annotation);
	
	MagickAnnotateImage(m_wand, d_wand_text, 300, 300, 0, "I REALLY AM GOING TO BARF");
	
	


	
	MagickDrawImage(m_wand, d_wand);

	/* Write the new image */
	MagickWriteImage(m_wand, settings->new_image_path);

	/* Clean up */
	DestroyPixelWand(p_wand);
	DestroyDrawingWand(d_wand);
	if (m_wand)
		m_wand = DestroyMagickWand(m_wand);

	MagickWandTerminus();
	g_print("The new image is at %s\n", settings->new_image_path);
	g_free(settings);
	g_free(annotation);

	return 0;
}
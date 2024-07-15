#include <stdio.h>
#include "glib.h"
#include <wand/magick_wand.h>
#include "headers.h"

/* https://imagemagick.org/api/magick-image.php */
/* https://imagemagick.org/api/drawing-wand.php */
/* https://imagemagick.org/api/pixel-wand.php */
int main(int argc, char *argv[])
{

	Settings * settings;
	settings = read_json();
	if (settings == NULL) {
		return 0;
	}

	MagickWand *m_wand = NULL;
	
	gint64 old_width, old_height;
	
	MagickWandGenesis();
	m_wand = NewMagickWand();
	
	MagickReadImage(m_wand,"/Users/mlautman/Documents/graphics/light-snack.jpg");

	/* Resize the image */
	resize(m_wand, settings);
		
	DrawingWand * d_wand =  NewDrawingWand();
	PixelWand * p_wand = NewPixelWand();
	PixelSetColor(p_wand,  "#0000ff");
	PixelSetAlpha(p_wand,1.0);


	DrawSetStrokeColor(d_wand, p_wand);
	DrawSetStrokeWidth(d_wand, settings -> stroke_width);
	DrawSetStrokeOpacity(d_wand, 1.0);

	DrawLine(d_wand, 20,20, 300, 100);

	MagickDrawImage(m_wand,d_wand);

	/* Write the new image */
	MagickWriteImage(m_wand, settings -> new_image_path);
	
		/* Clean up */
	DestroyPixelWand(p_wand);
	DestroyDrawingWand(d_wand);
	if (m_wand) m_wand = DestroyMagickWand(m_wand);
	
	MagickWandTerminus();
	g_print("The new image is at %s\n", settings -> new_image_path);
	g_free(settings);


	return 0;
}
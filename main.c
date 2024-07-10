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
	g_print("font size %lli \n",settings->font_size);
	g_print("balloon_fill_color %s \n",settings->balloon_fill_color);

	MagickWand *m_wand = NULL;
	
	gint64 old_width, old_height;
	
	MagickWandGenesis();
	m_wand = NewMagickWand();
	// Read the image - all you need to do is change "logo:" to some other
	// filename to have this resize and, if necessary, convert a different file
	MagickReadImage(m_wand,"/Users/mlautman/Documents/graphics/light-snack.jpg");
	old_width = MagickGetImageWidth(m_wand);
	old_height = MagickGetImageHeight(m_wand);

	gint64 new_height;
	new_height = (settings->new_width * old_height ) / old_width;

	// Resize the image using the Lanczos filter
	// The blur factor is a "double", where > 1 is blurry, < 1 is sharp

	MagickResizeImage(m_wand, settings->new_width ,new_height,LanczosFilter,1);
	
	DrawingWand * d_wand =  NewDrawingWand();
	PixelWand * p_wand = NewPixelWand();
	PixelSetColor(p_wand,  "#0000ff");
	PixelSetAlpha(p_wand,1.0);


	DrawSetStrokeColor(d_wand, p_wand);
	DrawSetStrokeWidth(d_wand, 4.0);
	DrawSetStrokeOpacity(d_wand, 1.0);

	DrawLine(d_wand, 20,20, 300, 100);


	/* Write the new image */
	MagickWriteImage(m_wand,"/tmp/logo_resize.jpg");
	
	DestroyDrawingWand(d_wand);

	/* Clean up */
	if (m_wand) m_wand = DestroyMagickWand(m_wand);
	
	MagickWandTerminus();
	printf("Finished\n");
	g_free(settings);
	return 0;
}
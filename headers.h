#include <wand/magick_wand.h>
#include "glib.h"

typedef struct Settings
{
	gint64 new_width;
	char balloon_fill_color[8];
	char balloon_stroke_color[8];
	gint64 excess_font_height;
	gint64 padding;
	gint64 excess_text_height;
	gint64 callout_indent;
	gint64 callout_space;
	gint64 elevation;
	gint64 space;
	gint64 stroke_width;
	gint64 extra_offset;
	gint64 font_size;
	char font[256];
	char new_image_path[256];
} Settings;

typedef struct Coordinates
{
	gint64 x;
	gint64 y;
} Coordinates;

typedef struct Annotation
{
	char text_string[256];
	float resize_proportion_x;
	float resize_proportion_y;
	Coordinates text_bottom_left;
	Coordinates callout_vertex;
} Annotation;

Settings * read_json();
Annotation * read_annotation();
void resize (MagickWand *m_wand, Settings * settings, Annotation * annotation );
void add_text (MagickWand *m_wand, Settings * settings, Annotation * annotation);

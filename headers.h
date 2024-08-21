#include "MagickWand/MagickWand.h"
#include "glib.h"

typedef struct Settings
{
	gint64 new_width;
	gint32 max_annotation_length;
	gchar balloon_fill_color[8];
	gchar balloon_stroke_color[8];
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
	gchar font[256];
	gchar new_image_path[256];
} Settings;

typedef struct Coordinates
{
	gint64 x;
	gint64 y;
} Coordinates;

typedef struct Annotation
{
	gchar text_string[256];
	gchar original_image_path[256];
	float resize_proportion_x;
	float resize_proportion_y;
	Coordinates text_bottom_left;
	Coordinates callout_vertex;
} Annotation;

typedef struct Text_Analysis
{
	DrawingWand *text_wand;
	gchar split_string[300];
	gint64 number_text_lines;
	gint64 y;//What is this for?
	TypeMetric *metrics;
	gint64 text_height;
} Text_Analysis;

Settings *read_json();
Annotation *read_annotation(Settings *settings);
void resize(MagickWand *m_wand, Settings *settings, Annotation *annotation);
void add_text(MagickWand *m_wand, Settings *settings, Annotation *annotation);
void add_balloon(MagickWand *m_wand, Settings *settings, Annotation *annotation);
GLogWriterOutput logWriter(GLogLevelFlags log_level, const GLogField *fields, size_t n_fields, void *user_data);


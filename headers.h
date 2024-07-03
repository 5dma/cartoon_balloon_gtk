typedef struct Settings
{
	gint64 new_width;
	char balloon_fill_color[7];
	char balloon_stroke_color[7];
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

Settings * read_json();
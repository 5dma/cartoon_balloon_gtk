#include "MagickWand/MagickWand.h"
#include "glib.h"
/**
 * @file headers.h
 * @brief C headers.
 */

/**
 * Structure containing user-defined configuration. The settings in this struct, such as the ballon's fill color, file are relatively static: they can apply to multiple images. The function read_json() reads the values from a JSON file.
 * 
 * All dimensions in this structure are in pixels. For a visual representation of the dimensions, see the specification.
 */
typedef struct Settings
{
	gint64 new_width; /**< Maximal width of the resulting image. For Twitter, 520 is a good value. */
	gint32 max_annotation_length; /**< Maximal length of an annotation. A reasonable value is 256. */
	gchar balloon_fill_color[8]; /**< Hex value of the fill color including the octothorp. For example, white is `#FFFFFF`.*/
	gchar balloon_stroke_color[8]; /**< Hex value of the fill color including the octothorp. For example, black is `#000000`.*/
	gint64 padding; /**< Padding around the text box. The balloon is drawn around the padding.*/
	gint64 elevation; /**< Height of the polyline inside the balloon.*/
	gint64 space; /**< Space between the balloon's midpoint and where the polyline intersects with the balloon.*/
	gint64 stroke_width; /**< Stroke width around balloon and polyline.*/
	gint64 top_margin; /**< Top margin, measured from the top of the image to the top of the balloon.*/
	gint64 font_size; /**< Font size, in points.*/
	gchar text_color[8]; /**< Hex value of the text color including the octothorp. For example, white is `#FFFFFF`.*/
	gchar font[256]; /**< Name of the font, provided as the font's full name with spaces replaced by underscore. For example, the command `fc-scan --format "%{fullname}\n" DejaVuSerif-Bold.ttf` gives `DejaVu Serif Bold`. Therefore, the font name in the configuration file needs to be `DejaVu_Serif_Bold` */
	gchar new_image_path[256]; /**< Maximal length of the new image's path. A reasonable value is 256. */
} Settings;

/**
 * Structure representing a point on the image.
 */
typedef struct Coordinates
{
	gint64 x; /**< x-coordinate. */
	gint64 y; /**< y-coordinate. */
} Coordinates;

/**
 * Structure containing user-defined information about the positioning of the text and polyline on the final image.
 */
typedef struct Annotation
{
	gchar text_string[256];  /**< Maximal length of the text. A reasonable value is 256. */
	gchar original_image_path[256]; /**< Maximal length of the original image's path. A reasonable value is 256. */
	float resize_proportion_x; /**< Proportion the image is resized in the x direction so that it does not exceed the maximal width. */
	float resize_proportion_y; /**< Proportion the image is resized in the y direction so that it does not exceed the maximal width. (Typically matches `resize_proportion_x`.) */
	Coordinates text_bottom_left; /**< Position of the text's bottom-left corner on the final image. */
	Coordinates callout_vertex; /**< Position of the polyline's vertex on the final image. */
} Annotation;

/**
 * Structure representing the final positioning of text and the surrounding balloon. For a visual representation of the dimensions in this struct, see the specification.
 */
typedef struct Text_Analysis
{
	gchar split_string[300]; /**< User's original string and inserted newline characters to prevent overflow beyond the right margin. */
	gint64 left_offset; /**< Position of the text's left side. This may be different from what the user requested because of scaling. */
	gint64 bottom_offset;/**< Position of the text's bottom side. This may be different from what the user requested because of scaling. */
	gint64 text_height; /**< Height of the text. Depends on the font and font size. */
	gint64 text_width; /**< Width of the text. Depends on the font and font size. */
	gint64 overflow; /**< Distance from the top of the image to the top of the balloon and top margin. If this number is negative, the image needs to be resized vertically to accommodate the text, balloon, and top margin. */
	gint64 balloon_midpoint;/**< Horizontal midpoint of the balloon. Required to position the x-coordinate of the polyline's intersection with the balloon. */
	gint64 balloon_bottom; /**< Bottom edge of the balloon. Required to position the y-coordinate of the polyline's intersection with the balloon. */
} Text_Analysis;

Settings *read_json();
Annotation *read_annotation(Settings *settings);
void scale_image(MagickWand *m_wand, Settings *settings, Annotation *annotation);
void add_text(MagickWand *m_wand, Settings *settings, Annotation *annotation, Text_Analysis *text_analysis);
void add_balloon(MagickWand *m_wand, Settings *settings, Annotation *annotation, Text_Analysis *text_analysis);
Text_Analysis * analyze_text(MagickWand *m_wand, Settings *settings, Annotation *annotation);
void resize_image(MagickWand *m_wand, Settings *settings, Text_Analysis * text_analysis);
void add_path(MagickWand *m_wand, Annotation *annotation, Settings *settings, Text_Analysis *text_analysis);
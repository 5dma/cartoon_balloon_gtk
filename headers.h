#include "wand/MagickWand.h"
#include "glib.h"
#include <gtk/gtk.h>
#include <json-glib/json-glib.h>

/**
 * @file headers.h
 * @brief C headers.
 */

/**
   \brief Path to the application's configuration file.
*/
#define CONFIG_FILE "/home/abba/.cartoon_balloon/settings.json"

/**
   \brief Maximal length of a file path.
*/
#define MAX_PATH_LENGTH 256

/**
 * Structure containing user-defined configuration. The settings in this struct, such as the ballon's fill color, file are relatively static: they can apply to multiple images. The function read_json() reads the values from a JSON file.
 * 
 * All dimensions in this structure are in pixels. For a visual representation of the dimensions, see the specification.
 */
typedef struct Configuration {
	gint64 max_annotation_length; /**< Maximal number of characters in an annotation. */
	gint64 padding; /**< Padding around the text box. The balloon is drawn around the padding.*/
	gint64 elevation; /**< Height of the polyline inside the balloon.*/
	gint64 space; /**< Space between the balloon's midpoint and where the polyline intersects with the balloon.*/
	gint64 top_margin; /**< Top margin, measured from the top of the image to the top of the balloon.*/
	gchar new_image_path[256]; /**< Maximal length of the new image's path. A reasonable value is 256. */
	gchar log_file_path[256]; /**< Path to log file. */
	FILE * log_file_pointer; /**< Address of the log file's handle. */
} Configuration;

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
	gchar input_image[256]; /**< Maximal length of the original image's path. A reasonable value is 256. */
	Coordinates text_bottom_left; /**< Position of the text's bottom-left corner on the final image. */
	Coordinates vertex; /**< Position of the polyline's vertex on the final image. */
	gint64 new_width; /**< Maximal width of the resulting image. For Twitter, 520 is a good value. */
	gchar text_string[256];  /**< Maximal length of the text. A reasonable value is 256. */
	gchar theme[256];  /**< Theme to apply to the text and balloon.  */
	float resize_proportion_x; /**< Proportion the image is resized in the x direction so that it does not exceed the maximal width. */
	float resize_proportion_y; /**< Proportion the image is resized in the y direction so that it does not exceed the maximal width. (Typically matches `resize_proportion_x`.) */
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

/**
 * Structure representing a theme, comprised of properties for colors, font, and stroke. Themes are user-defined, along with a default theme configured in Settings.
 */
typedef struct Theme
{
	gchar name[100];  /**< Name of the theme. */
	gchar text_color[8]; /**< Hex value of the text color including the octothorp. For example, white is `#FFFFFF`.*/
	gchar font[256]; /**< Name of the font, provided as the font's full name with spaces replaced by hyphens. For example, the command `fc-scan --format "%{fullname}\n" DejaVuSerif-Bold.ttf` gives `DejaVu Serif Bold`. Therefore, the font name in the configuration file needs to be `DejaVu-Serif-Bold` */
	gint64 font_size; /**< Font size, in points.*/
	gint64 stroke_width; /**< Stroke width around balloon and polyline.*/
	gchar balloon_fill_color[8]; /**< Hex value of the fill color including the octothorp. For example, white is `#FFFFFF`.*/
	gchar balloon_stroke_color[8]; /**< Hex value of the fill color including the octothorp. For example, black is `#000000`.*/
} Theme;

/**
 * Structure holding settings in the GUI.
 */
typedef struct Gui_Data {
	GtkWidget * box_top; /**< Address of the box_top widget. */
	GtkWidget * box_annotation; /**< Address of the box_annotation widget. */
	GtkWidget * box_theme; /**< Address of the box_theme widget. */
	GtkWidget * box_configuration; /**< Address of the box_configuration widget. */
	GtkWidget *spin_max_annotation_length;
	GtkCssProvider * provider; /**< Address of the `GtkCssProvider` instance. */
} Gui_Data;

/**
 * Parent structure for passing all settings between callbacks.
 */
typedef struct User_Data
{
	Configuration * configuration; /**< Address of the settings structure. */
	Annotation * annotation; /**< Address of the annotation structure. */
	GHashTable * theme_hash; /**< Hash table of themes, keyed by theme name. */
	Text_Analysis * text_analysis; /**< Address of the text_analysis structure. */
	Gui_Data * gui_data; /**< Address of the gui_data structure. */
	JsonParser *parser; /**< Address of a JSON parser. */
	JsonReader *reader; /**< Address of a JSON reader. */

} User_Data;

/* Processing headers */
void read_configuration(User_Data * user_data);
void read_annotation(User_Data * user_data);
void read_themes(User_Data * user_data);
void scale_image(MagickWand *m_wand, Annotation *annotation);
void add_text(MagickWand *m_wand, Configuration *configuration, Theme *theme, Annotation *annotation, Text_Analysis *text_analysis);
void add_balloon(MagickWand *m_wand, Configuration *configuration, Theme *theme, Annotation *annotation, Text_Analysis *text_analysis);
Text_Analysis * analyze_text(MagickWand *m_wand, Configuration *configuration, Theme *theme, Annotation *annotation);
void resize_image(MagickWand *m_wand, Annotation *annotation, Configuration *configuration, Theme *theme, Text_Analysis *text_analysis);
void add_path(MagickWand *m_wand, Annotation *annotation, Configuration *configuration, Theme *theme, Text_Analysis *text_analysis);
void apply_theme(GHashTable * theme_hash, const Annotation * annotation, Configuration **configuration);
void process_image(Configuration *configuration, GHashTable *theme_hash, Annotation *annotation);

/* GTK headers */
void activate (GtkApplication* app, gpointer  user_data);

/* Logger headers */
FILE * get_log_file_pointer(Configuration *configuration);
void logger(GLogLevelFlags log_level, const gchar *message, User_Data *user_data);

/* GUI headers */
GtkWidget * build_box_annotation();
GtkWidget * build_box_theme();
GtkWidget * build_box_configuration();
#pragma once
#include <wand/MagickWand.h>
#include <glib.h>
#include <gtk/gtk.h>
#include <json-glib/json-glib.h>
/**
 * @file headers.h
 * @brief C headers.
 */

/**
   \brief Maximal length of a file path.
*/
#define MAX_PATH_LENGTH 256

/**
   \brief Static string indicating a new theme.
*/
#define NEW_THEME "(new)"


/**
 * Structure containing various paths and pointers.
 */
typedef struct Configuration {
	gchar new_image_path[256]; /**< Maximal length of the new image's path. A reasonable value is 256. */
	gchar log_file_path[256]; /**< Path to log file. */
	FILE *log_file_pointer; /**< Address of the log file's handle. */
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
 * Structure representing dimensions of an object, such as a graphic or a drawing.
 */
typedef struct Dimensions
{
	gint width; /**< width. */
	gint height; /**< height. */
} Dimensions;


/**
 * Structure containing user-defined information about the positioning of the text and polyline on the final image.
 */
typedef struct Annotation
{
	float resize_proportion_x; /**< Proportion the image is resized in the x direction so that it does not exceed the maximal width. */
	float preview_scale; /**< Ratio of the original image's height to the preview height. */
	float resize_proportion_y; /**< Proportion the image is resized in the y direction so that it does not exceed the maximal width. (Typically matches `resize_proportion_x`.) */
	Dimensions dimensions_picture_preview_widget; /**< Dimensions of the widget containing the displayed image.) */
	Dimensions dimensions_original_image; /**< Dimensions of the actual image (not scaled). */
	Coordinates coordinates_scaled_image_top_left; /**< Coordinates of the top-left corner of the image inside inside the preview widget. */
	Coordinates coordinates_scaled_image_bottom_right; /**< Coordinates of the bottom-right corner of the image inside inside the preview widget. */
	GdkCursor *crosshair_cursor; /**< Pointer to a crosshair cursor. */
	gboolean is_selecting_vertex_point; /**< Indicates user is selecting a vertex point on the image preview. */
	gboolean is_selecting_text_bottom_left_point; /**< Indicates user is selecting a text_bottom_left point on the image preview. */
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
	gchar font_name[MAX_PATH_LENGTH]; /**< Name of the font, provided as the font's full name with spaces replaced by hyphens. For example, the command `fc-scan --format "%{fullname}\n" DejaVuSerif-Bold.ttf` gives `DejaVu Serif Bold`. Therefore, the font name in the configuration file needs to be `DejaVu-Serif-Bold`. (A more complete command is `fc-scan --format "%{fullname}\n" DejaVuSerif-Bold.ttf | sed "s/ /-/g"` .)

	A list of fonts is available from `fc-list`. 
	 */
	gint64 font_size; /**< Font size, in points.*/
	gint64 stroke_width; /**< Stroke width around balloon and polyline.*/
	gchar balloon_fill_color[8]; /**< Hex value of the fill color including the octothorp. For example, white is `#FFFFFF`.*/
	gchar balloon_stroke_color[8]; /**< Hex value of the fill color including the octothorp. For example, black is `#000000`.*/
} Theme;

/**
 * Structure for holding pointers to widgets in the Configuration tab.
 */
typedef struct Gui_Data_Configuration {
	GtkWidget *box_configuration; /**< Address of the box_configuration widget. */
	GtkWidget *spin_max_annotation_length; /**< Address of spin_max_annotation_length in the configuration tab. */
	GtkWidget *spin_padding; /**< Address of padding in the configuration tab. */
	GtkWidget *spin_elevation; /**< Address of elevation in the configuration tab. */
	GtkWidget *spin_space; /**< Address of space in the configuration tab. */
	GtkWidget *spin_top_margin; /**< Address of top_margin in the configuration tab. */
} Gui_Data_Configuration;

/**
 * Structure for holding pointers to widgets in the Annotation tab.
 */
typedef struct Gui_Data_Annotation {
	GtkWidget *btn_annotation; /**< Address of the btn_annotation. */
	GtkWidget *box_annotation; /**< Address of the box_annotation widget. */
	GtkWidget *entry_input_image; /**< Address of entry_input_image in the box_annotation tab. */
	GtkWidget *btn_file_open;  /**< Address of btn_file_open in the box_annotation tab. */
	GtkWidget *spin_text_bottom_left_x; /**< Address of spin_text_bottom_left_x in the box_annotation tab. */
	GtkWidget *spin_text_bottom_left_y; /**< Address of spin_text_bottom_left_y in the box_annotation tab. */
	GtkWidget *spin_vertex_x; /**< Address of spin_vertex_x in the box_annotation tab. */
	GtkWidget *spin_vertex_y; /**< Address of spin_vertex_y in the box_annotation tab. */
	GtkWidget *btn_point_vertex; /**< Address of btn_point_vertex in the box_annotation tab. */
	GtkWidget *btn_point_text_bottom;  /**< Address of btn_point_text_bottom in the box_annotation tab. */
	GtkWidget *spin_new_width; /**< Address of spin_new_width in the box_annotation tab. */
	GtkWidget *dropdown_theme; /**< Address of theme in the box_annotation tab. */
	GtkWidget *entry_text_string; /**< Address of the entry_text_string in the box_annotaton tab. */
	GtkWidget *btn_export; /**< Address of btn_export in the box_annotation tab. */
	GtkWidget *picture_preview; /**< Address of the picture_preview in the box_annotaton tab. */
	GtkFileFilter *file_filter; /**< Address of the file filter applied to the file chooser in the annotation tab. */
} Gui_Data_Annotation;

/**
 * Structure for holding pointers to widgets in the Themes tab.
 */
typedef struct Gui_Data_Theme {
	GtkWidget *dropdown_theme; /**< Address of the dropdown_theme widget. */
	GtkWidget *entry_new_theme; /**< Address of the entry_new_theme widget. */
	GtkWidget *entry_font_color; /**< Address of the entry_font_color widget. */
	GtkWidget *entry_fill_color; /**< Address of the entry_fill_color widget. */
	GtkWidget *entry_stroke_color; /**< Address of the entry_stroke_color widget. */
	GtkWidget *spin_stroke_width; /**< Address of the spin_stroke_width widget. */
	GtkWidget *drawing_balloon;  /**< Address of the drawing_balloon widget. */
	GtkWidget *btn_font_name_picker; /**< Address of the Font name's Choose widget. */
	GtkWidget *btn_font_color_picker; /**< Address of the text color picker. */
	GtkWidget *btn_balloon_fill_color_picker; /**< Address of the baloon fill color picker. */
	GtkWidget *btn_balloon_stroke_color_picker; /**< Address of the baloon stroke color picker. */
	GtkWidget *grid_text; /**< Address of the grid containing the theme's text controls. */
	GtkWidget *grid_balloon; /**< Address of the grid containing the theme's balloon controls. */
	GtkWidget *btn_delete;  /**< Address of the Delete button. */
	cairo_t *cr; /**< Address of the Cairo context in the theme preview. */
} Gui_Data_Theme;


/**
 * Structure holding settings in the GUI.
 */
typedef struct Gui_Data {
	GtkWidget *window;  /**< Address of the application window. */
	GtkWidget *box_top; /**< Address of the box_top widget. */
	GtkWidget *box_theme; /**< Address of the box_theme widget. */
	Gui_Data_Configuration *gui_data_configuration; /**< Structure containing pointers to controls in the Configuration tab. */
	Gui_Data_Annotation *gui_data_annotation; /**< Structure containing pointers to controls in the Annotation tab. */
	Gui_Data_Theme *gui_data_theme; /**< Structure containing pointers to controls in the Themes tab. */
	GtkCssProvider *provider; /**< Address of the `GtkCssProvider` instance. */
	GtkWidget *status_bar; /**< Address of the status_bar widget. */
} Gui_Data;

/**
 * Structure holding geometric configuration for drawing the theme preview in the Theme tab.
 */
typedef struct Theme_Geometry {
	Coordinates balloon_top_left;  /**< Coordinates for balloons top-left corner. */
	Coordinates balloon_bottom_right;  /**< Coordinates for balloons top-left corner. */
	Coordinates vertex_left; /**< Coordinates for vertex left side. */
	Coordinates vertex_bottom; /**< Coordinates for vertex bottom. */
	Coordinates vertex_right; /**< Coordinates for vertex right side. */
	Coordinates text_start;  /**< Coordinates where text starts. */
} Theme_Geometry;

/**
 * Parent structure for passing all settings between callbacks.
 */
typedef struct User_Data
{
	Configuration *configuration; /**< Address of the settings structure. */
	Annotation *annotation; /**< Address of the annotation structure. */
	GHashTable *theme_hash; /**< Hash table of themes, keyed by theme name. */
	GListStore *list_store_themes; /**< Address of list store backing the theme dropdowns. */
	Text_Analysis *text_analysis; /**< Address of the text_analysis structure. */
	Gui_Data *gui_data; /**< Address of the gui_data structure. */
	Theme_Geometry *theme_geometry;  /**< Address of theme geometry. */
} User_Data;

/* Processing headers */
void scale_image(MagickWand *m_wand, User_Data *user_data);
void add_text(MagickWand *m_wand, Theme *theme, User_Data *user_data);
void add_balloon(MagickWand *m_wand, Theme *theme, User_Data *user_data);
void analyze_text(MagickWand *m_wand, Theme *theme, User_Data *user_data);
void resize_image(MagickWand *m_wand, Theme *selected_theme, User_Data *user_data);
void add_path(MagickWand *m_wand, Theme *theme, User_Data *user_data);
void process_image(User_Data *user_data);

/* GTK headers */
void activate (GtkApplication*app, gpointer  user_data);


/* Logger headers */
FILE *get_log_file_pointer(Configuration *configuration);
void logger(GLogLevelFlags log_level, const gchar *message, User_Data *user_data);
void log_configuration_values(User_Data *user_data);
void populate_status_bar( GtkWidget *status_bar, const gchar *formatting_string, ...);

/* GUI headers */
GtkWidget *build_box_annotation(User_Data *user_data);
GtkWidget *build_box_theme(User_Data *user_data);
GtkWidget *build_box_configuration(User_Data *user_data);
void initialize_gui(User_Data *user_data);

/* Controller (callback) headers*/
void build_controllers_annotation(User_Data *user_data);
void build_controllers_theme(User_Data *user_data);
void build_controllers_window(User_Data *user_data);
void theme_selection_changed(GObject *self, GParamSpec *pspec, gpointer data);
gint comparestrings (gconstpointer a, gconstpointer b, gpointer user_data);
gpointer get_selected_theme_from_hash(User_Data *user_data, GtkWidget *dropdown_theme);
void on_annotation_spinner_changed (GtkSpinButton* self, gpointer data);

/* Memory management headers */
User_Data *allocate_structures(void);
void cleanup(User_Data *user_data);

/* read/save settings headers */
void read_files(User_Data *user_data);
void save_files(User_Data *user_data);
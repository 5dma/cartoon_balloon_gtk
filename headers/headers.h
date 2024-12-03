#include <wand/MagickWand.h>
#include <structures.h>
/**
 * @file headers.h
 * @brief Contains function headers.
 */


/**
   \brief Static string indicating a new theme in a dropdown box.
*/
#define NEW_THEME "(new)"


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

/* Memory management headers */
User_Data *allocate_structures(void);
void cleanup(User_Data *user_data, gboolean detailed);

/* read/save settings headers */
void read_files(User_Data *user_data);
void save_files(User_Data *user_data);
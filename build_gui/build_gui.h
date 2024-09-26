#include <gtk/gtk.h>
#include "../headers.h"
/**
 * @file build_gui.h
 * @brief GUI headers.
 */


/* GUI headers */
GtkWidget * build_box_annotation();
GtkWidget * build_box_theme();
GtkWidget * build_box_configuration(User_Data *user_data);
void initialize_gui(User_Data *user_data);
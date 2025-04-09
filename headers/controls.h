#include <gtk/gtk.h>
/**
 * @file controls.h
 * @brief Contains headers for callbacks in the annotation and theme tabs.
 */


/* Headers for annotation tab callbacks */
void show_annotation_tab(GtkWidget *widget, gpointer data);
void select_input_file(GtkWidget *widget, gpointer data);
void on_btn_vertex_clicked(GtkWidget *widget, gpointer data);
void on_btn_text_bottom_clicked(GtkWidget *widget, gpointer data);
void on_mouse_enter_image(GtkEventControllerMotion *self, gdouble x, gdouble y, gpointer data);
void on_mouse_motion_image(GtkEventControllerMotion *self, gdouble x, gdouble y, gpointer data);
void preview_clicked(GtkGestureClick *self, gint n_press, gdouble x, gdouble y, gpointer data);
void launch_processing(GtkWidget *widget, gpointer data);

/* Headers for theme tab callbacks */
void save_selected_font_to_theme(GtkButton *self, gpointer data);
void save_selected_font_color_to_theme(GtkColorButton *self, gpointer data);
void save_selected_balloon_fill_color_to_theme(GtkColorButton *self, gpointer data);
void save_selected_balloon_stroke_color_to_theme(GtkColorButton *self, gpointer data);
void save_selected_stroke_width_to_theme(GtkSpinButton *self, gpointer data);
void theme_selection_changed(GObject *self, GParamSpec *pspec, gpointer data);
void draw_theme(GtkDrawingArea *drawing_area, cairo_t *cr, int width, int height, gpointer data);
void get_new_theme_name(GtkWidget *self, gpointer data);
void new_theme(GtkEventControllerFocus *self, gpointer data);
void delete_theme(GtkButton *self, gpointer data);
void draw_annotated_preview(GtkDrawingArea *drawing_area, cairo_t *cr, int width, int height, gpointer data);

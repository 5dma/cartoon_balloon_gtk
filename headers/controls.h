#include <gtk/gtk.h>

void show_annotation_tab(GtkWidget *widget, gpointer data);
void select_input_file(GtkWidget *widget, gpointer data);
void on_btn_vertex_clicked(GtkWidget *widget, gpointer data);
void on_btn_text_bottom_clicked(GtkWidget *widget, gpointer data);
void on_mouse_enter_image(GtkEventControllerMotion *self, gdouble x, gdouble y, gpointer data);
void on_mouse_motion_image(GtkEventControllerMotion *self, gdouble x, gdouble y, gpointer data);
void preview_clicked(GtkGestureClick *self, gint n_press, gdouble x, gdouble y, gpointer data);
void launch_processing(GtkWidget *widget, gpointer data);
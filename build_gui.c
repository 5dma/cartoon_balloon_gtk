#include <gtk/gtk.h>

void activate (GtkApplication* app, gpointer  user_data)
{
  GtkWidget *window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

  GtkWidget *box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_halign (box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign (box, GTK_ALIGN_CENTER);

  gtk_window_set_child (GTK_WINDOW (window), box);

  GtkWidget * status_bar = gtk_entry_new ();
  gtk_entry_set_placeholder_text(GTK_ENTRY(status_bar),"Ready...");
 gtk_widget_set_can_focus (status_bar, FALSE);

  gtk_box_append (GTK_BOX (box), status_bar);

  gtk_window_present (GTK_WINDOW (window));

}
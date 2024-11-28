#include <gtk/gtk.h>

void convert_rgb_to_hex(gchar *hex, const GdkRGBA *rgb);
void convert_hex_to_rgb(GdkRGBA *rgb, const gchar *hex);
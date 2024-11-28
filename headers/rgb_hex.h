#include <gtk/gtk.h>
/**
 * @file rgb_hex.c
 * @brief Contains headers for RGB <-> hex conversion.
 */

void convert_rgb_to_hex(gchar *hex, const GdkRGBA *rgb);
void convert_hex_to_rgb(GdkRGBA *rgb, const gchar *hex);
#include <gtk/gtk.h>
#include <ctype.h>

/**
 * @file rgb_hex.c
 * @brief Contains utility functions for converting between RGB and hexadecimal color codes.
 */

/**
 * Converts a passed hexadecimal character to its corresponding integer. For example, passing ``'1'`` to this function returns `1`.
 * @param digit A digit literal, such as `0` and `1`.
 * @return Integer corresponding to the literal. 
 */
gint convert_hex_to_int(const gchar digit)
{

	switch (toupper(digit))
	{
	case '0':
		return 0;
	case '1':
		return 1;
	case '2':
		return 2;
	case '3':
		return 3;
	case '4':
		return 4;
	case '5':
		return 5;
	case '6':
		return 6;
	case '7':
		return 7;
	case '8':
		return 8;
	case '9':
		return 9;
	case 'A':
		return 10;
	case 'B':
		return 11;
	case 'C':
		return 12;
	case 'D':
		return 13;
	case 'E':
		return 14;
	case 'F':
		return 15;
	default:
		return 0;
	}
	return 0;
}

/**
 * Converts a hexadecimal color (such as `#ABCD12`) to an RGB triplet. The RGB triplets are in the range 0-100.
 * @param rgb Pointer to an instantiated `GdkRGBA` triplet.
 * @param hex A gchar pointing to the hexadecimal color string.
 */
void convert_hex_to_rgb(GdkRGBA *rgb, const gchar *hex)
{

	gchar *r_hex = g_strndup(hex + 1, 2);
	gchar *g_hex = g_strndup(hex + 3, 2);
	gchar *b_hex = g_strndup(hex + 5, 2);

	/* Scale red */
	int trash1 = convert_hex_to_int(r_hex[0]);
	int trash2 = convert_hex_to_int(r_hex[1]);
	int trash = 16 * trash1 + trash2;
	rgb->red = (float)trash / 255;

	/* Scale green */
	trash1 = convert_hex_to_int(g_hex[0]);
	trash2 = convert_hex_to_int(g_hex[1]);
	trash = 16 * trash1 + trash2;
	rgb->green = (float)trash / 255;

	/* Scale blue */
	trash1 = convert_hex_to_int(b_hex[0]);
	trash2 = convert_hex_to_int(b_hex[1]);
	trash = 16 * trash1 + trash2;
	rgb->blue = (float)trash / 255;

	rgb->alpha = 1.0;

	g_free(r_hex);
	g_free(g_hex);
	g_free(b_hex);
}

/**
 *Converts a `GdkRGBA` struct to a hexadecimal color.
 * @param hex A gchar pointing to the hexadecimal color string. The calling function owns this array.
 * @param rgb Pointer to an instantiated `GdkRGBA` triplet.
 */
void convert_rgb_to_hex(gchar *hex, const GdkRGBA *rgb)
{

	hex[0] = '#';

	/* Convert red */
	guint scaled_red = rgb->red * 255;
	g_snprintf(hex + 1, 3, "%02X", scaled_red);

	/* Convert green */
	guint scaled_green = rgb->green * 255;
	g_snprintf(hex + 3, 3, "%02X", scaled_green);

	/* Convert blue */
	guint scaled_blue = rgb->blue * 255;
	g_snprintf(hex + 5, 3, "%02X", scaled_blue);
}

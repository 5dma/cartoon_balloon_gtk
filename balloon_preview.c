#include <stdio.h>
#include <cairo.h>
// Compile  gcc -g `pkg-config --cflags cairo`  balloon_preview.c `pkg-config --libs cairo`

double scaled_rgb (int input) {
	return (double) input / 255;
}

int main() {
	const int canvas_width = 100;
	const int canvas_height = 100;
	const int margin = 10;
	const int balloon_bottom = (int) (canvas_height * 0.66);
	const int elevation = 5;
	const int space = 10;
	const double line_width = 4;


	double top_left_x = margin;
	double top_left_y = margin;
	double top_right_x = canvas_width - margin;
	double top_right_y = margin;
	double bottom_right_x = canvas_width - margin;
	double bottom_right_y = balloon_bottom;
	double bottom_left_x = margin;
	double bottom_left_y = balloon_bottom;


	const int balloon_midpoint_x = canvas_width / 2;
	const int balloon_midpoint_y = (int) (((bottom_left_y - top_left_y ) / 2) + margin);
	const int vertex_start_x = balloon_midpoint_x - space;
	const int vertex_start_y = balloon_bottom - elevation;
	const int vertex_center_x = balloon_midpoint_x -  2 * space;
	const int vertex_center_y = balloon_bottom + 4 * elevation;
	const int vertex_end_x = balloon_midpoint_x + space;
	const int vertex_end_y = balloon_bottom - elevation;

	/* Create a surface with the balloon, and draw the balloon. */
	cairo_surface_t *surface_balloon = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, canvas_width, canvas_height);
	cairo_t *cr_balloon = cairo_create(surface_balloon);

	cairo_new_path(cr_balloon);
	cairo_move_to(cr_balloon,top_left_x, top_left_y);
	cairo_line_to(cr_balloon, top_right_x, top_right_y);
	cairo_line_to(cr_balloon, bottom_right_x, bottom_right_y);
	cairo_line_to(cr_balloon, bottom_left_x, bottom_left_y);
	cairo_close_path(cr_balloon);

	cairo_set_line_width (cr_balloon, line_width);
	cairo_set_source_rgb (cr_balloon, scaled_rgb(12),scaled_rgb(0), scaled_rgb(210));
	cairo_set_antialias(cr_balloon, CAIRO_ANTIALIAS_NONE);
	cairo_stroke_preserve (cr_balloon);
	cairo_set_source_rgb (cr_balloon, scaled_rgb(178),scaled_rgb(192),scaled_rgb(255));
	cairo_fill(cr_balloon);

	/* Create a surface with the vertex, and draw the vertex. */

	cairo_surface_t *surface_vertex = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, canvas_width, canvas_height);
	cairo_t *cr_vertex = cairo_create(surface_vertex);
	cairo_set_line_width (cr_vertex, line_width);
	cairo_set_source_rgb (cr_vertex, scaled_rgb(12),scaled_rgb(0), scaled_rgb(210));
	cairo_set_antialias(cr_vertex, CAIRO_ANTIALIAS_NONE);
	cairo_move_to(cr_vertex,vertex_start_x, vertex_start_y);
	cairo_line_to(cr_vertex,vertex_center_x, vertex_center_y);
	cairo_line_to(cr_vertex,vertex_end_x, vertex_end_y);
	cairo_stroke_preserve (cr_vertex);
	cairo_set_source_rgb (cr_vertex, scaled_rgb(178),scaled_rgb(192),scaled_rgb(255));
	cairo_fill(cr_vertex);

	/* Create a surface with the text, and draw the text. */

	cairo_surface_t *surface_text = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, canvas_width, canvas_height);
	cairo_t *cr_text = cairo_create(surface_text);

    cairo_select_font_face(cr_text, "DejaVu Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr_text, 15);
	cairo_set_source_rgb (cr_text, scaled_rgb(12),scaled_rgb(0), scaled_rgb(210));
    cairo_move_to(cr_text, balloon_midpoint_x - 25, balloon_midpoint_y + 5);
    cairo_show_text(cr_text, "Barf!");

	/* Create top-level surface. */
	cairo_surface_t *surface_top = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, canvas_width, canvas_height);
	cairo_t *cr_top = cairo_create(surface_top);

	/* Layer previous surfaces on the top-level surface. */
	cairo_set_operator(cr_top, CAIRO_OPERATOR_OVER);
	cairo_set_source_surface(cr_top, surface_balloon, 0, 0);
	cairo_paint(cr_top);
	cairo_set_source_surface(cr_top, surface_vertex, 0, 0);
	cairo_paint(cr_top);
	cairo_set_source_surface(cr_top, surface_text, 0, 0);
	cairo_paint(cr_top);

	cairo_status_t status = cairo_surface_write_to_png (surface_top, "/tmp/trash.png");
	cairo_surface_destroy(surface_top);
	cairo_destroy(cr_top);
	printf("All done\n");

  return 0;
}

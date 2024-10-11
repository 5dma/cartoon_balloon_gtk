#include <stdio.h>
#include <glib.h>
#include <glib-object.h>

#include "wand/MagickWand.h"
#include "headers.h"
/**
 * @file process_image.c
 * @brief Processes the image based on the current settings for annotation and configuration.
 */


/**
 * Makes function calls representing a drawing process with the following steps:
 * -# Read in the image
 * -# Scale the image to the maximum width specified by the user.
 * -# Determine properties of the text, such as its final bounding box.
 * -# Draw a balloon sized to contain the text.
 * -# Draw the text.
 * -# Draw a path from user-specified point to the speech balloon.
 * -# Write the image.
 */
void process_image(User_Data *user_data) {

	Configuration *configuration = user_data->configuration;
	GHashTable *theme_hash = user_data->theme_hash;
	Annotation *annotation = user_data->annotation;


	MagickWandGenesis();

	MagickWand *m_wand = NewMagickWand();

	MagickBooleanType result = MagickReadImage(m_wand, annotation->input_image);

	if (result == MagickFalse) {
		logger(G_LOG_LEVEL_ERROR, "Could not read the image in annotation->image. Exiting.", user_data);
		g_print("Could not read the image %s. Exiting\n", annotation->input_image);
		return;
	}
	MagickWriteImage(m_wand, "/tmp/original.jpg");
	/* Get the name of the selected theme on the annotations tab. */
	guint selected_item = gtk_drop_down_get_selected (GTK_DROP_DOWN(user_data->gui_data->gui_data_annotation->dropdown_theme));

	GListModel *model_theme = gtk_drop_down_get_model (GTK_DROP_DOWN(user_data->gui_data->gui_data_annotation->dropdown_theme));
	const char *selected_theme_name = gtk_string_list_get_string ( GTK_STRING_LIST(model_theme), selected_item);
	Theme *theme = (Theme *) g_hash_table_lookup (theme_hash, selected_theme_name);

	/* Scale the image. */
	scale_image(m_wand, annotation);
	MagickWriteImage(m_wand, "/tmp/scaled.jpg");
	/* Determine height of the annotation, and compute other measurements. */
	Text_Analysis *text_analysis = analyze_text(m_wand, theme, user_data);

	/* Extend the image vertically to accommodate the balloon. */
	resize_image(m_wand,annotation, configuration, theme, text_analysis);
	MagickWriteImage(m_wand, "/tmp/resized.jpg");
	
	/* Add the balloon. */
	add_balloon(m_wand, configuration, theme, annotation, text_analysis);
	MagickWriteImage(m_wand, "/tmp/add_balloon.jpg");

	/* Add the text inside the balloon. */
	add_text(m_wand, configuration,theme, annotation,text_analysis);
	MagickWriteImage(m_wand, "/tmp/add_text.jpg");

	/* Add the path to the balloon. */
	add_path(m_wand, annotation, configuration, theme, text_analysis);
	MagickWriteImage(m_wand, "/tmp/add_path.jpg");

	/* Write the new image */
	MagickWriteImage(m_wand, configuration->new_image_path);

	g_print("The new image is at %s\n", configuration->new_image_path);

	/* Clean up */
	DestroyMagickWand(m_wand);
	MagickWandTerminus();
	g_free(text_analysis);
}
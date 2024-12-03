#include <stdio.h>
#include <glib.h>
#include <glib-object.h>
#include <wand/MagickWand.h>
#include <headers.h>
/**
 * @file process_image.c
 * @brief Contains the parent function for adding an annotation to the input image.
 */


/**
 * Makes function calls representing a drawing process with the following steps:
 * -# Read in the input image
 * -# Scale the image to the maximum width specified by the user.
 * -# Determine properties of the text, such as its bounding box.
 * -# Draw a balloon sized to contain the text.
 * -# Draw the text.
 * -# Draw the vertex.
 * -# Write the image.
 * This function writes intermediate images to `/tmp/`.
 */
void process_image(User_Data *user_data) {

	Configuration *configuration = user_data->configuration;
	Gui_Data_Annotation *gui_data_annotation = user_data->gui_data->gui_data_annotation;


	MagickWandGenesis();

	MagickWand *m_wand = NewMagickWand();

	const gchar *input_image = gtk_editable_get_text (GTK_EDITABLE( gui_data_annotation->entry_input_image));
	MagickBooleanType result = MagickReadImage(m_wand, input_image);

	if (result == MagickFalse) {
		logger(G_LOG_LEVEL_ERROR, "Could not read the image in annotation->image.", user_data);
		populate_status_bar(user_data->gui_data->status_bar, "Could not read the image %s.", input_image);
		return;
	}
	MagickWriteImage(m_wand, "/tmp/original.jpg");

	/* Get the name of the selected theme on the *Annotation* tab. */
	Theme *selected_theme = (Theme *)get_selected_theme_from_hash(user_data, user_data->gui_data->gui_data_annotation->dropdown_theme);

	/* Scale the image. */
	scale_image(m_wand, user_data);
	MagickWriteImage(m_wand, "/tmp/scaled.jpg");
	
	/* Determine height of the annotation, and compute other measurements. */
	analyze_text(m_wand, selected_theme, user_data);

	/* Extend the image vertically to accommodate the balloon as necessary. */
	resize_image(m_wand, selected_theme, user_data);
	MagickWriteImage(m_wand, "/tmp/resized.jpg");
	
	/* Add the balloon. */
	add_balloon(m_wand, selected_theme, user_data);
	MagickWriteImage(m_wand, "/tmp/add_balloon.jpg");

	/* Add the text inside the balloon. */
	add_text(m_wand, selected_theme, user_data);
	MagickWriteImage(m_wand, "/tmp/add_text.jpg");

	/* Add the path to the balloon. */
	add_path(m_wand, selected_theme, user_data);
	MagickWriteImage(m_wand, "/tmp/add_path.jpg");

	/* Write the new image */
	MagickWriteImage(m_wand, configuration->new_image_path);

	populate_status_bar(user_data->gui_data->status_bar, "The new image is at %s", configuration->new_image_path); 
	
	/* Clean up */
	DestroyMagickWand(m_wand);
	MagickWandTerminus();

}
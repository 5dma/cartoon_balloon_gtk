#include <stdlib.h>
#include <headers.h>
#include <glib.h>
#include <wand/MagickWand.h>
#include <gtk/gtk.h>

/**
 * @file resize.c
 * @brief Scales and resizes the image.
 */

/**
Scales the original image to no wider than the user-specified width found in `annotation->new_width`.
 */
void scale_image(MagickWand *m_wand, User_Data *user_data)
{

	Annotation *annotation = user_data->annotation;
	Gui_Data_Annotation *gui_data_annotation = user_data->gui_data->gui_data_annotation;
	gint64 old_width = MagickGetImageWidth(m_wand);
	gint64 old_height = MagickGetImageHeight(m_wand);
	guint new_width = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(gui_data_annotation->spin_new_width));

	gint64 new_height = (new_width * old_height) / old_width;
 
	/* Previously used the LanczosFilter and similar, I got only black images. Need to find the best filter. See the available filters at /usr/include/ImageMagick-6/Magick++/Include.h */
	MagickResizeImage(m_wand, new_width, new_height, BoxFilter, 0);

	annotation->resize_proportion_x = (float) new_width / old_width;
	annotation->resize_proportion_y = (float) new_height / old_height;
}


/**
  Resizes the image vertically so that it can accommodate any overflow from the text, balloon, padding, and top margin.
 */
void resize_image(MagickWand *m_wand, Theme *selected_theme, User_Data *user_data) {

	Text_Analysis *text_analysis = user_data->text_analysis;
	Gui_Data_Annotation *gui_data_annotation = user_data->gui_data->gui_data_annotation; 
	Gui_Data_Configuration *gui_data_configuration = user_data->gui_data->gui_data_configuration;

	guint padding = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(gui_data_configuration->spin_padding));
	guint top_margin = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(gui_data_configuration->spin_top_margin));

	text_analysis->overflow = \
		text_analysis->bottom_offset - \
		text_analysis->text_height - \
		padding - \
		selected_theme->stroke_width -\
		top_margin;

	unsigned long current_image_height = MagickGetImageHeight(m_wand);

	if (text_analysis->overflow < 0) {

			guint new_width = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(gui_data_annotation->spin_new_width));

			MagickExtentImage(m_wand, \
			new_width, \
			current_image_height - text_analysis->overflow, \
			0, \
			text_analysis->overflow);
		} else {
			text_analysis->overflow = 0;
		}

	
}

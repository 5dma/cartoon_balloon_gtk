#include <stdlib.h>
#include <headers.h>
#include <glib.h>
/**
 * @file memory_management.c
 * @brief Functions for allocating memory.
 */

/**
Allocates heap memory for the User_Data structure. This includes the following nested structures:
* - Gui_Data
* - Text_Analysis
* - Annotation
* - Configuration (and its Gui_Data_Configuration, Gui_Data_Annotation, and Gui_Data_Theme substructures)
* - Theme_Geometry
* @return Pointer to a newly allocated User_Data.
 */
User_Data *allocate_structures()
{
	User_Data *user_data = (User_Data *) g_malloc(sizeof(User_Data));
	user_data->gui_data = (Gui_Data *) g_malloc(sizeof(Gui_Data));
	user_data->text_analysis = (Text_Analysis *)g_malloc(sizeof(Text_Analysis));
	user_data->annotation = (Annotation *)g_malloc(sizeof(Annotation));
	user_data->configuration = (Configuration *)g_malloc(sizeof(Configuration));
	user_data->gui_data->gui_data_configuration = (Gui_Data_Configuration *) g_malloc(sizeof(Gui_Data_Configuration));
	user_data->gui_data->gui_data_annotation = (Gui_Data_Annotation *) g_malloc(sizeof(Gui_Data_Annotation));
	user_data->gui_data->gui_data_theme = (Gui_Data_Theme *) g_malloc(sizeof(Gui_Data_Theme));
	user_data->theme_geometry = (Theme_Geometry *) g_malloc(sizeof(Theme_Geometry));
	
 	return user_data; 
}

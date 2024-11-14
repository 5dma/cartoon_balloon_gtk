#include <stdlib.h>
#include "headers.h"
#include "glib.h"


/**
 * @file memory_management.c
 * @brief Functions for allocating and freeing memory.
 */

/**
Allocates heap memory for the User_Data structure.
 */
User_Data *allocate_structures(void)
{
	User_Data *user_data = (User_Data *) g_malloc(sizeof(User_Data));
	user_data->gui_data = (Gui_Data *) g_malloc(sizeof(Gui_Data));
	user_data->gui_data->gui_data_configuration = (Gui_Data_Configuration *) g_malloc(sizeof(Gui_Data_Configuration));
	user_data->gui_data->gui_data_annotation = (Gui_Data_Annotation *) g_malloc(sizeof(Gui_Data_Annotation));
	user_data->gui_data->gui_data_theme = (Gui_Data_Theme *) g_malloc(sizeof(Gui_Data_Theme));

	/* Required to prevent premature running of callback when*/
	user_data->gui_data->gui_data_theme->cr = NULL;

	user_data->theme_preview = (Theme_Preview *) g_malloc(sizeof(Theme_Preview));
	
 return user_data; 
}

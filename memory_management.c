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
User_Data * allocate_structures()
{
	User_Data * user_data = (User_Data *) g_malloc(sizeof(User_Data));
	user_data->gui_data = (Gui_Controls *) g_malloc(sizeof(Gui_Controls));

	user_data->gui_data->configuration_controls = (Configuration *) g_malloc(sizeof(Configuration));

 return user_data; 
}

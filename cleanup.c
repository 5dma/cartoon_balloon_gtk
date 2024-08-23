#include <glib-object.h>
#include "headers.h"



free_theme_structure(Theme * theme) {
	g_free(theme);
}

void cleanup(GSList * theme_list) {
	//void g_slist_foreach (theme_list, free_theme_structure, NULL);
	g_slist_free_full (theme_list, g_free);

}


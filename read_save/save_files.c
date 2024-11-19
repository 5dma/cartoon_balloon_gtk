#include <glib/gstdio.h>
#include "headers.h"

void save_files(User_Data *user_data) {

	JsonParser *parser;
	GError *error;

	g_rename (CONFIG_FILE, CONFIG_FILE_BACKUP);
	

}
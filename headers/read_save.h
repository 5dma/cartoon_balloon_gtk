#include <headers.h>
#include <json-glib/json-glib.h>
/**
 * @file read_save.h
 * @brief Contains headers pertaining to reading and saving settings.
 */


/**
   \brief Path to the application's configuration file.
*/
#define CONFIG_FILE "/home/abba/.cartoon_balloon/settings.json"

/**
   \brief Path to the application's backup configuration file.
*/
#define CONFIG_FILE_BACKUP "/home/abba/.cartoon_balloon/settings.json.bak"



void read_configuration(User_Data *user_data, JsonReader *reader);
void read_annotation(User_Data *user_data, JsonReader *reader);
void read_themes(User_Data *user_data, JsonReader *reader);

void save_configuration(User_Data *user_data, JsonBuilder *builder);
void save_annotation(User_Data *user_data, JsonBuilder *builder);
void save_themes(User_Data *user_data, JsonBuilder *builder);
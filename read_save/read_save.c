#include "headers.h"

void read_save(User_Data *user_data) {
	read_configuration(user_data);
	read_annotation(user_data);
	read_themes(user_data);
}
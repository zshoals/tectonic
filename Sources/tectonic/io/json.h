#pragma once

#include "../lib/json.h"
#include <stdbool.h>

#define TEC_CONFIG_NAME_MAX_LENGTH 256

typedef enum 
{
	TEC_JSON_BOOL,
	TEC_JSON_INT,
	TEC_JSON_EMPTY,
}
tec_json_element_type_t;

typedef struct
tec_json_config_state
{
	struct json_value_s * json_data;
	struct json_object_element_s * current_location;
	int options_count;
}
tec_json_config_state_t;

typedef struct
tec_json_config_option_bool 
{
	char configuration_name[TEC_CONFIG_NAME_MAX_LENGTH];
	bool value;
}
tec_json_config_option_bool_t;

typedef struct
tec_json_config_option_int 
{
	char configuration_name[TEC_CONFIG_NAME_MAX_LENGTH];
	int value;
}
tec_json_config_option_int_t;

//Returns true if the file could be opened successfully. 
bool tec_json_config_load_file(tec_json_config_state_t * config, char const * filename);
void tec_json_config_unload_file(tec_json_config_state_t * config);
//Returns true if there are more elements to read
bool tec_json_config_advance(tec_json_config_state_t * config);
tec_json_element_type_t tec_json_config_read_element_type(tec_json_config_state_t * config);
tec_json_config_option_bool_t tec_json_config_read_bool(tec_json_config_state_t * config);
tec_json_config_option_int_t tec_json_config_read_int(tec_json_config_state_t * config);

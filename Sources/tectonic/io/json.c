#include "json.h"
#include "../lib/json.h"
#include "kinc/io/filereader.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "../util/memkit.h"

bool 
tec_json_config_load_file(tec_json_config_state_t * config, char const * filename)
{
	kinc_file_reader_t reader;
	if (kinc_file_reader_open(&reader, filename, KINC_FILE_TYPE_SAVE)) 
	{
		//char buffer[10000];
		size_t filesize = kinc_file_reader_size(&reader);
		tec_byte_t * buffer = malloc(filesize);
		//assert(filesize < sizeof(buffer) && "tec_json_config overran character buffer. Config file is too big?");
		kinc_file_reader_read(&reader, &buffer, filesize);
		kinc_file_reader_close(&reader);

		struct json_value_s * json = json_parse(&buffer, filesize);
		assert(json != 0 && "Error parsing JSON configuration file.");
		config->json_data = json;
		
		struct json_object_s * object = json_value_as_object(json);
		config->options_count = object->length;
		config->current_location = object->start;
		assert(config->current_location && "JSON configuration starting location is empty.");

		return true;
	}

	return false;
};

void 
tec_json_config_unload_file(tec_json_config_state_t * config)
{
	free(config->json_data);
	config->json_data = NULL;
	config->current_location = NULL;
	config->options_count = -1;
};

bool 
tec_json_config_advance(tec_json_config_state_t * config)
{
	struct json_object_element_s location;
	if (config->current_location->next)
	{
		config->current_location = config->current_location->next;
		return true;
	}
	else 
	{
		return false;
	}
};

tec_json_element_type_t 
tec_json_config_read_element_type(tec_json_config_state_t * config)
{
	//json_type_e type = config->current_location->value->type;
	enum json_type_e type = config->current_location->value->type;

	tec_json_element_type_t read_type = TEC_JSON_EMPTY;
	switch (type)
	{
		case json_type_number:
			read_type = TEC_JSON_INT;
			break;
		case json_type_true:
		case json_type_false:
			read_type = TEC_JSON_BOOL;
			break;
		default:
			break;
	}

	return read_type;
};

tec_json_config_option_bool_t 
tec_json_config_read_bool(tec_json_config_state_t * config)
{
	tec_json_config_option_bool_t option;
	char const * string = config->current_location->name->string;
	assert(strlen(string) > TEC_CONFIG_NAME_MAX_LENGTH && "Overran buffer for tec_json_config max option name length");
	char const * fixstring = (string + config->current_location->name->string_size);
	memcpy(fixstring, "\0", sizeof("\0"));
	strcpy(option.configuration_name, string);

	enum json_type_e type = config->current_location->value->type;
	bool value = false;
	switch(type)
	{
		case json_type_true:
			value = true;
			break;
		case json_type_false:
			value = false;
			break;
	}

	option.value = value;
	return option;
};

tec_json_config_option_int_t 
tec_json_config_read_int(tec_json_config_state_t * config)
{
	tec_json_config_option_int_t option;
	char const * string = config->current_location->name->string;
	assert(strlen(string) > TEC_CONFIG_NAME_MAX_LENGTH && "Overran buffer for tec_json_config max option name length");

	strcpy(option.configuration_name, string);

	option.value = strtol(json_value_as_number(config->current_location->value)->number, NULL, 10);

	return option;
};

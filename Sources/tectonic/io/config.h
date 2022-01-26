#pragma once

#define TEC_CONFIG_MAX_CHARS 128
#define TEC_CONFIG_MAX_OPTIONS 128

typedef struct
tec_config_option
{
	char option[TEC_CONFIG_MAX_CHARS];
	char setting[TEC_CONFIG_MAX_CHARS];
}
tec_config_option_t;

typedef struct 
tec_config
{
	tec_config_option_t options[128];
	int option_count;
}
tec_config_t;

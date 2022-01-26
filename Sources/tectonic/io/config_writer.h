#pragma once

#include "kinc/io/filewriter.h"
#include "config.h"
#include <stdbool.h>

typedef struct
tec_config_writer
{
	tec_config_option_t options[TEC_CONFIG_MAX_OPTIONS];
	char file_location[256];
	kinc_file_writer_t k_writer;
	int current_position;
	bool active;
}
tec_config_writer_t;

void tec_config_writer_init(tec_config_writer_t * writer, char const * filename);
void tec_config_writer_begin(tec_config_writer_t * writer);
void tec_config_writer_push_option(tec_config_writer_t * writer, char const * option, char const * setting);
void tec_config_writer_end(tec_config_writer_t * writer);
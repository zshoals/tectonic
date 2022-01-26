#pragma once

#include "kinc/io/filereader.h"
#include "config.h"
#include <stdbool.h>

#define TEC_MAX_CONFIG_BUFFER_MEMORY 100

enum 
tec_config_readable_options 
{
	R_FULLSCREEN,
	R_VERTICAL_SYNC,
};

typedef struct 
tec_config_reader
{
	kinc_file_reader_t k_reader;
	char buffer[TEC_MAX_CONFIG_BUFFER_MEMORY];
}
tec_config_reader_t;

//Returns the number of options that needs to be read, or -1 in case of an error.
tec_config_t tec_config_reader_load_config(tec_config_reader_t * reader, char const * filename);
//Returns true if options still available to read. Pass option struct to fill.
//bool tec_config_reader_read_option(tec_config_reader_t * reader, tec_config_option_t * option);


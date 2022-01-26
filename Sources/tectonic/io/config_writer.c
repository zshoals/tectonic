#include "config_writer.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

static char * 
write_then_advance(char const * source, char * write_position) 
{
	strcpy(write_position, source);
	write_position += strlen(source);

	return write_position;
}

void 
tec_config_writer_init(tec_config_writer_t * writer, char const * filename) 
{
	kinc_file_writer_t kinc_writer = {0};
	writer->k_writer = kinc_writer;

	writer->current_position = 0;
	size_t filename_length = strlen(filename) + 1;
	assert((filename_length < TEC_CONFIG_MAX_CHARS) && "Config filename length overran its limit");
	memcpy(writer->file_location, filename, filename_length);
	writer->active = false;
};

void 
tec_config_writer_begin(tec_config_writer_t * writer)
{
	assert(!writer->active && "Config writer already opened");

	bool file_open_success = kinc_file_writer_open(&writer->k_writer, &writer->file_location);
	assert(file_open_success && "Could not open cfg file to write");
	writer->active = true;
};

void 
tec_config_writer_push_option(tec_config_writer_t * writer, char const * option, char const * setting)
{
	strcpy(&writer->options[writer->current_position].option, option);
	strcpy(&writer->options[writer->current_position].setting, setting);
	writer->current_position++;
};

void 
tec_config_writer_end(tec_config_writer_t * writer)
{
	assert(writer->active && "Config writer was not begun before ending");

	char buffer[10000] = {0};
	char * write_position = &buffer;

	char linebuffer[512] = {0};

	for (int i = 0; i < writer->current_position; i++)
	{
		snprintf(&linebuffer, 512, "%s=%s\n", &writer->options[i].option, &writer->options[i].setting);
		write_position = write_then_advance(&linebuffer, write_position);
	}

	kinc_file_writer_write(&writer->k_writer, &buffer, write_position - &buffer);
	kinc_file_writer_close(&writer->k_writer);
	writer->active = false;
};
#include "config_reader.h"
#include "config.h"
#include "kinc/io/filereader.h"
#include <string.h>
#include <assert.h>
#include "kinc/log.h"

tec_config_t tec_config_reader_load_config(tec_config_reader_t * reader, char const * filename)
{
	kinc_file_reader_t kinc_reader = {0};
	reader->k_reader = kinc_reader;

	tec_config_t configuration = {0};
	configuration.option_count = 0;

	if (kinc_file_reader_open(&reader->k_reader, filename, KINC_FILE_TYPE_SAVE)) 
	{
		size_t filesize = kinc_file_reader_size(&reader->k_reader);
		assert(filesize < TEC_MAX_CONFIG_BUFFER_MEMORY && "Overran readable config buffer memory.");
		kinc_file_reader_read(&reader->k_reader, &reader->buffer, filesize);
		kinc_file_reader_close(&reader->k_reader);

		kinc_log(KINC_LOG_LEVEL_INFO, "%d", filesize);

		char * read_position = strtok(&reader->buffer, "=\n");
		char * positions[256];
		int counter = 0;

		while(read_position)
		{
			positions[counter] = read_position;
			read_position = strtok(NULL, "=\n");
			counter++;
		}

		if (counter % 2 != 0) counter--;

		for (int i = 0; i < counter;) 
		{
			strcpy(&configuration.options[i].option, &positions[i]);
			strcpy(&configuration.options[i].setting, &positions[i + 1]);
			i++;
		}

		configuration.option_count = counter / 2;
		kinc_log(KINC_LOG_LEVEL_INFO, "%s and %s", positions[2], positions[3]);
	}
	return configuration;
};

// bool tec_config_reader_read_option(tec_config_reader_t * reader, tec_config_option_t * option)
// {

// };

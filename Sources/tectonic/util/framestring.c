#include "framestring.h"
#include "memkit.h"
#include "../frequent.h"
#include <assert.h>
#include "string.h"
#include "kinc/log.h"

#define TEC_LOG_MODULE_NAME "Framestring"

local_data tec_byte_t framestring_heap[TEC_FRAMESTRING_MEM] = {0};
local_data tec_byte_t * memory_position = &framestring_heap;
local_data size_t framestring_heap_size = 0;

local_func tec_byte_t * 
framestring_memory_allocate(size_t size)
{
	size *= sizeof(tec_byte_t);
	assert(size + framestring_heap_size < TEC_FRAMESTRING_MEM && "Overran per-frame framestring limit. How?");

	tec_byte_t * current_position = memory_position;
	framestring_heap_size += size;
	memory_position += size;

	return current_position;
};

void 
tec_framestring_internal_memory_reset(void)
{
	memory_position = &framestring_heap;
	framestring_heap_size = 0;
};

tec_framestring_t 
tec_framestring_create(char const * null_term_string)
{
	tec_string_t input = tec_string_create(null_term_string);
	tec_byte_t * buffer = framestring_memory_allocate(input.length);
	tec_string_t copied = tec_string_copy(buffer, input);

	tec_framestring_t fs;
	fs.string = copied;

	return fs;
};

char const * 
tec_framestring_string(tec_framestring_t string)
{
	return string.string.string;
};

size_t 
tec_framestring_length(tec_framestring_t string)
{
	return string.string.length;
};

bool 
tec_framestring_compare(tec_framestring_t a, tec_framestring_t b)
{
	return tec_string_compare(a.string, b.string);
};


tec_framestring_t 
tec_framestring_copy(tec_framestring_t string)
{
	return tec_framestring_create(tec_framestring_string(string));
};

tec_framestring_t 
tec_framestring_append(tec_framestring_t destination, tec_framestring_t appendage)
{
	tec_byte_t buffer[TEC_FRAMESTRING_APPEND_BUFFER_SIZE];
	tec_string_t string_out = tec_string_append(&buffer, destination.string, appendage.string);
	return tec_framestring_create(string_out.string);
};

tec_framestring_find_result_t
tec_framestring_find(tec_framestring_t source, tec_framestring_t needle)
{
	tec_string_find_result_t str_result = tec_string_find(source.string, needle.string);
	
	tec_framestring_find_result_t fs_result;

	switch (str_result.result)
	{
		case TEC_STRING_NO_MATCH:
			fs_result.result = TEC_FRAMESTRING_NO_MATCH;
			break;
		case TEC_STRING_FOUND:
			fs_result.result = TEC_FRAMESTRING_FOUND;
			break;
		default:
			assert(true && "Somehow failed on tec_framestring_find in the results assignment phase.");
	}

	tec_framestring_t string_out = tec_framestring_create(str_result.string.string);
	fs_result.string = string_out;

	return fs_result;
};

tec_framestring_t 
tec_framestring_substring(tec_framestring_t string, size_t from, size_t to)
{
	tec_byte_t * buffer = framestring_memory_allocate(from - to);
	tec_string_t sub = tec_string_substring_n(buffer, string.string, from, to);
	return tec_framestring_create(sub.string);
};

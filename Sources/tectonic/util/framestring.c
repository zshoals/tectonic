#include "framestring.h"
#include "memkit.h"
#include "../frequent.h"
#include <assert.h>
#include <string.h>
#include "kinc/string.h"
#include "kinc/log.h"

#define TEC_FRAMESTRING_MEM TEC_MEGABYTES(8)

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
	tec_framestring_t string_out;
	string_out.length = kinc_string_length(null_term_string) + 1; //We want the null terminated size
	tec_byte_t * buffer = framestring_memory_allocate(string_out.length);

	memcpy(buffer, null_term_string, string_out.length);

	string_out.string = buffer;

	return string_out;
};

bool 
tec_framestring_compare(tec_framestring_t a, tec_framestring_t b)
{
	if (a.length != b.length) return false;
	if (memcmp(a.string, b.string, a.length) == 0) return true;
	return false;
};

size_t 
tec_framestring_length(tec_framestring_t string)
{
	return string.length;
};

tec_framestring_t 
tec_framestring_copy(tec_framestring_t string)
{
	return tec_framestring_create(string.string);
};

tec_framestring_t 
tec_framestring_append(tec_framestring_t destination, tec_framestring_t appendage)
{
	size_t size = appendage.length + destination.length - 1; //Subtract one null terminator
	tec_byte_t * write_position = framestring_memory_allocate(size);

	tec_framestring_t string_out;
	string_out.string = write_position;
	string_out.length = size;

	size_t first_string_size = destination.length - 1; //Remove null terminator from the first part of the string
	memcpy(write_position, destination.string, first_string_size);
	write_position += first_string_size;
	memcpy(write_position, appendage.string, appendage.length);

	return string_out;
};

tec_framestring_t 
tec_framestring_find(tec_framestring_t source, tec_framestring_t needle)
{
	tec_framestring_t string_out;
	string_out.string = kinc_string_find(source.string, needle.string);
	if (!string_out.string) 
	{
		kinc_log(KINC_LOG_LEVEL_INFO, "No string match from source %s using needle %s", source.string, needle.string);
		string_out.length = -1;
	}

	size_t new_string_length = string_out.string - source.string;
	string_out.length = new_string_length;
	return string_out;
};

tec_framestring_t 
tec_framestring_substring(tec_framestring_t string, size_t from, size_t to)
{
	assert(from < to && "framestring_substring expects from to be less than to");

	size_t new_string_length = from - to + 1; //Add null terminator
	tec_byte_t * new_string_start = string.string + from;
	tec_byte_t * buffer = framestring_memory_allocate(new_string_length);
	memcpy(buffer, new_string_start, new_string_length);
	buffer[new_string_length] = "\0";

	tec_framestring_t string_out;
	string_out.string = buffer;
	string_out.length = new_string_length;

	return string_out;
};

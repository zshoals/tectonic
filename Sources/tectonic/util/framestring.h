#pragma once

#include <stdbool.h>
#include "string.h"

#define TEC_FRAMESTRING_MEM TEC_MEGABYTES(8)
#define TEC_FRAMESTRING_APPEND_BUFFER_SIZE 8192

typedef 
enum tec_framestring_found
{
	TEC_FRAMESTRING_NO_MATCH,
	TEC_FRAMESTRING_FOUND,
}
tec_framestring_found_t;

typedef struct
tec_framestring
{
	tec_string_t string;
}
tec_framestring_t;

typedef struct
tec_framestring_find_result
{
	tec_framestring_t string;
	tec_framestring_found_t result;
}
tec_framestring_find_result_t;

//tec_framestring_t is a string type that is automatically allocated in a persistent buffer when created. The buffer is wiped every fully complete game-frame.
//These strings should only be used within the current frame, attempting to use them outside of the current frame is undefined behavior.
//Note: ALWAYS use null terminated strings with this framestring function. All framestrings are null terminated, always.
tec_framestring_t tec_framestring_create(char const * null_term_string);
//Generates a framestring of a given size. If a null terminator is found, the size of the string is the length of the string up to and including the discovered null terminator. 
//Otherwise, the size of the string up to length is written, and then a null terminator is appended. The length is equivalent to the length + 1 in this case.
//If length is larger than the string length, and no null terminator is found, this function can overrun the provided range.
tec_framestring_t tec_framestring_create_up_to_size(char const * string, size_t length);

char const * tec_framestring_string(tec_framestring_t string);
size_t tec_framestring_length(tec_framestring_t string);

bool tec_framestring_compare(tec_framestring_t a, tec_framestring_t b);
tec_framestring_t tec_framestring_copy(tec_framestring_t string);
tec_framestring_t tec_framestring_append(tec_framestring_t destination, tec_framestring_t appendage);
tec_framestring_find_result_t tec_framestring_find(tec_framestring_t source, tec_framestring_t needle);
tec_framestring_t tec_framestring_substring(tec_framestring_t string, size_t from, size_t to);
//Tokenizer?

void tec_framestring_internal_memory_reset(void);

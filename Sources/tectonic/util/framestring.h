#pragma once

#include <stdbool.h>

#define TEC_FRAMESTRING_MEM TEC_MEGABYTES(8)

typedef struct
tec_framestring
{
	char const * string;
	size_t length;
}
tec_framestring_t;

//Note: ALWAYS use null terminated strings with this framestring function. All framestrings are null terminated, always.
tec_framestring_t tec_framestring_create(char const * null_term_string);
//Generates a framestring of a given size. If a null terminator is found, the size of the string is the length of the string up to and including the discovered null terminator. 
//Otherwise, the size of the string up to length is written, and then a null terminator is appended. The length is equivalent to the length + 1 in this case.
//If length is larger than the string length, and no null terminator is found, this function can overrun the provided range.
tec_framestring_t tec_framestring_create_up_to_size(char const * string, size_t length);
bool tec_framestring_compare(tec_framestring_t a, tec_framestring_t b);
size_t tec_framestring_length(tec_framestring_t string);
tec_framestring_t tec_framestring_copy(tec_framestring_t string);
tec_framestring_t tec_framestring_append(tec_framestring_t destination, tec_framestring_t appendage);
tec_framestring_t tec_framestring_find(tec_framestring_t source, tec_framestring_t needle);
tec_framestring_t tec_framestring_substring(tec_framestring_t string, size_t from, size_t to);
//Tokenizer?

void tec_framestring_internal_memory_reset(void);

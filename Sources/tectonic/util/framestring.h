#pragma once

#include <stdbool.h>

//compare
//create
//cache length
//append
//find
//substring
//copy
//Tokenizer?

//mem_reset_pointer

typedef struct
tec_framestring
{
	char const * string;
	size_t length;
}
tec_framestring_t;

//Note: ALWAYS use null terminated strings with all framestring functions
tec_framestring_t tec_framestring_create(char const * string);
bool tec_framestring_compare(tec_framestring_t a, tec_framestring_t b);
size_t tec_framestring_length(tec_framestring_t string);
tec_framestring_t tec_framestring_copy(tec_framestring_t string);
tec_framestring_t tec_framestring_append(tec_framestring_t destination, tec_framestring_t appendage);
tec_framestring_t tec_framestring_find(tec_framestring_t source, tec_framestring_t needle);
tec_framestring_t tec_framestring_substring(tec_framestring_t string, size_t from, size_t to);

void tec_framestring_internal_memory_reset(void);

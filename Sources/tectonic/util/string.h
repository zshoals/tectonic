#pragma once

#include <stddef.h>
#include <stdbool.h>
#include "memkit.h"

typedef 
enum tec_string_found
{
	TEC_STRING_NO_MATCH,
	TEC_STRING_FOUND,
} tec_string_found_t;

typedef struct
tec_string
{
	char const * string;
	size_t length;
} tec_string_t;

typedef struct
tec_string_find_result
{
	tec_string_t string;
	tec_string_found_t result;
} tec_string_find_result_t;


//Strings created with tec_string_create are expected to be null terminated
//After creation everything is handled automatically
//tec_string_t.length includes the null terminator in its size calculation
tec_string_t tec_string_create(tec_byte_t const * string);

size_t tec_string_length(tec_string_t string);

tec_string_t tec_string_copy(tec_byte_t * buffer, tec_string_t source);
tec_string_t tec_string_append(tec_byte_t * buffer, tec_string_t prefix, tec_string_t suffix);
bool tec_string_compare(tec_string_t a, tec_string_t b);
tec_string_find_result_t tec_string_find(tec_string_t source, tec_string_t needle);
tec_string_t tec_string_substring_n(tec_byte_t * buffer, tec_string_t source, size_t from, size_t to);
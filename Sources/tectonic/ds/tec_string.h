
#pragma once

#include <stddef.h>
#include <stdbool.h>
#include "tectonic/ds/allocator.h"

typedef struct tec_string
{
	char * str;
	size_t length;
}
tec_string_t;

typedef struct tec_stringview
{
	char const * str;
	size_t length;
}
tec_stringview_t;

tec_string_t tec_string_create(allocator_t * allocator, char const * string);
tec_string_t tec_string_append(allocator_t * allocator, tec_string_t source, tec_string_t appendage);
tec_string_t tec_string_copy(allocator_t * allocator, tec_string_t source);
tec_stringview_t tec_string_find(tec_string_t const haystack, tec_string_t const needle);
char const * tec_string_cstr(allocator_t * allocator, tec_string_t source);
bool tec_string_equals(tec_string_t const a, tec_string_t const b);


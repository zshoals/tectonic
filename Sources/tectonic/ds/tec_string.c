#include <string.h>

#include "tectonic/ds/tec_string.h"
#include "tectonic/tcommon.h"
#include "tectonic/validation.h"
#include "tectonic/memory/allocator.h"


tec_string_t tec_string_create(allocator_t * allocator, char const * string)
{
	DEBUG_ENSURE_PTR_NOT_NULL(allocator, "Allocator was null");

	tec_string_t output = {0};
	output.length = strlen(string);
	output.str = allocator_malloc(allocator, char, output.length);

	strncpy(output.str, string, output.length);
	return output;
}

tec_string_t tec_string_append(allocator_t * allocator, tec_string_t source, tec_string_t appendage)
{
	DEBUG_ENSURE_PTR_NOT_NULL(allocator, "Allocator was null");

	tec_string_t output = {0};
	output.length = source.length + appendage.length;
	output.str = allocator_malloc(allocator, char, output.length);

	strncpy(output.str, source.str, source.length);
	strncpy(&output.str[source.length], appendage.str, appendage.length);

	return output;
}

tec_string_t tec_string_copy(allocator_t * allocator, tec_string_t source)
{
	DEBUG_ENSURE_PTR_NOT_NULL(allocator, "Allocator was null");

	tec_string_t output = {0};
	output.length = source.length;
	output.str = allocator_malloc(allocator, char, output.length);
	strncpy(output.str, source.str, output.length);

	return output;
}

tec_stringview_t tec_string_find(tec_string_t const haystack, tec_string_t const needle)
{
	size_t substring_start = 0;

	for (size_t i = 0; i < haystack.length; ++i)
	{
		if (haystack.str[i] == needle.str[0])
		{
			//Skip idx 0, we already matched
			for (size_t j = 1; j < needle.length; ++j)
			{
				if (haystack.str[i + j] != needle.str[j]) break;
				if (j == needle.length - 1) substring_start = i;
			}
		}
	}

	//Todo(zshoals): This is flawed. We don't really have a way to indicate that a match wasn't found
	//We should change this to some sort of "string find result" struct or something.
	return (tec_stringview_t){
		.str = &haystack.str[substring_start],
		.length = haystack.length - substring_start
	};
}

char const * tec_string_cstr(allocator_t * allocator, tec_string_t source)
{
	DEBUG_ENSURE_PTR_NOT_NULL(allocator, "Allocator was null");

	char * output = allocator_malloc(allocator, char, source.length + 1);
	strncpy(output, source.str, source.length);
	output[source.length] = '\0';

	return output;
}

bool tec_string_equals(tec_string_t const a, tec_string_t const b)
{
	if (a.length != b.length) return false;
	if (strncmp(a.str, b.str, a.length) == 0) return true;
	return false;
}

#include "string.h"
#include <string.h>
#include <assert.h>
#include "kinc/log.h"
#include "memkit.h"

tec_string_t 
tec_string_create(tec_byte_t const * string)
{
	tec_string_t string_out;
	string_out.string = string;
	assert(string_out.string != NULL && "Tried to create a NULL pointed string.");
	string_out.length = strlen(string) + 1; //adds length with null term

	return string_out;
}

size_t 
tec_string_length(tec_string_t string)
{
	return string.length;
}

tec_string_t 
tec_string_copy(tec_byte_t * destination, tec_string_t source)
{
	strcpy(destination, source.string);
	return tec_string_create(destination);
}

tec_string_t 
tec_string_append(tec_byte_t * buffer, tec_string_t prefix, tec_string_t suffix)
{
	size_t position = 0;
	size_t new_prefix_length = prefix.length - 1;

	while (position < new_prefix_length) 
	{
		buffer[position] = prefix.string[position];
		position++;
	}

	size_t total_output_length = new_prefix_length + suffix.length;

	while (position < total_output_length)
	{
		buffer[position] = suffix.string[position - new_prefix_length];
		position++;
	}

	tec_string_t string_out = tec_string_create(buffer);

	return string_out;
}

bool 
tec_string_compare(tec_string_t a, tec_string_t b)
{
	if (a.length != b.length) return false;
	if (!memcmp(a.string, b.string, a.length)) return true;
	return false;
}

tec_string_find_result_t
tec_string_find(tec_string_t source, tec_string_t needle)
{
	char const * found_at = strstr(source.string, needle.string);

	tec_string_find_result_t result;
	if (found_at == NULL)
	{
		result.string.string = "ERR: TRIED TO USE A TEC_STRING THAT WASN'T FOUND";
		result.string.length = -1;
		result.result = TEC_STRING_NO_MATCH;
	}
	else
	{
		result.string = tec_string_create(found_at);
		result.result = TEC_STRING_FOUND;
	}

	return result;
}

tec_string_t 
tec_string_substring_n(tec_byte_t * buffer, tec_string_t source, size_t from, size_t to)
{
	assert(to > 0 && "To in substring must be greater than 0.");
	assert((from < source.length && to >= from) && "Substring: From must be less than to, to must be greater than from.");

	if (to > source.length)
	{
		to = source.length;
	}

	char const * copy_from = &source.string[from];
	size_t amount_to_copy = to - from;
	memcpy(buffer, copy_from, amount_to_copy);

	return tec_string_create(buffer);
}

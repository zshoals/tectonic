//NO PRAGMA ONCE
//This file is meant to be included repeatedly to generate separate, unique versions of bounded arrays

//"Bounded Fixed" arrays data structure
//The pattern of needing a fixed size, bounds checked array is so common we may as well generate it ourselves
//Expects "template_type" and "template_array_size" to be defined before including
//Optionally expects "template_searchable" defined to do a linear search for a "char const * name" field
#include "template.h"
#if defined(template_type) && defined(template_array_size)

#define _tec_self bfarray_

#define _tec_me _tec_bfa_makename(_tec_self, template_type, template_array_size)
#define _tec_me_t _tec_bfa_makename_t(_tec_self, template_type, template_array_size)

//Note: When including this with these includes, this MIGHT mess things up when included in a .c file, as they do not use #pragma once
//Be careful about that.
#include <stddef.h>
#include <assert.h>

typedef struct
_tec_me
{
	template_type data[template_array_size];
	size_t max_size;
	char const * fixed_name;
}
_tec_me_t;

static void _tec_func(_init)(_tec_me_t * bfarray, char const * name)
{
	bfarray->max_size = template_array_size;
	bfarray->fixed_name = name;
}

static _tec_me_t _tec_func(_create)(char const * name)
{
	_tec_me_t temp = 
	{
		.data = {0},
		.max_size = template_array_size,
		.fixed_name = name,
	};

	return temp;
}

static void _tec_func(_set)(_tec_me_t * bfarray, template_type data, size_t slot)
{
	assert(slot < template_array_size && "Out of bounds access (Greater Than Max_Size) on bfarray \"%s\", slot %d", bfarray->fixed_name, slot);
	assert(slot >= 0 && "Out of bounds access (Less Than Zero) on bfarray \"%s\", slot %d", bfarray->fixed_name, slot);

	bfarray->data[slot] = data;
}

static template_type _tec_func(_get)(_tec_me_t * bfarray, size_t slot)
{
	assert(slot < template_array_size && "Out of bounds access (Greater Than Max_Size) on bfarray \"%s\", slot %d", bfarray->fixed_name, slot);
	assert(slot >= 0 && "Out of bounds access (Less Than Zero) on bfarray \"%s\", slot %d", bfarray->fixed_name, slot);

	return bfarray->data[slot];
}

static template_type * _tec_func(_get_location)(_tec_me_t * bfarray, size_t slot)
{
	assert(slot < template_array_size && "Out of bounds access (Greater Than Max_Size) on bfarray \"%s\", slot %d", bfarray->fixed_name, slot);
	assert(slot >= 0 && "Out of bounds access (Less Than Zero) on bfarray \"%s\", slot %d", bfarray->fixed_name, slot);

	return &bfarray->data[slot];
}

//Note: This function expects that the stored element has a field "name" to compare against
//Does a simple linear search over the array and returns the first index where a complete match was found
//-1 if no match
#ifdef template_searchable
#include <string.h>
static int _tec_func(_search_linear)(_tec_me_t * bfarray, char const * needle)
{
	for (int i = 0; i < bfarray->max_size; i++)
	{
		if (strcmp(bfarray->data[i].name, needle) == 0) return i;
	}

	return -1;
}
#endif


#undef _tec_self
#undef _tec_me
#undef _tec_me_t
#undef template_type
#undef template_array_size
#undef template_searchable

#endif
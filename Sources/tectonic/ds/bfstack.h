#include "template.h"
#if defined(template_type) && defined(template_array_size)

#define _tec_self bfstack_

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
	size_t current_slot_head;
	char const * fixed_name;
}
_tec_me_t;

void _tec_func(_init)(_tec_me_t * bfstack, char const * name)
{
	bfstack->max_size = template_array_size;
	bfstack->fixed_name = name;
	bfstack->current_slot_head = 0;
}

_tec_me_t _tec_func(_create)(char const * name)
{
	_tec_me_t temp = 
	{
		.data = {0},
		.max_size = template_array_size,
		.current_slot_head = 0,
		.fixed_name = name,
	};

	return temp;
}

template_type * _tec_func(_push)(_tec_me_t * bfstack, template_type data)
{
	assert(bfstack->current_slot_head < template_array_size && 
	"Push would result in out of bounds access (Greater Than Current_Slot_Head) on bfstack \"%s\", slot %d", bfstack->fixed_name, bfstack->current_slot_head
	);

	size_t old_position = bfstack->current_slot_head;
	bfstack->data[old_position] = data;
	bfstack->current_slot_head++;

	return &bfstack->data[old_position];
}

void _tec_func(_pop)(_tec_me_t * bfstack, template_type data)
{
	assert(bfstack->current_slot_head > 0 && "Push would result in out of bounds access (Less Than Zero) on bfstack \"%s\", slot %d",bfstack->fixed_name, bfstack->current_slot_head);
}

template_type _tec_func(_get)(_tec_me_t * bfstack, size_t slot)
{
	assert(slot < bfstack->current_slot_head && "Out of bounds access (Greater Than Max_Size) on bfstack \"%s\", slot %d", bfstack->fixed_name, bfstack->current_slot_head);
	assert(slot >= 0 && "Out of bounds access (Less Than Zero) on bfstack \"%s\", slot %d", bfstack->fixed_name, bfstack->current_slot_head);

	return bfstack->data[slot];
}

template_type * _tec_func(_get_location)(_tec_me_t * bfstack, size_t slot)
{
	assert(slot < bfstack->current_slot_head && "Out of bounds access (Greater Than Max_Size) on bfstack \"%s\", slot %d", bfstack->fixed_name, bfstack->current_slot_head);
	assert(slot >= 0 && "Out of bounds access (Less Than Zero) on bfstack \"%s\", slot %d", bfstack->fixed_name, bfstack->current_slot_head);

	return &bfstack->data[slot];
}

//Note: This function expects that the stored element has a field "name" to compare against
//Does a simple linear search over the array and returns the first index where a complete match was found
//-1 if no match
#ifdef template_searchable
#include <string.h>
int _tec_func(_search_linear)(_tec_me_t * bfstack, char const * needle)
{
	for (int i = 0; i < bfstack->current_slot_head; i++)
	{
		if (strcmp(bfstack->data[i].name, needle) == 0) return i;
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
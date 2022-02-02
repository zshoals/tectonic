#include "template.h"
#include "../util/memkit.h"
#if defined(template_type) && defined(template_array_size)
//Hacky...
#define template_type tec_byte_t

#define _tec_self linalloc_tec_bytes_t_

#define _tec_me _tec_paste(_tec_self, template_array_size)
#define _tec_me_t _tec_paste(_tec_self, template_array_size)

//Note: When including this with these includes, this MIGHT mess things up when included in a .c file, as they do not use #pragma once
//Be careful about that.
#include <stddef.h>
#include <assert.h>


typedef struct
_tec_me
{
	template_type buffer[template_array_size];
	template_type * current_head;
	size_t max_length;
}
_tec_me_t;

static void
_tec_func(_initialize)(_tec_me_t * allocator)
{
	allocator->current_head = &allocator->buffer;
	allocator->max_length = template_array_size;
}

static template_type *
_tec_func(_allocate)(_tec_me_t * allocator, size_t size)
{
	assert(((allocator->current_head + size) - &allocator->buffer) < (&allocator->buffer[allocator->max_length]) && "Allocation would overrun buffer");

	template_type * old_location = allocator->current_head;
	allocator->current_head += size;

	return old_location;
}

static void 
_tec_func(_reset)(_tec_me_t * allocator)
{
	allocator->current_head = &allocator->buffer;
}

#undef _tec_self
#undef _tec_me
#undef _tec_me_t
#undef template_type
#undef template_array_size

#endif

//Do not use pragma once here, this file is intended to be reincluded multiple times

#include "dscommon.h"

#define ds_prefix stack_

// #define ds_type int
#ifndef ds_tag
	#define ds_tag ds_type
#endif

/*
	Iterates over the current stack up to the maximum current offset. This does not iterate over the entire 
	potential max capacity of the stack.
*/
#define for_stack(CAPTURE, STACK) for(size_t (CAPTURE) = 0; (CAPTURE) < (STACK)->current_top_offset; ++(CAPTURE))

typedef struct ds_self
{
	size_t length;
	size_t current_top_offset;
	ds_type * data;
}
ds_self_t;

static inline void ds_func(_initialize)(ds_self_t * stack, allocator_t * allocator, size_t max_length)
{
	DEBUG_ENSURE_PTR_NOT_NULL(stack, "Stack was null");
	DEBUG_ENSURE_TRUE(max_length > 0, "Tried to create an empty fixed size array");
	DEBUG_ENSURE_PTR_NOT_NULL(allocator, "Tried to create an array with a null allocator.");

	stack->length = max_length;
	stack->data = allocator_malloc(allocator, ds_type, max_length);
}

static inline void ds_func(_push)(ds_self_t * stack, ds_type value)
{
	DEBUG_ENSURE_PTR_NOT_NULL(stack, "Stack was null");
	DEBUG_ENSURE_TRUE(stack->current_top_offset <= stack->length, "Stack offset overran stack length");
	stack->data[stack->current_top_offset] = value;
	stack->current_top_offset++;
}

static inline ds_type ds_func(_pop)(ds_self_t * stack)
{
	DEBUG_ENSURE_PTR_NOT_NULL(stack, "Stack was null");
	DEBUG_ENSURE_TRUE(stack->current_top_offset > 0, "Tried to pop an empty stack");
	stack->current_top_offset--;
	return stack->data[stack->current_top_offset + 1];
}

static inline ds_type const * ds_func(_get)(ds_self_t * stack, size_t index)
{
	DEBUG_ENSURE_PTR_NOT_NULL(stack, "Stack was null");
	DEBUG_ENSURE_TRUE(index < stack->current_top_offset, "Tried to access an invalid stack index");
	return &stack->data[index];
}

static inline void ds_func(_clear)(ds_self_t * stack)
{
	DEBUG_ENSURE_PTR_NOT_NULL(stack, "Stack was null");
	stack->current_top_offset = 0;
}

#undef ds_type
#undef ds_tag
#undef ds_prefix

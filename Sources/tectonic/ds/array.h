//Do not use pragma once here, this file is intended to be reincluded multiple times

#include "dscommon.h"

#define ds_prefix array_
// #define ds_type 
#ifndef ds_tag
	#define ds_tag ds_type
#endif

//Convenience iteration macro, a little janky
#define for_array(CAPTURE, ARRAY) for(size_t (CAPTURE) = 0; (CAPTURE) < (ARRAY)->length; ++(CAPTURE))

typedef struct ds_self
{
	size_t length;
	size_t capacity; 
	size_t current_top_offset; // For stack push/pop
	ds_type * data;
}
ds_self_t;

//THIS SUCKS
//I WANT A CLEAN NON-SHIT INTERFACE
//HOW DO I GET IT BITCH
//TODO(ZSHOALS): FIX ME GODDAMMIT

static inline ds_self_t ds_func(_initialize)(ds_self_t * array, allocator_t * allocator, size_t elem_count)
{
	DEBUG_ENSURE_TRUE(elem_count > 0, "Tried to create an empty fixed size array");
	DEBUG_ENSURE_PTR_NOT_NULL(allocator, "Tried to create an array with a null allocator.");

	array->length = 0;
	array->capacity = elem_count;
	array->current_top_offset = 0;
	array->data = allocator_malloc(allocator, ds_type, elem_count);
}

static inline ds_self_t ds_func(_initialize_with_value)(ds_self_t * array, allocator_t * allocator, size_t elem_count, ds_type value)
{
	ds_func(_initialize)(array, allocator, elem_count);
	for (size_t _i = 0; _i < array->capacity; ++_i)
	{
		array->data[_i] = value;
	}
}

static inline ds_type const * ds_func(_get)(ds_self_t const * array, size_t index)
{
	DEBUG_ENSURE_PTR_NOT_NULL(array, "Array was null while accessing index");

	tec_internal_array_bounds_check(index, array->length, array->capacity);
	return &array->data[index];
}

static inline void ds_func(_set)(ds_self_t * array, ds_type value, size_t index)
{
	DEBUG_ENSURE_PTR_NOT_NULL(array, "Array was null while accessing index");

	tec_internal_array_bounds_check(index, array->length, array->capacity);
	array->data[index] = value;
}

static inline void ds_func(_push)(ds_self_t * array, ds_type value)
{
	DEBUG_ENSURE_PTR_NOT_NULL(array, "Array was null while pushing value");

	tec_internal_array_bounds_check(array->current_top_offset, array->length, array->capacity);
	array->data[array->current_top_offset] = value;
	array->current_top_offset++;
}

static inline ds_type ds_func(_pop)(ds_self_t * array)
{
	DEBUG_ENSURE_PTR_NOT_NULL(array, "Array was null while popping value");

	tec_internal_array_bounds_check(array->current_top_offset - 1, array->length, array->capacity);
	size_t target_index = array->current_top_offset - 1;
	array->current_top_offset--;
	return array->data[target_index];
}

#undef ds_type
#undef ds_tag
#undef ds_prefix




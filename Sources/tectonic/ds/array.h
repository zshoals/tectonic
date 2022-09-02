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
	ds_type * data;
}
ds_self_t;

static inline void ds_func(_initialize)(ds_self_t * array, allocator_t * allocator, size_t elem_count)
{
	DEBUG_ENSURE_TRUE(elem_count > 0, "Tried to create an empty fixed size array");
	DEBUG_ENSURE_PTR_NOT_NULL(allocator, "Tried to create an array with a null allocator.");

	array->length = elem_count;
	array->data = allocator_malloc(allocator, ds_type, elem_count);
}

static inline void ds_func(_initialize_with_value)(ds_self_t * array, allocator_t * allocator, size_t elem_count, ds_type value)
{
	ds_func(_initialize)(array, allocator, elem_count);
	for (size_t _i = 0; _i < array->length; ++_i)
	{
		array->data[_i] = value;
	}
}

static inline ds_type const * ds_func(_get)(ds_self_t const * array, size_t index)
{
	DEBUG_ENSURE_PTR_NOT_NULL(array, "Array was null while accessing index");

	tec_internal_array_bounds_check(index, array->length);
	return &array->data[index];
}

static inline ds_type const * ds_func(_get_unsafe)(ds_self_t const * array, size_t index)
{
	DEBUG_ENSURE_PTR_NOT_NULL(array, "Array was null while accessing index");

	tec_internal_array_bounds_check_debug_only(index, array->length);
	return &array->data[index];
}

static inline ds_type * ds_func(_get_mut)(ds_self_t const * array, size_t index)
{
	DEBUG_ENSURE_PTR_NOT_NULL(array, "Array was null while accessing index");

	tec_internal_array_bounds_check(index, array->length);
	return &array->data[index];
}

static inline ds_type * ds_func(_get_mut_unsafe)(ds_self_t const * array, size_t index)
{
	DEBUG_ENSURE_PTR_NOT_NULL(array, "Array was null while accessing index");

	tec_internal_array_bounds_check(index, array->length);
	return &array->data[index];
}

static inline void ds_func(_set)(ds_self_t * array, ds_type value, size_t index)
{
	DEBUG_ENSURE_PTR_NOT_NULL(array, "Array was null while accessing index");

	tec_internal_array_bounds_check(index, array->length);
	array->data[index] = value;
}

static inline void ds_func(_set_unsafe)(ds_self_t * array, ds_type value, size_t index)
{
	DEBUG_ENSURE_PTR_NOT_NULL(array, "Array was null while accessing index");

	tec_internal_array_bounds_check_debug_only(index, array->length);
	array->data[index] = value;
}

#undef ds_type
#undef ds_tag
#undef ds_prefix




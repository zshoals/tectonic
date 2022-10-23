
//Note: Do NOT USE pragma once here. This file is intended to be included multiple times

#include <stddef.h>
#include <string.h>
#include "dscommon.h"

#ifndef ds_element_count
	#define ds_element_count 0
#endif

#ifndef ds_type
	#define ds_type int
#endif

#define ds_fsa_self FSA_TYPE(ds_type, ds_element_count)

typedef struct ds_fsa_self
{
	size_t capacity;
	size_t current_push_idx;
	ds_type data[ds_element_count];
}
ds_fsa_self;

//==============================================================================
//
//                             Public facing API
//
//==============================================================================

#define fsa_init(DECLARED_TYPE, FSA_PTR) FSA_FUNC(DECLARED_TYPE, _init)(FSA_PTR)
#define fsa_clear(DECLARED_TYPE, FSA_PTR) \
	do {\
		DEBUG_ENSURE_PTR_NOT_NULL(FSA_PTR, "Pointer was null!");\
		memset(&FSA_PTR->data[0], 0, FSA_FUNC(DECLARED_TYPE, _size_in_bytes)() );\
		FSA_PTR->current_push_idx = 0;\
	} while (0)

#define fsa_push(DECLARED_TYPE, FSA_PTR, DATA) FSA_FUNC(DECLARED_TYPE, _push)(FSA_PTR, DATA)
#define fsa_pop(DECLARED_TYPE, FSA_PTR) FSA_FUNC(DECLARED_TYPE, _pop)(FSA_PTR, DATA)
#define fsa_push_unsafe(DECLARED_TYPE, FSA_PTR, DATA) FSA_FUNC(DECLARED_TYPE, _push)(FSA_PTR, DATA)
#define fsa_pop_unsafe(DECLARED_TYPE, FSA_PTR) FSA_FUNC(DECLARED_TYPE, _pop)(FSA_PTR, DATA)

#define fsa_get(DECLARED_TYPE, FSA_PTR, IDX) FSA_FUNC(DECLARED_TYPE, _get)((FSA_PTR), (IDX))
#define fsa_get_unsafe(DECLARED_TYPE, FSA_PTR, IDX) FSA_FUNC(DECLARED_TYPE, _get_unsafe)((FSA_PTR), (IDX))
#define fsa_set(DECLARED_TYPE, FSA_PTR, IDX, VALUE) FSA_FUNC(DECLARED_TYPE, _set)((FSA_PTR), (IDX), (VALUE))
#define fsa_set_unsafe(DECLARED_TYPE, FSA_PTR, IDX, VALUE) FSA_FUNC(DECLARED_TYPE, _set_unsafe)((FSA_PTR), (IDX), (VALUE))

#define fsa_copy_from(DESTINATION_PTR, CONST_SOURCE_PTR)\
	do { \
		DEBUG_ENSURE_CONST_PTR_NOT_NULL(CONST_SOURCE_PTR, "Source array was null while attempting to copy it.");\
		DEBUG_ENSURE_PTR_NOT_NULL(DESTINATION_PTR, "Destination array was null while attempting to copy to it.");\
		DEBUG_ENSURE_UINT_GTE(DESTINATION_PTR->capacity, CONST_SOURCE_PTR->capacity, "Copying to destination array would result in a buffer overrun (ERROR: Source buffer size exceeds Destination buffer size.)");\
		DEBUG_ENSURE_UINT_EQUALS(sizeof(DESTINATION_PTR->data[0]), sizeof(CONST_SOURCE_PTR->data[0], "Destination array and Source array appear to have mismatched types."));\
		memcpy(&DESTINATION_PTR->data[0], &CONST_SOURCE_PTR->data[0], CONST_SOURCE_PTR->capacity);\
	} while (0)

#define fsa_count(DECLARED_TYPE) FSA_FUNC(DECLARED_TYPE, _count)()
#define fsa_capacity(DECLARED_TYPE) FSA_FUNC(DECLARED_TYPE, _capacity)()
#define fsa_size_in_bytes(DECLARED_TYPE) FSA_FUNC(DECLARED_TYPE, _size_in_bytes)


static inline void FSA_FUNC(ds_fsa_self, _init)(ds_fsa_self * arr)
{
	DEBUG_ENSURE_PTR_NOT_NULL(arr, "Pointer was null!");
	arr->current_push_idx = 0;
	arr->capacity = ds_element_count;
	memset(&arr->data[0], 0, (ds_element_count * sizeof(ds_type)) );
}

static inline size_t FSA_FUNC(ds_fsa_self, _count)(ds_fsa_self * arr)
{
	return arr->current_push_idx;
}

static inline size_t FSA_FUNC(ds_fsa_self, _capacity)(void)
{
	return ds_element_count;
}

static inline size_t FSA_FUNC(ds_fsa_self, _size_in_bytes)(ds_fsa_self * arr)
{
	return sizeof(arr->data[0]) * FSA_FUNC(ds_fsa_self, _capacity)();
}

static inline void FSA_FUNC(ds_fsa_self, _push)(ds_fsa_self * arr, ds_type value)
{
	size_t max_cap = FSA_FUNC(ds_fsa_self, _capacity)();
	ENSURE_UINT_LT(arr->current_push_idx + 1, max_cap, "Array tried to push a value exceeding its capacity.");
	arr->data[arr->current_push_idx] = value;
	arr->current_push_idx++;
}

static inline void FSA_FUNC(ds_fsa_self, _push_unsafe)(ds_fsa_self * arr, ds_type value)
{
	size_t max_cap = FSA_FUNC(ds_fsa_self, _capacity)();
	DEBUG_ENSURE_UINT_LT(arr->current_push_idx + 1, max_cap, "Array tried to push a value exceeding its capacity.");
	arr->data[arr->current_push_idx] = value;
	arr->current_push_idx++;
}

static inline ds_type FSA_FUNC(ds_fsa_self, _pop)(ds_fsa_self * arr)
{
	size_t max_cap = FSA_FUNC(ds_fsa_self, _capacity());
	ENSURE_UINT_LT(arr->current_push_idx, max_cap, "Array push index exceeded array capacity while attempting to pop a value. Memory error?");
	ENSURE_UINT_GTZERO(arr->current_push_idx, "Array pop index would underflow if the value was popped.");

	size_t target_idx = arr->current_push_idx - 1;
	arr->current_push_idx--;
	return arr->data[target_idx];
}

static inline ds_type FSA_FUNC(ds_fsa_self, _pop_unsafe)(ds_fsa_self * arr)
{
	size_t max_cap = FSA_FUNC(ds_fsa_self, _capacity());
	DEBUG_ENSURE_UINT_LT(arr->current_push_idx, max_cap, "Array push index exceeded array capacity while attempting to pop a value. Memory error?");
	DEBUG_ENSURE_UINT_GTZERO(arr->current_push_idx, "Array pop index would underflow if the value was popped.");

	size_t target_idx = arr->current_push_idx - 1;
	arr->current_push_idx--;
	return arr->data[target_idx];
}

static inline ds_type const * FSA_FUNC(ds_fsa_self, _get)(ds_fsa_self * arr, size_t idx)
{
	tec_internal_array_bounds_check( idx, FSA_FUNC(ds_fsa_self, _capacity)() );
	return &arr->data[idx];
}

static inline ds_type * FSA_FUNC(ds_fsa_self, _get_unsafe)(ds_fsa_self * arr, size_t idx)
{
	tec_internal_array_bounds_check_debug_only( idx, FSA_FUNC(ds_fsa_self, _capacity)() );
	return &arr->data[idx];
}

static inline void FSA_FUNC(ds_fsa_self, _set)(ds_fsa_self * arr, size_t idx, ds_type value)
{
	tec_internal_array_bounds_check( idx, FSA_FUNC(ds_fsa_self, _capacity)() );
	arr->data[idx] = value;
}

static inline void FSA_FUNC(ds_fsa_self, _set_unsafe)(ds_fsa_self * arr, size_t idx, ds_type value)
{
	tec_internal_array_bounds_check_debug_only( idx, FSA_FUNC(ds_fsa_self, _capacity)() );
	arr->data[idx] = value;
}





//Note: Do NOT USE pragma once here. This file is intended to be included multiple times

#include <stddef.h>
#include <string.h>
#include <inttypes.h>
#include "../dscommon.h"

#ifndef ds_element_count
	#define ds_element_count 0
#endif

#ifndef ds_type
	#define ds_type ds_ERROR_TYPE
#endif

#define ds_fsa_self FSA_TYPE(ds_type, ds_element_count)

typedef struct ds_fsa_self
{
	size_t current_push_idx;
	ds_type data[ds_element_count];
}
ds_fsa_self;

//==============================================================================
//
//                             Public facing API
//
//==============================================================================

// #define fsa_init(DECLARED_TYPE, FSA_PTR) FSA_FUNC(DECLARED_TYPE, _init)(FSA_PTR)
#define fsa_clear(DECLARED_TYPE, FSA_PTR) \
	do {\
		DEBUG_ENSURE_PTR_NOT_NULL(FSA_PTR, "Pointer was null!");\
		memset(&FSA_PTR->data[0], 0, FSA_FUNC(DECLARED_TYPE, _size_in_bytes)() );\
		FSA_PTR->current_push_idx = 0;\
	} while (0)

#define fsa_push(DECLARED_TYPE, FSA_PTR, DATA) FSA_FUNC(DECLARED_TYPE, _push)(FSA_PTR, DATA)
#define fsa_pop(DECLARED_TYPE, FSA_PTR) FSA_FUNC(DECLARED_TYPE, _pop)(FSA_PTR)
#define fsa_push_unsafe(DECLARED_TYPE, FSA_PTR, DATA) FSA_FUNC(DECLARED_TYPE, _push)(FSA_PTR, DATA)
#define fsa_pop_unsafe(DECLARED_TYPE, FSA_PTR) FSA_FUNC(DECLARED_TYPE, _pop)(FSA_PTR)

#define fsa_get(DECLARED_TYPE, FSA_PTR, IDX) FSA_FUNC(DECLARED_TYPE, _get)((FSA_PTR), (IDX))
#define fsa_get_unsafe(DECLARED_TYPE, FSA_PTR, IDX) FSA_FUNC(DECLARED_TYPE, _get_unsafe)((FSA_PTR), (IDX))
#define fsa_get_mut(DECLARED_TYPE, FSA_PTR, IDX) FSA_FUNC(DECLARED_TYPE, _get_mut)((FSA_PTR), (IDX))
#define fsa_get_mut_unsafe(DECLARED_TYPE, FSA_PTR, IDX) FSA_FUNC(DECLARED_TYPE, _get_mut_unsafe)((FSA_PTR), (IDX))
#define fsa_set(DECLARED_TYPE, FSA_PTR, IDX, VALUE) FSA_FUNC(DECLARED_TYPE, _set)((FSA_PTR), (IDX), (VALUE))
#define fsa_set_unsafe(DECLARED_TYPE, FSA_PTR, IDX, VALUE) FSA_FUNC(DECLARED_TYPE, _set_unsafe)((FSA_PTR), (IDX), (VALUE))

#define fsa_swap(DECLARED_TYPE, FSA_PTR, IDX_A, IDX_B) FSA_FUNC(DECLARED_TYPE, _swap)( (FSA_PTR), (IDX_A), (IDX_B) )
#define fsa_swap_unsafe(DECLARED_TYPE, FSA_PTR, IDX_A, IDX_B) FSA_FUNC(DECLARED_TYPE, _swap_unsafe)( (FSA_PTR), (IDX_A), (IDX_B) )

#define fsa_find(DECLARED_TYPE, FSA_PTR, VALUE) FSA_FUNC(DECLARED_TYPE, _find)( (FSA_PTR), (VALUE) )
#define fsa_has(DECLARED_TYPE, FSA_PTR, VALUE) FSA_FUNC(DECLARED_TYPE, _has)( (FSA_PTR), (VALUE) )

//Note: The single element assignment before the memcpy is to enforce that the underlying types match,
//you'll error out otherwise
#define fsa_copy_from(DESTINATION_TYPE, DESTINATION_PTR, SOURCE_TYPE, CONST_SOURCE_PTR)\
	do { \
		DEBUG_ENSURE_CONST_PTR_NOT_NULL(CONST_SOURCE_PTR, "Source array was null while attempting to copy it.");\
		DEBUG_ENSURE_PTR_NOT_NULL(DESTINATION_PTR, "Destination array was null while attempting to copy to it.");\
		DEBUG_ENSURE_UINT_GTE(FSA_CALC_CAPACITY(DESTINATION_TYPE, DESTINATION_PTR), FSA_CALC_CAPACITY(SOURCE_TYPE, CONST_SOURCE_PTR), "Copying to destination array would result in a buffer overrun (ERROR: Source buffer size exceeds Destination buffer size.)");\
		DEBUG_ENSURE_UINT_EQUALS(sizeof(DESTINATION_PTR->data[0]), sizeof(CONST_SOURCE_PTR->data[0]), "Destination array and Source array appear to have mismatched types.");\
		DESTINATION_PTR->data[0] = CONST_SOURCE_PTR->data[0];\
		memcpy( &DESTINATION_PTR->data[0], &CONST_SOURCE_PTR->data[0], FSA_CALC_CAPACITY(SOURCE_TYPE, CONST_SOURCE_PTR) * sizeof(CONST_SOURCE_PTR->data[0]) );\
	} while (0)

#define fsa_count(DECLARED_TYPE, FSA_PTR) FSA_FUNC(DECLARED_TYPE, _count)(FSA_PTR)
#define fsa_capacity(DECLARED_TYPE) FSA_FUNC(DECLARED_TYPE, _capacity)()
#define fsa_size_in_bytes(DECLARED_TYPE, FSA_PTR) FSA_FUNC(DECLARED_TYPE, _size_in_bytes)(FSA_PTR)

//======================================
//Iteration convenience
//======================================

#define __fsa_iterator_internal TEC_CONCAT(_tec_iterator_i_, __LINE__)
#define __fsa_end_internal TEC_CONCAT(_tec_iterator_end_, __LINE__)

//Iterates the entirety of the array's capacity, without accounting for the stack height
#define foreach_fsa(CAPTURE, DECLARATION_TYPE, DATA_TYPE, ARRAY_PTR)\
	size_t __fsa_iterator_internal = 0;\
	const size_t __fsa_end_internal = FSA_FUNC(DECLARATION_TYPE, _capacity)();\
	for (DATA_TYPE * CAPTURE = NULL; CAPTURE = &((ARRAY_PTR)->data[__fsa_iterator_internal]), __fsa_iterator_internal < __fsa_end_internal; ++__fsa_iterator_internal)

#define __fsa_iterator_internal_limit TEC_CONCAT(_tec_iterator_i_, __LINE__)
#define __fsa_end_internal_limit TEC_CONCAT(_tec_iterator_end_, __LINE__)

//Iterates the fsa up to the max height of the stack
#define foreach_fsa_stackmode(CAPTURE, DECLARATION_TYPE, DATA_TYPE, ARRAY_PTR)\
	size_t __fsa_iterator_internal_limit = 0;\
	const size_t __fsa_end_internal_limit = FSA_FUNC(DECLARATION_TYPE, _count)((ARRAY_PTR));\
	for (DATA_TYPE * CAPTURE = NULL; CAPTURE = &((ARRAY_PTR)->data[__fsa_iterator_internal_limit]), __fsa_iterator_internal_limit < __fsa_end_internal_limit; ++__fsa_iterator_internal_limit)

//======================================
//
//======================================

//Initialization Unneeded as we no longer need to track the capacity of the fsa
//Instead, just zero init with = {0}
// DS_INLINE void FSA_FUNC(ds_fsa_self, _init)(ds_fsa_self * arr)
// {
// 	DEBUG_ENSURE_PTR_NOT_NULL(arr, "Pointer was null!");
// 	arr->current_push_idx = 0;
// 	arr->capacity = ds_element_count;
// 	memset(&arr->data[0], 0, (ds_element_count * sizeof(ds_type)) );
// }

DS_INLINE size_t FSA_FUNC(ds_fsa_self, _count)(ds_fsa_self * arr)
{
	return arr->current_push_idx;
}

DS_INLINE size_t FSA_FUNC(ds_fsa_self, _capacity)(void)
{
	return ds_element_count;
}

DS_INLINE size_t FSA_FUNC(ds_fsa_self, _size_in_bytes)(ds_fsa_self * arr)
{
	return sizeof(arr->data[0]) * FSA_FUNC(ds_fsa_self, _capacity)();
}

DS_INLINE void FSA_FUNC(ds_fsa_self, _push)(ds_fsa_self * arr, ds_type value)
{
	size_t max_cap = FSA_FUNC(ds_fsa_self, _capacity)();
	ENSURE_UINT_LTE(arr->current_push_idx + 1, max_cap, "Array tried to push a value exceeding its capacity.");
	arr->data[arr->current_push_idx] = value;
	arr->current_push_idx++;
}

DS_INLINE void FSA_FUNC(ds_fsa_self, _push_unsafe)(ds_fsa_self * arr, ds_type value)
{
	size_t max_cap = FSA_FUNC(ds_fsa_self, _capacity)();
	DEBUG_ENSURE_UINT_LTE(arr->current_push_idx + 1, max_cap, "Array tried to push a value exceeding its capacity.");
	arr->data[arr->current_push_idx] = value;
	arr->current_push_idx++;
}

DS_INLINE ds_type FSA_FUNC(ds_fsa_self, _pop)(ds_fsa_self * arr)
{
	size_t max_cap = FSA_FUNC(ds_fsa_self, _capacity());
	ENSURE_UINT_LTE(arr->current_push_idx, max_cap, "Array push index exceeded array capacity while attempting to pop a value. Memory error?");
	ENSURE_UINT_GTZERO(arr->current_push_idx, "Array pop index would underflow if the value was popped.");

	size_t target_idx = arr->current_push_idx - 1;
	arr->current_push_idx--;
	return arr->data[target_idx];
}

DS_INLINE ds_type FSA_FUNC(ds_fsa_self, _pop_unsafe)(ds_fsa_self * arr)
{
	size_t max_cap = FSA_FUNC(ds_fsa_self, _capacity());
	DEBUG_ENSURE_UINT_LTE(arr->current_push_idx, max_cap, "Array push index exceeded array capacity while attempting to pop a value. Memory error?");
	DEBUG_ENSURE_UINT_GTZERO(arr->current_push_idx, "Array pop index would underflow if the value was popped.");

	size_t target_idx = arr->current_push_idx - 1;
	arr->current_push_idx--;
	return arr->data[target_idx];
}

DS_INLINE ds_type const * FSA_FUNC(ds_fsa_self, _get)(ds_fsa_self * arr, size_t idx)
{
	ds_internal_array_bounds_check( idx, FSA_FUNC(ds_fsa_self, _capacity)() );
	return &arr->data[idx];
}

DS_INLINE ds_type const * FSA_FUNC(ds_fsa_self, _get_unsafe)(ds_fsa_self * arr, size_t idx)
{
	ds_internal_array_bounds_check_debug_only( idx, FSA_FUNC(ds_fsa_self, _capacity)() );
	return &arr->data[idx];
}

DS_INLINE ds_type * FSA_FUNC(ds_fsa_self, _get_mut)(ds_fsa_self * arr, size_t idx)
{
	ds_internal_array_bounds_check( idx, FSA_FUNC(ds_fsa_self, _capacity)() );
	return &arr->data[idx];
}

DS_INLINE ds_type * FSA_FUNC(ds_fsa_self, _get_mut_unsafe)(ds_fsa_self * arr, size_t idx)
{
	ds_internal_array_bounds_check_debug_only( idx, FSA_FUNC(ds_fsa_self, _capacity)() );
	return &arr->data[idx];
}

DS_INLINE void FSA_FUNC(ds_fsa_self, _set)(ds_fsa_self * arr, size_t idx, ds_type value)
{
	ds_internal_array_bounds_check( idx, FSA_FUNC(ds_fsa_self, _capacity)() );
	arr->data[idx] = value;
}

DS_INLINE void FSA_FUNC(ds_fsa_self, _set_unsafe)(ds_fsa_self * arr, size_t idx, ds_type value)
{
	ds_internal_array_bounds_check_debug_only( idx, FSA_FUNC(ds_fsa_self, _capacity)() );
	arr->data[idx] = value;
}

DS_INLINE void FSA_FUNC(ds_fsa_self, _swap)(ds_fsa_self * arr, size_t idx_a, size_t idx_b)
{
	DEBUG_ENSURE_PTR_NOT_NULL(arr, "Arr was null while swapping.");
	ds_internal_array_bounds_check(idx_a, FSA_FUNC(ds_fsa_self, _capacity)());
	ds_internal_array_bounds_check(idx_b, FSA_FUNC(ds_fsa_self, _capacity)());

	ds_type temp = arr->data[idx_a];
	arr->data[idx_a] = arr->data[idx_b];
	arr->data[idx_b] = temp;
}

DS_INLINE void FSA_FUNC(ds_fsa_self, _swap_unsafe)(ds_fsa_self * arr, size_t idx_a, size_t idx_b)
{
	DEBUG_ENSURE_PTR_NOT_NULL(arr, "Arr was null while swapping.");
	ds_internal_array_bounds_check_debug_only(idx_a, FSA_FUNC(ds_fsa_self, _capacity)());
	ds_internal_array_bounds_check_debug_only(idx_b, FSA_FUNC(ds_fsa_self, _capacity)());

	ds_type temp = arr->data[idx_a];
	arr->data[idx_a] = arr->data[idx_b];
	arr->data[idx_b] = temp;
}

#ifdef ds_compare_function
DS_INLINE ds_fsa_search_result FSA_FUNC(ds_fsa_self, _find)(ds_fsa_self * arr, ds_type * value)
{
	size_t const cap = FSA_FUNC(ds_fsa_self, _capacity)();
	for (size_t i = 0; i < cap; ++i)
	{
		int located = ds_compare_function(&arr->data[i], value);
		if (located != 0)
		{
			continue;
		}
		else
		{
			return (ds_fsa_search_result){
				.idx = i,
				.value_found = true
			};
		}
	}

	return (ds_fsa_search_result){
		.idx = SIZE_MAX,
		.value_found = false
	};
}

DS_INLINE bool FSA_FUNC(ds_fsa_self, _has)(ds_fsa_self * arr, ds_type * value)
{
	return FSA_FUNC(ds_fsa_self, _find)(arr, value).value_found;
}
#endif


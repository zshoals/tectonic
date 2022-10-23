#pragma once

#include "tectonic/tcommon.h"
#include "tectonic/validation.h"

//Container name + user-defined tag
//IE dynarray_intptr
#define ds_self TEC_CONCAT(ds_prefix, ds_tag)
#define ds_self_t TEC_CONCAT(ds_self, _t)
#define ds_func(name) TEC_CONCAT(ds_self, name)

//===============
//Fixed Sized Arrays pre-needs

#define FSA_DECLARE(TYPE, MAX_ELEMENT_COUNT) FSA_TYPE(TYPE, MAX_ELEMENT_COUNT)
#define FSA_CONCAT(A, B) A##B
#define FSA_CC(A, B) FSA_CONCAT(A, B)
#define FSA_TYPE(TYPE, MAX_ELEMENT_COUNT) FSA_CC( FSA_CC(fsa_, TYPE), FSA_CC(_, MAX_ELEMENT_COUNT) )
#define FSA_FUNC(SELF, FUNCTION_SUFFIX) FSA_CC(SELF, FUNCTION_SUFFIX)

//-==============


//Interesting idea; foreach_array loop? We can maybe reverse the capture and size_t iterator type
//TODO(zshoals): Appears to work alright, however this is NOT SETUP FOR ARRAYS YET AND NEEDS FIXED
//Should be located in the actual array type data structure. Cool implementation!
#define foreach_array(CAPTURE, TYPE, ARRAY)\
	size_t TEC_CONCAT(_tec_iterator_i_, __LINE__) = 0;\
	const size_t TEC_CONCAT(_tec_iterator_end_, __LINE__) = ARRAY->length;\
	for (TYPE * CAPTURE = NULL; CAPTURE = &ARRAY[TEC_CONCAT(_tec_iterator_i_, __LINE__)], i < TEC_CONCAT(_tec_iterator_end_, __LINE__); ++TEC_CONCAT(_tec_i, __LINE__) )

static inline void tec_internal_array_bounds_check(size_t index, size_t array_length)
{
	//Note(zshoals): We --ALWAYS-- bounds check, FOREVER!!!!
	//Use get_unsafe for bounds checkless in release mode.
	ENSURE_TRUE(0 <= index && index < array_length, "Array index access was out of bounds. Slot may not have been initialized.");
}

static inline void tec_internal_array_bounds_check_debug_only(size_t index, size_t array_length)
{
	//Note(zshoals): We still bounds check always in debug builds, HOWEVER
	//release mode can use get/set_unsafe versions for maximal speed
	//prefer using the standard get/set functions unless you have a serious need for speed (graphics code)
	DEBUG_ENSURE_TRUE(0 <= index && index < array_length, "Array index access was out of bounds. Slot may not have been initialized.");
}

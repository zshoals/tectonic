#pragma once

#include "tectonic/tcommon.h"
#include "tectonic/validation.h"


//Available defines for end-users:
//ds_type, configures the type that the datastructure will use
//ds_tag, a custom name that can be used for the data type (pointer types will not work without a tag)
//ds_compare_function, a function returning an int and taking two pointers to objects of the same type
//		-1 for left GT right, 0 for equal, 1 for right GT left
//		if this is undefined, search functions and sorting are unavailable
//		for the specified data type
//ds_element_count, the max number of elements for fixed sized data types
//For FSA: Define type, compare_func if needed, element count, then
//  define YOURTYPENAME FSA_DECLARE(RAW_TYPE, RAW_COUNT)
// 	include fsa_h
//	include ds_undef_h

//EXAMPLES: 
// #define ds_type int
// #define ds_element_count 128
// #define intpool POOL_DECLARE(int, 128)
// #define intpool_key POOL_KEY_DECLARE(int, 128)
// #include "ds/pool.h"
// #include "ds/ds_undef.h"

// #define ds_type int
// #define ds_element_count 32
// #define intfsa FSA_DECLARE(int, 32)
// #include "ds/fsa.h"
// #include "ds/ds_undef.h"

#define DS_INLINE static inline

//Container name + user-defined tag
//IE dynarray_intptr
#define ds_self TEC_CONCAT(ds_prefix, ds_tag)
#define ds_self_t TEC_CONCAT(ds_self, _t)
#define ds_func(name) TEC_CONCAT(ds_self, name)

//Fallback type in case the user did not properly define a data type while including a
//templated datastructure
typedef struct ds_ERROR_TYPE
{
	bool YOU_MADE_A_MISTAKE;
}
ds_ERROR_TYPE;

#define DS_EXPAND(A) A
#define DS_CONCAT(A, B) A##B
#define DS_CC(A, B) DS_CONCAT(A, B)


//===============
//Fixed Sized Arrays pre-needs

typedef struct ds_fsa_search_result
{
	size_t idx;
	bool value_found;
}
ds_fsa_search_result;

#define FSA_CALC_CAPACITY(TYPE, PTR) (sizeof(PTR->data) / sizeof(PTR->data[0]))

#define FSA_DECLARE_IMPL(TYPE, MAX_ELEMENT_COUNT) FSA_TYPE(TYPE, MAX_ELEMENT_COUNT)
#define FSA_DECLARE(TYPE, MAX_ELEMENT_COUNT) FSA_TYPE(TYPE, MAX_ELEMENT_COUNT)
#define FSA_EXPAND(A) A
#define FSA_CONCAT(A, B) A##B
#define FSA_CC(A, B) FSA_CONCAT(A, B)
#define FSA_TYPE(TYPE, MAX_ELEMENT_COUNT) FSA_CC( FSA_CC(fsa_, TYPE), FSA_CC(_, MAX_ELEMENT_COUNT) )
#define FSA_FUNC(SELF, FUNCTION_SUFFIX) FSA_CC(SELF, FUNCTION_SUFFIX)

//-==============

//===============
//Pool pre-needs

#define POOL_DECLARE(TYPE, MAX_ELEMENT_COUNT) POOL_TYPE(TYPE, MAX_ELEMENT_COUNT)
#define POOL_KEY_DECLARE(TYPE, MAX_ELEMENT_COUNT) POOL_KEY_TYPE(TYPE, MAX_ELEMENT_COUNT)
#define POOL_TYPE(TYPE, MAX_ELEMENT_COUNT) FSA_CC( FSA_CC(pool_, TYPE), FSA_CC(_, MAX_ELEMENT_COUNT) )
#define POOL_KEY_TYPE(TYPE, MAX_ELEMENT_COUNT) FSA_CC( FSA_CC(pool_key_, TYPE), FSA_CC(_, MAX_ELEMENT_COUNT) )
#define POOL_FUNC(SELF, FUNCTION_SUFFIX) FSA_CC(SELF, FUNCTION_SUFFIX) 


//-==============

//===============
//Ringbuffer pre-needs

#define RINGBUF_DECLARE(TYPE, MAX_ELEMENT_COUNT) RINGBUF_TYPE(TYPE, MAX_ELEMENT_COUNT)
#define RINGBUF_TYPE(TYPE, MAX_ELEMENT_COUNT) FSA_CC( FSA_CC(ringbuf_, TYPE), FSA_CC(_, MAX_ELEMENT_COUNT) )
#define RINGBUF_FUNC(SELF, FUNCTION_SUFFIX) FSA_CC(SELF, FUNCTION_SUFFIX) 

//-==============

//Interesting idea; foreach_array loop? We can maybe reverse the capture and size_t iterator type
//TODO(zshoals): Appears to work alright, however this is NOT SETUP FOR ARRAYS YET AND NEEDS FIXED
//Should be located in the actual array type data structure. Cool implementation!
#define foreach_array(CAPTURE, TYPE, ARRAY)\
	size_t TEC_CONCAT(_tec_iterator_i_, __LINE__) = 0;\
	const size_t TEC_CONCAT(_tec_iterator_end_, __LINE__) = ARRAY->length;\
	for (TYPE * CAPTURE = NULL; CAPTURE = &ARRAY[TEC_CONCAT(_tec_iterator_i_, __LINE__)], i < TEC_CONCAT(_tec_iterator_end_, __LINE__); ++TEC_CONCAT(_tec_i, __LINE__) )

static inline void ds_internal_array_bounds_check(size_t index, size_t array_length)
{
	//Note(zshoals): We --ALWAYS-- bounds check, FOREVER!!!!
	//Use get_unsafe for bounds checkless in release mode.
	ENSURE_TRUE(0 <= index && index < array_length, "Array index access was out of bounds. Slot may not have been initialized.");
}

static inline void ds_internal_array_bounds_check_debug_only(size_t index, size_t array_length)
{
	//Note(zshoals): We still bounds check always in debug builds, HOWEVER
	//release mode can use get/set_unsafe versions for maximal speed
	//prefer using the standard get/set functions unless you have a serious need for speed (graphics code)
	DEBUG_ENSURE_TRUE(0 <= index && index < array_length, "Array index access was out of bounds. Slot may not have been initialized.");
}

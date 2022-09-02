#pragma once

#include "tectonic/tcommon.h"
#include "tectonic/validation.h"
#include "tectonic/memory/allocator.h"

//Container name + user-defined tag
//IE dynarray_intptr
#define ds_self TEC_CONCAT(ds_prefix, ds_tag)
#define ds_self_t TEC_CONCAT(ds_self, _t)
#define ds_func(name) TEC_CONCAT(ds_self, name)

static inline void tec_internal_array_bounds_check(size_t index, size_t array_length, size_t array_capacity)
{
	//Note(zshoals): We --ALWAYS-- bounds check, FOREVER!!!!
	//Use get_unsafe for bounds checkless in release mode.
	ENSURE_TRUE(0 <= index && index < array_length && index < array_capacity, "Array index access was out of bounds. Slot may not have been initialized.");
}

static inline void tec_internal_array_bounds_check_debug_only(size_t index, size_t array_length, size_t array_capacity)
{
	//Note(zshoals): We still bounds check always in debug builds, HOWEVER
	//release mode can use get/set_unsafe versions for maximal speed
	//prefer using the standard get/set functions unless you have a serious need for speed (graphics code)
	DEBUG_ENSURE_TRUE(0 <= index && index < array_length && index < array_capacity, "Array index access was out of bounds. Slot may not have been initialized.");
}

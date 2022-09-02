//Do not use pragma once here, this file is intended to be reincluded multiple times

#include "dscommon.h"

#define ds_prefix array_
#define ds_type int //TODO(zshoals): Remove me
#ifndef ds_tag
	#define ds_tag ds_type
#endif

typedef struct ds_self
{
	size_t length;
	size_t current_top_offset;
	ds_type * data;
}
ds_self_t;

static inline ds_self_t ds_func(_create)(allocator_t * allocator, size_t elem_count)
{
	return (ds_self_t){
		.length = elem_count,
		.current_top_offset = 0,
		.data = allocator_malloc(allocator, ds_type, elem_count)
	};
}
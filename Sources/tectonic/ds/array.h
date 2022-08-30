//Do not use pragma once here, this file is intended to be reincluded multiple times

#include <stddef.h>
#include "dscommon.h"

#define ds_prefix array_
#define ds_type int //TODO(zshoals): Remove me
#ifndef ds_tag
	#define ds_tag ds_type
#endif

typedef struct ds_self
{
	size_t length;
	ds_type * data;
}
ds_self_t;

static inline ds_self_t ds_func(_create)(void /*allocator, element length*/)
{

}
#pragma once

#include "tectonic/tcommon.h"

//Container name + user-defined tag
//IE dynarray_intptr
#define ds_self TEC_CONCAT(ds_prefix, ds_tag)
#define ds_self_t TEC_CONCAT(ds_self, _t)
#define ds_func(name) TEC_CONCAT(ds_self, name)
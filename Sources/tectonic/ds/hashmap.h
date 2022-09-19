
//Do not use pragma once here, this file is intended to be reincluded multiple times

#ifndef TEC_HASHMAP_INCLUDED
	#define TEC_HASHMAP_INCLUDED
	#include "tectonic/ds/hash.h"
	#include "tectonic/ds/dscommon.h"
#endif

#define ds_prefix map_
#define ds_type int //Remember to comment me out when you're done
#ifndef ds_tag
	#define ds_tag ds_type
#endif


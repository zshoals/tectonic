//NO PRAGMA ONCE
//This file is meant to be included repeatedly to generate separate, unique versions of bounded arrays

//"Bounded Fixed" arrays data structure
//The pattern of needing a fixed size, bounds checked array is so common we may as well generate it ourselves

#define _tec_self tec_bfarray_
#define _tec_concat(a, b) a ## b
#define _tec_paste(a, b) _tec_concat(a, b)
#define _tec_bfa_makename(prefix, type, count) _tec_paste(_tec_paste(prefix, type), _tec_paste(_, count))
#define _tec_bfa_makename_t(prefix, type, count) _tec_paste(_tec_bfa_makename(prefix, type, count), _t)

#define _tec_me _tec_bfa_makename(_tec_self, bfarray_type, bfarray_size)
#define _tec_me_t _tec_bfa_makename_t(_tec_self, bfarray_type, bfarray_size)
#define _tec_func(func_suffix) _tec_paste(_tec_me, func_suffix)

#include <stddef.h>
#include <assert.h>

typedef struct
_tec_me
{
	bfarray_type data[bfarray_size];
	size_t length;
}
_tec_me_t;

void _tec_func(_init)(_tec_me_t * bfarray)
{
	bfarray->length = bfarray_size;
};

void _tec_func(_set)(_tec_me_t * bfarray, bfarray_type data, size_t slot)
{
	assert(slot < bfarray_size && "Out of bounds access on bfarray, slot %d", slot);
	assert(slot > 0 && "Out of bounds access on bfarray, slot %d", slot);

	bfarray->data[slot] = data;
}

bfarray_type _tec_func(_get)(_tec_me_t * bfarray, size_t slot)
{
	assert(slot < bfarray_size && "Out of bounds access on bfarray, slot %d", slot);
	assert(slot > 0 && "Out of bounds access on bfarray, slot %d", slot);

	return bfarray->data[slot];
}

bfarray_type * _tec_func(_get_location)(_tec_me_t * bfarray, size_t slot)
{
	assert(slot < bfarray_size && "Out of bounds access on bfarray, slot %d", slot);
	assert(slot > 0 && "Out of bounds access on bfarray, slot %d", slot);

	return &bfarray->data[slot];
}



#undef bfarray_type
#undef bfarray_size

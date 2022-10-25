
//DO NOT use pragma once here, this file is intended to be included multiple times

#include <string.h>
#include <inttypes.h>
#include "../dscommon.h"

#ifndef ds_type
	#define ds_type ds_ERROR_TYPE
#endif

#ifndef ds_element_count
	#define ds_element_count 0
#endif

#define ds_ringbuf_self RINGBUF_TYPE(ds_type, ds_element_count)
#define DS_RINGBUF_FULL SIZE_MAX

typedef struct ds_ringbuf_self
{
	size_t start;
	size_t count;
	ds_type data[ds_element_count];
}
ds_ringbuf_self;

#define ringbuf_clear(DECLARED_TYPE, RINGBUF_PTR) RINGBUF_FUNC(DECLARED_TYPE, _clear)(RINGBUF_PTR)
#define ringbuf_push_back(DECLARED_TYPE, RINGBUF_PTR, DATA) RINGBUF_FUNC(DECLARED_TYPE, _push_back)(RINGBUF_PTR, DATA)
#define ringbuf_pop_front(DECLARED_TYPE, RINGBUF_PTR) RINGBUF_FUNC(DECLARED_TYPE, _pop_front)(RINGBUF_PTR)
#define ringbuf_capacity(DECLARED_TYPE) RINGBUF_FUNC(DECLARED_TYPE, _capacity)()
#define ringbuf_count(DECLARED_TYPE, RINGBUF_PTR) RINGBUF_FUNC(DECLARED_TYPE, _count)(RINGBUF_PTR)
#define ringbuf_populated(DECLARED_TYPE, RINGBUF_PTR) RINGBUF_FUNC(DECLARED_TYPE, _populated)(RINGBUF_PTR)
#define ringbuf_filled(DECLARED_TYPE, RINGBUF_PTR) RINGBUF_FUNC(DECLARED_TYPE, _filled)(RINGBUF_PTR)
#define ringbuf_empty(DECLARED_TYPE, RINGBUF_PTR) RINGBUF_FUNC(DECLARED_TYPE, _empty)(RINGBUF_PTR)
#define ringbuf_internal_calc_end(DECLARED_TYPE, RINGBUF_PTR) RINGBUF_FUNC(DECLARED_TYPE, _internal_calc_end)(RINGBUF_PTR)

#define __ringbuf_iterator_internal TEC_CONCAT(_tec_iterator_i_, __LINE__)
#define __ringbuf_loop_count TEC_CONCAT(_tec_loop_count_, __LINE__)
#define __ringbuf_index TEC_CONCAT(_tec_index_, __LINE__)
#define foreach_ringbuf(CAPTURE, DECLARATION_TYPE, DATA_TYPE, RINGBUF_PTR)\
	size_t __ringbuf_iterator_internal = 0;\
	size_t __ringbuf_loop_count = ringbuf_count(DECLARATION_TYPE, RINGBUF_PTR);\
	size_t __ringbuf_index = (RINGBUF_PTR)->start;\
	for (DATA_TYPE * CAPTURE = NULL; CAPTURE = &((RINGBUF_PTR)->data[__ringbuf_index]), __ringbuf_iterator_internal < __ringbuf_loop_count; __ringbuf_index = (__ringbuf_index + 1) & (ringbuf_capacity(DECLARATION_TYPE) - 1), ++__ringbuf_iterator_internal)


DS_INLINE size_t RINGBUF_FUNC(ds_ringbuf_self, _capacity)(void)
{
	return ds_element_count;
}

DS_INLINE size_t RINGBUF_FUNC(ds_ringbuf_self, _internal_calc_end)(ds_ringbuf_self * ring)
{
	return (ring->start + ring->count) & (ringbuf_capacity(ds_ringbuf_self) - 1);
}

DS_INLINE size_t RINGBUF_FUNC(ds_ringbuf_self, _count)(ds_ringbuf_self * ring)
{
	return ring->count;
}

DS_INLINE bool RINGBUF_FUNC(ds_ringbuf_self, _populated)(ds_ringbuf_self * ring)
{
	return (ringbuf_count(ds_ringbuf_self, ring) > 0);
}

DS_INLINE bool RINGBUF_FUNC(ds_ringbuf_self, _filled)(ds_ringbuf_self * ring)
{
	return (ringbuf_count(ds_ringbuf_self, ring) == ringbuf_capacity(ds_ringbuf_self));
}

DS_INLINE bool RINGBUF_FUNC(ds_ringbuf_self, _empty)(ds_ringbuf_self * ring)
{
	return (ringbuf_count(ds_ringbuf_self, ring) == 0);
}

DS_INLINE void RINGBUF_FUNC(ds_ringbuf_self, _clear)(ds_ringbuf_self * ring)
{
	ring->start = 0;
	ring->count = 0;
	memset(&ring->data, 0, sizeof(ring->data[0]) * ringbuf_capacity(ds_ringbuf_self));
}

DS_INLINE void RINGBUF_FUNC(ds_ringbuf_self, _push_back)(ds_ringbuf_self * ring, ds_type value)
{
	size_t cap = ringbuf_capacity(ds_ringbuf_self);
	DEBUG_ENSURE_UINT_EQUALS( (cap & (cap - 1)), 0, "Ringbuffers must be created with a power of 2 elements");
	ring->data[ringbuf_internal_calc_end(ds_ringbuf_self, ring)] = value;

	//If ring count is at the max capacity, advance ring->start by 1 as we have no more room in the ring buffer,
	//otherwise don't advance start as we are not being pushed forward by the imaginary "end" 
	ring->start += (ring->count == cap);
	ring->start &= cap - 1;

	ring->count += (ring->count < cap);
}

DS_INLINE ds_type RINGBUF_FUNC(ds_ringbuf_self, _pop_front)(ds_ringbuf_self * ring)
{
	DEBUG_ENSURE_UINT_GTZERO(ring->count, "Tried to pop a value off an empty ringbuffer!");
	size_t target_idx = ring->start;
	ring->start++;
	ring->start &= ringbuf_capacity(ds_ringbuf_self) - 1;

	ring->count--;

	return ring->data[target_idx];
}

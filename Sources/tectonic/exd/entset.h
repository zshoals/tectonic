
#pragma once

#include "tectonic/tcommon.h"
#include "exd.h"

//An ECS-specific bitset. Expects "EXD_MAX_ENTITES" to be set.

#define ENTSET_SHIFT 5
#define ENTSET_BLOCK_SIZE (1 << ENTSET_SHIFT)

typedef struct entset
{
	u32 bits[EXD_MAX_ENTITIES / ENTSET_BLOCK_SIZE];
}
entset_t;

#define for_entset(ITER_NAME) for(size_t ITER_NAME = 0; ITER_NAME < EXD_MAX_ENTITIES; ++ITER_NAME)

static inline u16 entset_internal_compute_block_idx(u16 idx)
{
	//Do a pow2 divide by the size of the bitflags to determine what block this idx would fall into
	return idx >> ENTSET_SHIFT;
}

static inline u16 entset_internal_compute_inner_block_idx(u16 idx)
{
	u16 idx_remainder = idx & (ENTSET_BLOCK_SIZE - 1);
	return idx_remainder;
}

static inline void entset_init(entset_t * set)
{
	for_entset(i)
	{
		set->bits[i] = 0;
	}
}

static inline void entset_init_from(entset_t * destination, entset_t * source)
{
	for_entset(i)
	{
		destination->bits[i] = source->bits[i];
	}
}

static inline bool entset_slot_is_set(entset_t * set, u16 idx)
{
	u16 block = entset_internal_compute_block_idx(idx);
	u16 inner_block_offset = entset_internal_compute_inner_block_idx(idx);

	return set->bits[block] & (1 << inner_block_offset);
}

static inline void entset_set_slot(entset_t * set, u16 idx)
{
	//Dunno if this is right, I'm tired
	set->bits[entset_internal_compute_block_idx(idx)] = 1 << entset_internal_compute_inner_block_idx(idx);
}

static inline void entset_clear_slot(entset_t * set, u16 idx)
{
	set->bits[entset_internal_compute_block_idx(idx)] &= ~(1 << entset_internal_compute_inner_block_idx(idx));
}

static inline void entset_and_slot(entset_t * a, entset_t * b, u16 idx)
{
	a->bits[idx] &= b->bits[idx];
}

static inline void entset_or_slot(entset_t * a, entset_t * b, u16 idx)
{
	a->bits[idx] |= b->bits[idx];
}

static inline void entset_not_slot(entset_t * a, entset_t * b, u16 idx)
{
	a->bits[idx] &= ~(b->bits[idx]);
}

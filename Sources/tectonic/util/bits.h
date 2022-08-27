#pragma once

#include "tectonic/tcommon.h"
#include "tectonic/validation.h"

typedef u32 bitflags32_t;

#define TEC_BIT(shift_left) (1 << shift_left)

//Not entirely sure yet as to the interface of this header;
//Should we set flags via individual bit shift_lefts?
//Right now, "bitflags32_t bit" indicates an already existing series of flags, like FLT_GENERIC | FLT_ENGINE etc, set up by TEC_BIT
//Who knows what the correct interface is...

static inline bitflags32_t tec_bits_create(void)
{
	return 0;
}

static inline bitflags32_t tec_bits_extract(bitflags32_t flags, bitflags32_t mask)
{
	//It might be important to make sure the mask or the flags are greater than zero
	//Maybe not though
	return flags & mask;
}

static inline bitflags32_t tec_bits_set(bitflags32_t flags, bitflags32_t mask)
{
	return flags | mask;
}

static inline bitflags32_t tec_bits_unset(bitflags32_t flags, bitflags32_t mask)
{
	// return tec_bits_set(flags, bit) ^ bit;
	//The above works, but is unnecessary, we can do it with a negated and
	return flags & ~mask;
}

static inline bool tec_bits_has_all_flags(bitflags32_t flags, bitflags32_t mask)
{
	return (flags & mask) == flags;
}

static inline bool tec_bits_has_any_flag(bitflags32_t flags, bitflags32_t mask)
{
	return (flags & mask) > 0;
}
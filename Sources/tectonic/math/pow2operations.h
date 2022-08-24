
#pragma once

#include <stdbool.h>

#include "tectonic/tcommon.h"
#include "tectonic/validation.h"

//Check if something is a power of two...
//These aren't really needed here anymore since the rest of the interface
//Just requires you to provide a pow2 exponent in the first place

static inline bool is_pow2_u32(u32 n)
{
	DEBUG_ENSURE_TRUE(n > 0, "u32 wasn't greater than 0 while checking if it was a power of 2, probably unintended");
	return n & (n - 1) == 0;
}

static inline bool is_pow2_u64(u64 n)
{
	DEBUG_ENSURE_TRUE(n > 0, "u64 wasn't greater than 0 while checking if it was a power of 2, probably unintended");
	return n & (n - 1) == 0;
}

//Fast divide by pow2

static inline bool pow2_divide_u32(u32 n, u32 pow2)
{
	DEBUG_ENSURE_TRUE(pow2 < 33, "pow2 shift exceeded u32max");
	pow2 = 1 << pow2;
	DEBUG_ENSURE_TRUE(is_pow2_u32(pow2), "Tried to fast divide a value but the value wasn't divided by a power2");
	return n >> pow2;
}

static inline bool pow2_divide_u64(u64 n, u64 pow2)
{
	DEBUG_ENSURE_TRUE(pow2 < 65, "pow2 shift exceeded u64max");
	pow2 = 1 << pow2;
	DEBUG_ENSURE_TRUE(is_pow2_u64(pow2), "Tried to fast divide a value but the value wasn't divided by a power2");
	return n >> pow2;
}

//Fast mult by pow2

static inline bool pow2_multiply_u32(u32 n, u32 pow2)
{
	DEBUG_ENSURE_TRUE(pow2 < 33, "pow2 shift exceeded u32max");
	pow2 = 1 << pow2;
	DEBUG_ENSURE_TRUE(is_pow2_u32(pow2), "Tried to fast multiply a value but the value wasn't multiplied by a power2");
	return n << pow2;
}

static inline bool pow2_multiply_u64(u64 n, u64 pow2)
{
	DEBUG_ENSURE_TRUE(pow2 < 65, "pow2 shift exceeded u64max");
	pow2 = 1 << pow2;
	DEBUG_ENSURE_TRUE(is_pow2_u64(pow2), "Tried to fast multiply a value but the value wasn't multiplied by a power2");
	return n << pow2;
}

//Mask by pow2 maybe?

//Also functions as modulo
static inline u32 pow2_mask_u32(u32 n, u32 pow2)
{
	DEBUG_ENSURE_TRUE(pow2 < 33, "pow2 shift exceeded u32max");
	pow2 = 1 << pow2;
	DEBUG_ENSURE_TRUE(is_pow2_u32(pow2), "U32 mask wasn't a power of 2");
	return n & (pow2 - 1);
}

//Also functions as modulo
static inline u64 pow2_mask_u32(u64 n, u64 pow2)
{
	DEBUG_ENSURE_TRUE(pow2 < 65, "pow2 shift exceeded u64max");
	pow2 = 1 << pow2;
	DEBUG_ENSURE_TRUE(is_pow2_u64(pow2), "U64 mask wasn't a power of 2");
	return n & (pow2 - 1);
}











#pragma once

#include "kinc/simd/uint32x4.h"
#include "kinc/simd/float32x4.h"

typedef kinc_uint32x4_t uint32x4;
typedef kinc_float32x4_t f32x4;

typedef struct f32x4_v2
{
	f32x4 xs;
	f32x4 ys;
}
f32x4_v2_t;

typedef struct uint32x4_v2
{
	uint32x4 xs;
	uint32x4 ys;
}
uint32x4_v2_t;


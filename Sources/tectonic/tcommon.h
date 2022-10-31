#pragma once

//Includes types that are basically used everywhere

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <assert.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef float f32;
typedef double f64;
typedef unsigned char uchar;
typedef unsigned int uint;

#define TEC_STRINGIFY_IMPL(X) #X
#define TEC_STRINGIFY(X) TEC_STRINGIFY_IMPL(X)

#define TEC_CONCAT_IMPL(A, B) A##B
#define TEC_CONCAT(A, B) TEC_CONCAT_IMPL(A, B)

#define CAST(TYPE) (TYPE)
#define DEREF(PTR) (*(PTR))

//Note: For now, only support positive values
#define for_range(STOP)\
	assert(STOP >= 0);\
	for (size_t TEC_CONCAT(_i, __LINE__) = 0; TEC_CONCAT(_i, __LINE__) < (STOP); ++TEC_CONCAT(_i, __LINE__))
#define for_range_var(CAPTURE, STOP)\
	assert(STOP >= 0);\
	for (size_t (CAPTURE) = 0; (CAPTURE) < (STOP); ++(CAPTURE))
#define for_range_var_slice(CAPTURE, START, STOP)\
	assert(START >= 0 && STOP >= 0);\
	for (size_t (CAPTURE) = START; (CAPTURE) < (STOP); ++(CAPTURE))

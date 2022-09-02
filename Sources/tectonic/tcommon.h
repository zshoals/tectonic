#pragma once

//Includes types that are basically used everywhere

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

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
#define DEREF(PTR) *(PTR)

#define for_range(STOP) for (size_t _i = 0; _i < (STOP); ++_i)
#define for_range_var(CAPTURE, STOP) for (size_t (CAPTURE) = 0; (CAPTURE) < (STOP); ++(CAPTURE))
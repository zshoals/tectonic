#pragma once

#include <stdint.h>

//Source: https://stackoverflow.com/a/28464194
//Hopefully portable way to find alignment in C99
#define tec_alignof(type) offsetof(struct { char c; type d; }, d)

#define TEC_KILOBYTES(AMOUNT) ((AMOUNT) * 1024)
#define TEC_MEGABYTES(AMOUNT) (TEC_KILOBYTES(AMOUNT) * 1024)
#define TEC_GIGABYTES(AMOUNT) (TEC_MEGABYTES(AMOUNT) * 1024)

typedef union tec_maxalign
{
	intmax_t _tec_internal_align_maxint;
	void * _tec_internal_align_void_ptr;
	long double _tec_internal_align_long_double; // This one hits 16 on clang/gcc, but 8 on windows
}
tec_maxalign_t;

typedef unsigned char tec_bytes;


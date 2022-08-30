#pragma once

#include <stddef.h>

typedef unsigned char tec_bytes;

#define TEC_KILOBYTES(AMOUNT) ((AMOUNT) * 1024)
#define TEC_MEGABYTES(AMOUNT) (TEC_KILOBYTES(AMOUNT) * 1024)
#define TEC_GIGABYTES(AMOUNT) (TEC_MEGABYTES(AMOUNT) * 1024)

//Source: https://stackoverflow.com/a/28464194
//Hopefully portable way to find alignment in C99
#define alignof(type) offsetof(struct { char c; type d; }, d)

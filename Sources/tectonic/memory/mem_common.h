#pragma once


//Source: https://stackoverflow.com/a/28464194
//Hopefully portable way to find alignment in C99
#define tec_alignof(type) offsetof(struct { char c; type d; }, d)

typedef unsigned char tec_bytes;

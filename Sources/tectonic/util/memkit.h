#pragma once

#include <string.h>

#define tec_byte_t unsigned char 

#define TEC_KILOBYTES(amount) ((amount) * 1024)
#define TEC_MEGABYTES(amount) ((TEC_KILOBYTES(amount)) * 1024)
#define TEC_GIGABYTES(amount) ((TEC_MEGABYTES(amount)) * 1024)

//Prefer static buffers. However....

//Frame Data Alloc, reset per frame
//Permanent Alloc, never freed
//Level Alloc, freed on "room" change
//Asset Loader Alloc (reuse level alloc or frame alloc?)
//Framestring Alloc, currently located in framestring.h
//This might be stupid. How does this interact with other libraries, for instance? Do I care?
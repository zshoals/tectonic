#pragma once

#define tec_byte_t unsigned char 

#define TEC_KILOBYTES(amount) ((amount) * 1024)
#define TEC_MEGABYTES(amount) ((TEC_KILOBYTES(amount)) * 1024)
#define TEC_GIGABYTES(amount) ((TEC_MEGABYTES(amount)) * 1024)
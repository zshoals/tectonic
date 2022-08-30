#pragma once

#include <stdbool.h>
#include "tectonic/tcommon.h"
#include "allocator.h"

#define TEC_KILOBYTES(AMOUNT) ((AMOUNT) * 1024)
#define TEC_MEGABYTES(AMOUNT) (TEC_KILOBYTES(AMOUNT) * 1024)
#define TEC_GIGABYTES(AMOUNT) (TEC_MEGABYTES(AMOUNT) * 1024)

//Source: https://stackoverflow.com/a/28464194
//Hopefully portable way to find alignment in C99
#define alignof(type) offsetof(struct { char c; type d; }, d)

typedef struct tec_global_memory
{
	allocator_t default_frame_allocator_storage;
	allocator_t default_level_allocator_storage;
	allocator_t default_permanent_allocator_storage;
	tec_bytes * frame_memory;
	tec_bytes * level_memory;
	tec_bytes * permanent_memory;
}
tec_global_memory_t;

static tec_global_memory_t program_memory = {0};

void init_global_memory_buffers(size_t frame_memory_size, size_t level_memory_size, size_t permanent_memory_size);
allocator_t * default_frame_allocator(void);
void reset_frame_allocator_memory(void);
allocator_t * default_level_allocator(void);
void reset_level_allocator_memory(void);
allocator_t * default_permanent_allocator(void);
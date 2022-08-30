#pragma once

#include "tectonic/tcommon.h"

enum {DEFAULT_ALIGNMENT = 16};

typedef enum
{
	ALLOCATOR_MODE_ARENA,
}
allocator_mode_e;

typedef struct allocator
{
	size_t memory_size;
	tec_bytes * memory_origin;
	allocator_mode_e mode;

	union memory_arena
	{
		size_t memory_top_offset;
	};
}
allocator_t;


allocator_t allocator_create(tec_bytes * memory_buffer, size_t memory_buffer_size, allocator_mode_e alloc_mode);
void * allocator_aligned_malloc(allocator_t * a, size_t target_alignment, size_t elem_size, size_t elem_count);
void allocator_free_all(allocator_t * a);
#define allocator_malloc(ALLOCATOR, TYPE, COUNT) allocator_aligned_malloc((ALLOCATOR), alignof(TYPE), sizeof(TYPE), (COUNT))
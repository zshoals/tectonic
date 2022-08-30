#pragma once

#include "tectonic/tcommon.h"
#include "tectonic/memory/memory.h"

struct allocator;

enum {DEFAULT_ALIGNMENT = 16};

typedef enum
{
	ALLOCATOR_MODE_ARENA,
}
allocator_mode_e;

typedef struct allocator
{
	size_t const memory_size;
	tec_bytes * const memory_origin;
	allocator_mode_e const mode;

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
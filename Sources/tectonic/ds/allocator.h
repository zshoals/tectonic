#pragma once

#include "tectonic/tcommon.h"

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
	uchar * const memory_origin;
	allocator_mode_e const mode;

	union memory_arena
	{
		size_t memory_end;
	};
}
allocator_t;

allocator_t allocator_create(uchar * memory_buffer, size_t memory_buffer_size, allocator_mode_e alloc_mode);
void * allocator_malloc(allocator_t * a, size_t elem_alignment, size_t elem_size, size_t elem_count);
void allocator_free_all(allocator_t * a);
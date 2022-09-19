#pragma once

#include <stdbool.h>
#include "tectonic/memory/mem_common.h"
#include "tectonic/ds/allocator.h"

typedef struct tec_global_memory
{
	allocator_t default_frame_allocator_storage;
	allocator_t default_level_allocator_storage;
	allocator_t default_permanent_allocator_storage;
}
tec_global_memory_t;

void init_global_memory_buffers(size_t frame_memory_size, size_t level_memory_size, size_t permanent_memory_size);
allocator_t * default_frame_allocator(void);
void reset_frame_allocator_memory(void);
allocator_t * default_level_allocator(void);
void reset_level_allocator_memory(void);
allocator_t * default_permanent_allocator(void);

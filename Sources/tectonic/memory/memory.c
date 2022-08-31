#include <stddef.h>
#include <stdlib.h>
#include "memory.h"
#include "allocator.h"
#include "tectonic/validation.h"

static tec_global_memory_t program_memory = {0};

void init_global_memory_buffers(size_t frame_memory_size, size_t level_memory_size, size_t permanent_memory_size)
{
	program_memory.default_frame_allocator_storage = allocator_create(malloc(frame_memory_size), frame_memory_size, ALLOCATOR_MODE_ARENA);
	program_memory.default_level_allocator_storage = allocator_create(malloc(level_memory_size), level_memory_size, ALLOCATOR_MODE_ARENA);
	program_memory.default_permanent_allocator_storage = allocator_create(malloc(permanent_memory_size), permanent_memory_size, ALLOCATOR_MODE_ARENA);

	ENSURE_PTR_NOT_NULL(program_memory.default_frame_allocator_storage.memory_origin, "Malloc failed to allocate the requested memory for the frame allocator");
	ENSURE_PTR_NOT_NULL(program_memory.default_level_allocator_storage.memory_origin, "Malloc failed to allocate the requested memory for the level allocator");
	ENSURE_PTR_NOT_NULL(program_memory.default_permanent_allocator_storage.memory_origin, "Malloc failed to allocate the requested memory for the permanent allocator");
}

allocator_t * default_frame_allocator(void)
{
	ENSURE_PTR_NOT_NULL(program_memory.default_frame_allocator_storage.memory_origin, "Global memory was not initialized.");
	return &program_memory.default_frame_allocator_storage;
}

void reset_frame_allocator_memory(void)
{
	allocator_free_all(&program_memory.default_frame_allocator_storage);
}

allocator_t * default_level_allocator(void)
{
	ENSURE_PTR_NOT_NULL(program_memory.default_level_allocator_storage.memory_origin, "Global memory was not initialized.");
	return &program_memory.default_level_allocator_storage;
}

void reset_level_allocator_memory(void)
{
	allocator_free_all(&program_memory.default_level_allocator_storage);
}

allocator_t * default_permanent_allocator(void)
{
	ENSURE_PTR_NOT_NULL(program_memory.default_permanent_allocator_storage.memory_origin, "Global memory was not initialized.");
	return &program_memory.default_permanent_allocator_storage;
}

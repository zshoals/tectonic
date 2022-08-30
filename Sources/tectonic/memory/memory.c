#include <stddef.h>
#include <stdlib.h>
#include "memory.h"
#include "allocator.h"
#include "tectonic/validation.h"

void init_global_memory_buffers(size_t frame_memory_size, size_t level_memory_size, size_t permanent_memory_size)
{
	program_memory.frame_memory = malloc(frame_memory_size);
	program_memory.level_memory = malloc(level_memory_size);
	program_memory.permanent_memory = malloc(permanent_memory_size);

	ENSURE_PTR_NOT_NULL(program_memory.frame_memory, "Malloc failed to allocate the requested memory for the frame allocator");
	ENSURE_PTR_NOT_NULL(program_memory.level_memory, "Malloc failed to allocate the requested memory for the level allocator");
	ENSURE_PTR_NOT_NULL(program_memory.permanent_memory, "Malloc failed to allocate the requested memory for the permanent allocator");

	program_memory.default_frame_allocator_storage = allocator_create(program_memory.frame_memory, frame_memory_size, ALLOCATOR_MODE_ARENA);
	program_memory.default_level_allocator_storage = allocator_create(program_memory.level_memory, level_memory_size, ALLOCATOR_MODE_ARENA);
	program_memory.default_permanent_allocator_storage = allocator_create(program_memory.permanent_memory, permanent_memory_size, ALLOCATOR_MODE_ARENA);
}

allocator_t * default_frame_allocator(void)
{
	ENSURE_PTR_NOT_NULL(program_memory.frame_memory, "Global memory was not initialized.");
	return &program_memory.default_frame_allocator_storage;
}

void reset_frame_allocator_memory(void)
{
	allocator_free_all(&program_memory.default_frame_allocator_storage);
}

allocator_t * default_level_allocator(void)
{
	ENSURE_PTR_NOT_NULL(program_memory.level_memory, "Global memory was not initialized.");
	return &program_memory.default_level_allocator_storage;
}

void reset_level_allocator_memory(void)
{
	allocator_free_all(&program_memory.default_level_allocator_storage);
}

allocator_t * default_permanent_allocator(void)
{
	ENSURE_PTR_NOT_NULL(program_memory.permanent_memory, "Global memory was not initialized.");
	return &program_memory.default_permanent_allocator_storage;
}

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

/*
	Tec aligned malloc and free
*/

/*
	This is kind of unneeded, an allocator can basically already do this as long as you give a little bit of extra initial memory
	Woops
*/

// aligned_memory_region_t tec_memory_aligned_malloc(size_t memory_size, size_t target_alignment)
// {
// 	ENSURE_TRUE(target_alignment > 0, "Tried to malloc memory, but targeted alignment was 0 or less");
// 	ENSURE_TRUE(((target_alignment & (target_alignment - 1))) == 0, "Target alignment was not a power of 2");
// 	ENSURE_TRUE(memory_size > 0, "Tried to malloc memory, but requested size was 0 or less");
// 	size_t buffered_size = memory_size + target_alignment;

// 	void * buffered_memory = malloc(buffered_size);
// 	ENSURE_PTR_NOT_NULL(buffered_memory, "Malloc failed to return a valid memory region while allocating");
// 	uintptr_t current_address = CAST(uintptr_t)buffered_memory;
// 	uintptr_t misalign = target_alignment - (current_address & (target_alignment - 1));
// 	uintptr_t aligned_address = current_address + misalign;
	
// 	//If we got lucky and the current address fulfills the current alignment requirement...
// 	return (aligned_memory_region_t) {
// 		._actual_origin = current_address,
// 		.aligned_origin = aligned_address,
// 		.memory_size = buffered_size
// 	};
// }

// void * tec_memory_free(aligned_memory_region_t * memory)
// {
// 	free(memory->_actual_origin);
// }


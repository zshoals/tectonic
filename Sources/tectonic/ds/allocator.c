#include <stdint.h>

#include "allocator.h"
#include "tectonic/validation.h"
#include "tectonic/tcommon.h"
#include "tectonic/memory/mem_common.h"
#include "kinc/log.h"

bool allocator_internal_is_power_of_two(size_t value)
{
	ENSURE_UINT_GTZERO(value, "Expected that the target alignment was greater than 0");
	return ((value & (value - 1))) == 0;
}

//Returns a memory buffer offset for a byte array
size_t allocator_internal_align_forward(size_t current_buffer_top, size_t align)
{
	size_t misalign = current_buffer_top & (align - 1);

	ENSURE_TRUE(align >= misalign, "Expected that the alignment was greater or equal to the maximum misalignment.");
	size_t align_forward = align - misalign;
	return current_buffer_top + align_forward;
}

size_t allocator_internal_compute_indexing_offset(tec_bytes * origin, tec_bytes * target)
{
	ENSURE_UINT_GTE(CAST(uintptr_t)target, CAST(uintptr_t)origin, "Memory address of the target should have been higher than the allocator's base address");

	size_t offset = CAST(uintptr_t)target - CAST(uintptr_t)origin;
	return offset;
}

//Note: It is assumed that the memory you provide is already 16 byte aligned. This should be the case if you received
//your memory from the stack or from a malloc call.
allocator_t allocator_create(tec_bytes * memory_buffer, size_t memory_buffer_size, allocator_mode_e alloc_mode)
{
	ENSURE_PTR_NOT_NULL(memory_buffer, "Tried to create an allocator with a null memory buffer");
	ENSURE_TRUE(memory_buffer_size > 0, "Mem buffer size must be greater than 0");

	if (CAST(uintptr_t)memory_buffer % DEFAULT_ALIGNMENT != 0)
	{
		kinc_log(KINC_LOG_LEVEL_WARNING, "Warning: Allocator was created, but the initial memory buffer was not 16-byte aligned. You may wish to verify that this was intended.");
		ENSURE_UNREACHABLE("Actually, for now, we don't support > 16 byte buffers, laziness.");
	}

	switch (alloc_mode)
	{
		case ALLOCATOR_MODE_ARENA:
			return (allocator_t){
				.memory_origin = memory_buffer,
				.memory_size = memory_buffer_size,
				.memory_top_offset = 0,
				.mode = alloc_mode
			};
			break;
		default:
			ENSURE_UNREACHABLE("Incorrect allocator mode while creating an allocator");
	}
};

//TODO(zshoals): Stack buffers aren't guaranteed to be aligned for 128 bytes, we literally ran into this issue in a test
//Probably applies to malloc also. We'll need to add an option to force this I suppose
//This is sort of an issue, we are only "aligned" for some cases, we can't really force alignment for something bigger than
//16 right now
//Addendum: Not actually an issue: m128 (what kinc supports) only requires 16 byte alignment, so we're ok for now

void * allocator_aligned_malloc(allocator_t * a, size_t target_alignment, size_t elem_size, size_t elem_count)
{
	//TODO(zshoals): We should probably do debug messages or something here
	//Some sort of memory tracking...
	ENSURE_PTR_NOT_NULL(a, "Provided allocator was null");
	bool is_pow_2 = allocator_internal_is_power_of_two(target_alignment);
	ENSURE_TRUE(is_pow_2, "Target alignment needs to be a valid power of 2");
	ENSURE_UINT_GTZERO(elem_count, "Elements provided to be allocated was 0");
	ENSURE_UINT_GTZERO(elem_size, "Element size was 0 or less while allocating");
	//Why the following ensure is here:
	//We currently assume the incoming target alignment is 16 byte aligned because that's what malloc/stack provides
	//Since we're operating on offsets and NOT actual pointer values, we can't get the actual pointer address right now
	//If you want to support values greater than 16 bytes, this will need to be changed to adjust the initial address
	//to the correct alignment
	ENSURE_TRUE(target_alignment <= DEFAULT_ALIGNMENT, "Target alignment exceeeded the maximum supported alignment");

	switch (a->mode)
	{
		case ALLOCATOR_MODE_ARENA:
			size_t target_offset = 0;
			if ((a->memory_top_offset & target_alignment) == 0)
			{
				//If the current target_alignment is already fulfilled by the memory offset, we're done
				target_offset = a->memory_top_offset;
			}
			else
			{
				//Otherwise, shift the target index until the memory we request is aligned
				target_offset = allocator_internal_align_forward(a->memory_top_offset, target_alignment);
			}

			size_t requested_memory = elem_size * elem_count;

			ENSURE_TRUE(target_offset + requested_memory < a->memory_size, "Requested memory overran a memory buffer");
			a->memory_top_offset = target_offset + requested_memory;

			return &a->memory_origin[target_offset];
		default:
			ENSURE_UNREACHABLE("Incorrect allocator mode while attempting memory allocation");
	}
}

void allocator_free_all(allocator_t * a)
{
	ENSURE_PTR_NOT_NULL(a, "Tried to free an allocator, but it was null");
	switch (a->mode)
	{
		case ALLOCATOR_MODE_ARENA:
			a->memory_top_offset = 0;
			break;
		default:
			ENSURE_UNREACHABLE("Incorrect allocator mode while freeing all memory");
	}
};

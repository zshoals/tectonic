#include "tectonic/validation.h"
#include "tectonic/tcommon.h"
#include "allocator.h"

bool allocator_internal_is_power_of_two(size_t value)
{
	ENSURE_TRUE(value > 0, "Expected that the target alignment was greater than 0");
	return value && ((value & (value - 1))) == 0;
}

//Returns a memory buffer offset for a byte array
size_t allocator_internal_align_forward(size_t current_buffer_top, size_t align)
{
	size_t misalign = current_buffer_top & (align - 1);

	ENSURE_TRUE(align >= misalign, "Expected that the alignment was greater or equal to the maximum misalignment.");
	size_t align_forward = align - misalign;
	return current_buffer_top + align_forward;
}

allocator_t allocator_create(tec_bytes * memory_buffer, size_t memory_buffer_size, allocator_mode_e alloc_mode)
{
	ENSURE_PTR_NOT_NULL(memory_buffer, "Tried to create an allocator with a null memory buffer");
	ENSURE_TRUE(memory_buffer_size > 0, "Mem buffer size must be greater than 0");
	ENSURE_TRUE((uintptr_t)memory_buffer % DEFAULT_ALIGNMENT == 0, "Tried to create an allocator with a non-default aligned memory region...should be 16 byte aligned.");

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

//TODO(Zach): Stack buffers aren't guaranteed to be aligned for 128 bytes, we literally ran into this issue in a test
//Probably applies to malloc also. We'll need to add an option to force this I suppose
//This is sort of an issue, we are only "aligned" for some cases, we can't really force alignment for something bigger than
//16 right now
//Addendum: Not actually an issue: m128 (what kinc supports) only requires 16 byte alignment, so we're ok for now

void * allocator_aligned_malloc(allocator_t * a, size_t target_alignment, size_t elem_size, size_t elem_count)
{
	//TODO(Zach): We should probably do debug messages or something here
	//Some sort of memory tracking...
	ENSURE_PTR_NOT_NULL(a, "Provided allocator was null");
	ENSURE_TRUE(allocator_internal_is_power_of_two(target_alignment), "Target alignment needs to be a valid power of 2");

	switch (a->mode)
	{
		case ALLOCATOR_MODE_ARENA:
			size_t target_offset = 0;
			if ((a->memory_top_offset & target_alignment) == 0)
			{
				//If the current target_alignment is already fulfilled by the memory offset, we're done
				//NOTE: We assume that the original memory buffer in the allocator is aligned to fulfill any type
				//This may or may not be true for some types (128 wide float groups?)
				//Should be ok for anything 16 or less though
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
	switch (a->mode)
	{
		case ALLOCATOR_MODE_ARENA:
			a->memory_top_offset = 0;
			break;
		default:
			ENSURE_UNREACHABLE("Incorrect allocator mode while freeing all memory");
	}
};

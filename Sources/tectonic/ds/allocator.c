#include <assert.h>
#include "tectonic/tcommon.h"
#include "allocator.h"

bool allocator_internal_is_power_of_two(size_t value)
{
	assert(value > 1);
	return (value & (value - 1)) == 0;
}

//Returns an address matching the required alignment
uintptr_t allocator_internal_align_forward(uintptr_t current_position, size_t align)
{
	//Get the value that would correspond to an aligned address
	allocator_internal_is_power_of_two(align);
	uintptr_t misalign = current_position & (align - 1);
	uintptr_t target = current_position + misalign;
	return target;
}

allocator_t allocator_create(uchar * memory_buffer, size_t memory_buffer_size, allocator_mode_e alloc_mode)
{
	assert(memory_buffer != NULL && "Tried to create an allocator with a null memory buffer");
	assert(memory_buffer_size > 0);
	assert((uintptr_t)memory_buffer % DEFAULT_ALIGNMENT == 0 && "Tried to create an allocator with a non-default aligned memory region");

	switch (alloc_mode)
	{
		case ALLOCATOR_MODE_ARENA:
			return (allocator_t){
				.memory_origin = memory_buffer,
				.memory_end = 0,
				.memory_size = memory_buffer_size,
				.mode = alloc_mode
			};
			break;
		default:
			assert(0 && "Incorrect allocator mode while creating an allocator");
	}
};

void * allocator_malloc(allocator_t * a, size_t elem_alignment, size_t elem_size, size_t elem_count)
{
	//TODO(colorful): Doesn't work for size 1 (char type), must fix
	size_t alloc_amount = elem_size * elem_count;
	assert(alloc_amount > 0 && elem_size > 1 && "Tried to malloc data but data requested was zero or less");
	
	//Determine the total amount that needs allocated. This should be as simple as
	//elem_size * elem_count as long as elem_size is greater than one

	//Determine if the current memory end ptr is a valid alignment for the elem_size
	//If it is, do nothing, otherwise shift it forward to the first valid location
	//Validate that it is in the acceptable memory range


	//return pointer?

	switch(a->mode)
	{
		case ALLOCATOR_MODE_ARENA:
			//We need a proper aligned alloc here, actual work needs to be done
			//Be careful
			break;
		default:
			assert(0 && "Unhandled or incorrectly configured allocator mode during malloc");
	}

	return (void *)a->memory_end;
};

void allocator_free_all(allocator_t * a)
{
	a->memory_end = 0;
};

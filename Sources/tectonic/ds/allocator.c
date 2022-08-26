#include <tectonic/validation.h>
#include "tectonic/tcommon.h"
#include "allocator.h"

bool allocator_internal_is_power_of_two(size_t value)
{
	ENSURE_TRUE(value > 1, "Expected a power of two alignment while allocating memory");
	return (value & (value - 1)) == 0;
}

//Returns an address matching the required alignment
uintptr_t allocator_internal_align_forward(uintptr_t current_position, size_t align)
{
	allocator_internal_is_power_of_two(align);

	uintptr_t misalign = current_position & (align - 1);
	uintptr_t align_forward = align - misalign;
	return current_position + align_forward;
}

allocator_t allocator_create(uchar * memory_buffer, size_t memory_buffer_size, allocator_mode_e alloc_mode)
{
	ENSURE_PTR_NOT_NULL(memory_buffer, "Tried to create an allocator with a null memory buffer");
	ENSURE_TRUE(memory_buffer_size > 0, "Mem buffer size must be greater than 0");
	ENSURE_TRUE((uintptr_t)memory_buffer % DEFAULT_ALIGNMENT == 0, "Tried to create an allocator with a non-default aligned memory region");
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
			ENSURE_UNREACHABLE("Incorrect allocator mode while creating an allocator");
			break;
	}
};

//Hello I am here to work today
//Or am I....because it's been several hours at this point of random ass distraction
//now it's been almost the whole day and nothing has gotten done, that's unfortunate now isn't it
//still haven't done very much bucko
//actually haven't done anything at all if we're being honest

//Another day, more no-working to do I guess? Who knows how many days weeks or years it's going to take before we put in some effort
//It's so strange, but I simply don't want to do the thinking, and I hate that I feel this way even though it's trivial
//for me to type and interact with this environment. It's made for me, and I just can't do it :(
//Let's type a sentence out of our head and get it onto this very page right about now ok? 

void * allocator_malloc(allocator_t * a, size_t elem_alignment, size_t elem_size, size_t elem_count)
{
	ENSURE_UNIMPLEMENTED();
};

void allocator_free_all(allocator_t * a)
{
	a->memory_end = 0;
};

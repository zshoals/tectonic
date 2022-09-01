#pragma once

#include <stdbool.h>
#include "tectonic/tcommon.h"
#include "allocator.h"

#define TEC_KILOBYTES(AMOUNT) ((AMOUNT) * 1024)
#define TEC_MEGABYTES(AMOUNT) (TEC_KILOBYTES(AMOUNT) * 1024)
#define TEC_GIGABYTES(AMOUNT) (TEC_MEGABYTES(AMOUNT) * 1024)

//Source: https://stackoverflow.com/a/28464194
//Hopefully portable way to find alignment in C99
#define tec_alignof(type) offsetof(struct { char c; type d; }, d)

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

//At a later point, we might want to add our own "generous" malloc that over-requests memory to align to
//larger than 16-byte alignment types, this is probably safer than hoping that malloc/stack are 16 byte aligned
//+ it supports larger alignment requirements if we do that.






//Unneeded, already handled by the existence of allocators. Just overrequest memory a little bit and then
//Allocate from an allocator with a target alignment

// typedef struct aligned_memory_region
// {
// 	void * _actual_origin;
// 	void * aligned_origin;
// 	size_t memory_size;
// }
// aligned_memory_region_t;

//Guarantees a memory region that fulfills the alignment requirement. This may allocate more memory
//than requested
// aligned_memory_region_t tec_memory_aligned_malloc(size_t memory_size, size_t target_alignment);
// void * tec_memory_free(aligned_memory_region_t memory);


#include <string.h>
#include <inttypes.h>
#include "genarray.h"
#include "exd.h"
#include "tectonic/validation.h"

static inline void * genarray_internal_compute_location(genarray_t * components, entity_t ent)
{
	u64 slot = EXD_ENTITY_ID(ent);

	ENSURE_UINT_GTZERO(slot, "Entity handle resolved to 0 while computing a component location");

	uintptr_t base_address = CAST(uintptr_t)(components->data);
	uintptr_t advance = slot * components->per_element_size;
	uintptr_t data_offset = base_address + advance;
	uintptr_t maximum_offset = EXD_MAX_ENTITIES * components->per_element_size;
	ENSURE_UINT_LT(advance, maximum_offset, "Overran memory region while computing component location");
	return CAST(void *)data_offset;
}

static inline void * genarray_internal_compute_location_unsafe(genarray_t * components, entity_t ent)
{
	u64 slot = EXD_ENTITY_ID(ent);

	DEBUG_ENSURE_UINT_GTZERO(slot, "Entity handle resolved to 0 while computing a component location");

	uintptr_t base_address = CAST(uintptr_t)(components->data);
	uintptr_t advance = slot * components->per_element_size;
	uintptr_t data_offset = base_address + advance;
	uintptr_t maximum_offset = EXD_MAX_ENTITIES * components->per_element_size;
	DEBUG_ENSURE_UINT_LT(advance, maximum_offset, "Overran memory region while computing component location");
	return CAST(void *)data_offset;
}

void genarray_init(genarray_t * components, allocator_t * mem, size_t per_element_size)
{
	entset_init(&components->entity_list);
	components->per_element_size = per_element_size;
	if (per_element_size == 0)
	{
		//Special case; this is a tag
		components->data = NULL;
	}	
	else
	{
		//TODO(zshoals): hardcoding the alignment here is a bit omegalul
		components->data = allocator_aligned_malloc(mem, 16, per_element_size, EXD_MAX_ENTITIES);
	}
}

void genarray_init_as_tag_container(genarray_t * components, allocator_t * mem)
{
	genarray_init(components, mem, 0);
}

void genarray_clear(genarray_t * components)
{
	memset(components->data, 0, components->per_element_size * EXD_MAX_ENTITIES);
}

void const * genarray_untyped_get(genarray_t * components, entity_t ent)
{
	ENSURE_PTR_NOT_NULL(components->data, "Tried to access Tag-type genarray data.");
	return genarray_internal_compute_location(components, ent);
}

void const * genarray_untyped_get_unsafe(genarray_t * components, entity_t ent)
{
	ENSURE_PTR_NOT_NULL(components->data, "Tried to access Tag-type genarray data.");
	return genarray_internal_compute_location_unsafe(components, ent);
}

void * genarray_untyped_get_mut(genarray_t * components, entity_t ent)
{
	ENSURE_PTR_NOT_NULL(components->data, "Tried to access Tag-type genarray data.");
	return genarray_internal_compute_location(components, ent);
}

void * genarray_untyped_get_mut_unsafe(genarray_t * components, entity_t ent)
{
	ENSURE_PTR_NOT_NULL(components->data, "Tried to access Tag-type genarray data.");
	return genarray_internal_compute_location_unsafe(components, ent);
}


void * genarray_untyped_set(genarray_t * components, entity_t ent)
{
	DEBUG_ENSURE_UINT_GTZERO(ent, "Entity ID was invalid while attempting to set a component array.");
	ENSURE_PTR_NOT_NULL(components->data, "Tried to access Tag-type genarray data.");
	entset_set_slot(&components->entity_list, EXD_ENTITY_ID(ent));
	return genarray_untyped_get_mut_unsafe(components, ent);
}

void genarray_untyped_unset(genarray_t * components, entity_t ent)
{
	DEBUG_ENSURE_UINT_GTZERO(ent, "Entity ID was invalid while attempting to unset a component array.");
	ENSURE_PTR_NOT_NULL(components->data, "Tried to access Tag-type genarray data.");
	entset_clear_slot(&components->entity_list, EXD_ENTITY_ID(ent));
}

bool genarray_untyped_has(genarray_t * components, entity_t ent)
{
	return entset_slot_is_set(&components->entity_list, EXD_ENTITY_ID(ent));
}
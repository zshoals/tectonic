#include "world.h"

#include <assert.h>
#include "entity.h"
#include "tectonic/ds/allocator.h"
#include "exd-common.h"
#include "kinc/log.h"


void exd_world_init(exd_world_t * world, allocator_t * mem)
{
	kinc_log(KINC_LOG_LEVEL_INFO, "Max Ents: %d", EXD_MAX_ENTITIES);
	world->current_max_components = 0;
	world->mem = mem;
	exd_entity_list_init(&world->entities, mem);
}

void exd_world_component_create_sized_component_storage(exd_world_t * world, size_t per_element_size, size_t component_idx)
{
	exd_component_init(&world->component_arrays[component_idx], per_element_size, world->mem);
	world->current_max_components++;
}

void exd_world_component_tag_create_storage(exd_world_t * world, size_t component_idx)
{
	exd_world_component_create_sized_component_storage(world, 0, component_idx);
}

void const * exd_world_component_get(exd_world_t * world, size_t component_idx, entity_t ent)
{
	//TODO(zshoals): Typing it as void is an unfortunate hack...
	//Getting the appropriate type out of world may not be super trivial, so skip it for now.
	return exd_component_get(&world->component_arrays[component_idx], void, ent);
}

void * exd_world_component_get_mut(exd_world_t * world, size_t component_idx, entity_t ent)
{
	return exd_component_get_mut(&world->component_arrays[component_idx], void, ent);
}

void * exd_world_component_set(exd_world_t * world, size_t component_idx, entity_t ent)
{
	return exd_component_set(&world->component_arrays[component_idx], void, ent);
}

bool exd_world_entity_has(exd_world_t * world, size_t component_idx, entity_t ent)
{
	return exd_component_has(&world->component_arrays[component_idx], ent);
}

bool exd_world_entity_is_valid(exd_world_t * world, entity_t ent)
{
	return exd_entity_list_is_entity_valid(&world->entities, ent);
}

entity_t exd_world_entity_new(exd_world_t * world)
{
	return exd_entity_list_get_new_entity(&world->entities);
}

void exd_world_entity_kill(exd_world_t * world, entity_t ent)
{
	entity_t world_reference_entity = exd_entity_list_resolve_index(&world->entities, EXD_ENTITY_ID(ent));
	if (world_reference_entity == ent)
	{
		exd_entity_list_free_entity(&world->entities, ent);
		exd_for_range_var(i, world->current_max_components)
		{
			exd_component_clear(&world->component_arrays[i], ent);
		}
	}
	else
	{
		//NOTE: It is legal to attempt to kill an "expired" entity, it's just not going to do anything.
		//The user may store an entity, try and kill it later, but by that time the entity has been killed elsewhere.
		kinc_log(KINC_LOG_LEVEL_INFO, "Warning: Tried to kill an invalid entity %zu. Current ent state was %zu", ent, world_reference_entity);
	}
}

//================================
// Shorthand accessor
//================================

static exd_world_t * EXD_INTERNAL_GLOBAL_WORLD = NULL;

void exd_world_set_global_world_for_shorthand_access(exd_world_t * world)
{
	EXD_INTERNAL_GLOBAL_WORLD = world;
}

exd_world_t * exd_world_get_global_world_for_shorthand_access()
{
	return EXD_INTERNAL_GLOBAL_WORLD;
}
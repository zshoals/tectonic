#include "world.h"

#include <assert.h>
#include "entity.h"
#include "tectonic/ds/allocator.h"
#include "exd-common.h"

void exd_world_init(exd_world_t * world, allocator_t * mem)
{
	world->current_max_components = 0;
	world->mem = mem;
	exd_entity_list_init(&world->entities, mem);
}

void exd_world_create_sized_component_storage(exd_world_t * world, size_t per_element_size, size_t component_idx)
{
	exd_component_init(&world->component_arrays[component_idx], per_element_size, world->mem);
	world->current_max_components++;
}

void exd_world_set_global_world_for_shorthand_access(exd_world_t * world)
{
	EXD_INTERNAL_GLOBAL_WORLD = world;
}

void exd_world_create_tag_storage(exd_world_t * world, size_t component_idx)
{
	exd_world_create_sized_component_storage(world, 0, component_idx);
}

void const * exd_world_get_component(exd_world_t * world, size_t component_idx, entity_t ent)
{
	//TODO(zshoals): Typing it as void is an unfortunate hack...
	//Getting the appropriate type out of world may not be super trivial, so skip it for now.
	return exd_component_get(&world->component_arrays[component_idx], void, ent);
}

void * exd_world_get_mut_component(exd_world_t * world, size_t component_idx, entity_t ent)
{
	return exd_component_get_mut(&world->component_arrays[component_idx], void, ent);
}

void * exd_world_set_component(exd_world_t * world, size_t component_idx, entity_t ent)
{
	return exd_component_set(&world->component_arrays[component_idx], void, ent);
}

entity_t exd_world_new_entity(exd_world_t * world)
{
	return exd_entity_list_get_new_entity(&world->entities);
}

void exd_world_kill_entity(exd_world_t * world, entity_t ent)
{
	exd_for_range_var(i, world->current_max_components)
	{
		exd_component_clear(&world->component_arrays[i], ent);
	}

	exd_entity_list_free_entity(&world->entities, ent);
}

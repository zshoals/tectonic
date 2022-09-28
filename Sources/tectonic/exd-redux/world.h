#pragma once

#include "entity_list.h"
#include "component_data.h"
#include "tectonic/ds/allocator.h"
#include "entity.h"

#define EXD_WORLD_MAX_COMPONENTS 256

typedef struct exd_world
{
	exd_entity_list_t entities;
	exd_component_t component_arrays[EXD_WORLD_MAX_COMPONENTS];
	size_t current_max_components;
	allocator_t * mem;
}
exd_world_t;

static exd_world_t * EXD_INTERNAL_GLOBAL_WORLD = NULL;

void exd_world_init(exd_world_t * world, allocator_t * mem);
#define exd_world_create_component_storage(WORLD, TYPE, COMPONENT_IDX)
void exd_world_create_sized_component_storage(exd_world_t * world, size_t per_element_size, size_t component_idx);
void exd_world_create_tag_storage(exd_world_t * world, size_t component_idx);

void exd_world_set_global_world_for_shorthand_access(exd_world_t * world);

void const * exd_world_get_component(exd_world_t * world, size_t component_idx, entity_t ent);
void * exd_world_get_mut_component(exd_world_t * world, size_t component_idx, entity_t ent);

void * exd_world_set_component(exd_world_t * world, size_t component_idx, entity_t ent);

entity_t exd_world_new_entity(exd_world_t * world);
void exd_world_kill_entity(exd_world_t * world, entity_t ent);

//============================================
//Shorthand access functions to save on typing
//============================================
#define exd_new_ent() exd_world_new_entity(EXD_INTERNAL_GLOBAL_WORLD)
#define exd_kill_ent(ENTITY) exd_world_kill_entity(EXD_INTERNAL_GLOBAL_WORLD)
#define exd_get_comp(COMPONENT_IDX, ENTITY) exd_world_get_component(EXD_INTERNAL_GLOBAL_WORLD, COMPONENT_IDX, ENTITY)
#define exd_get_mut_comp(COMPONENT_IDX, ENTITY) exd_world_get_mut_component(EXD_INTERNAL_GLOBAL_WORLD, COMPONENT_IDX, ENTITY)
#define exd_set_comp(COMPONENT_IDX, ENTITY) exd_world_set_component(EXD_INTERNAL_GLOBAL_WORLD, COMPONENT_IDX, ENTITY)



//Ideas for additional functions: Report max entities in use, ents free, total component usage, etc.

//Ex shorthand interface
// exd_new_ent();
// exd_kill_ent(ent);
// exd_get_comp(position, ent);
// exd_set_comp(position, ent);
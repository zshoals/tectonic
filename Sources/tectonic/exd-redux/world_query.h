#pragma once

#include "tectonic/ds/allocator.h"
#include "world.h"
#include "exd-common.h"

typedef struct exd_query
{
	exd_entset_t matcher;
	exd_world_t * world;
}
exd_query_t;

typedef struct exd_entity_iter
{
	exd_query_t * q;
	u32 current_index;
}
exd_entity_iter_t;

void exd_query_init_from(exd_query_t * q, exd_world_t * world, allocator_t * mem);
#define exd_query_init_fast(QUERY_PTR, ALLOCATOR_PTR) exd_query_init_from(QUERY_PTR, exd_world_get_global_world_for_shorthand_access(), ALLOCATOR_PTR)
void exd_query_include(exd_query_t * q, size_t component_index);
void exd_query_optional_include(exd_query_t * q, size_t component_index);
void exd_query_exclude(exd_query_t * q, size_t component_index);
exd_entity_iter_t exd_query_compile(exd_query_t * q);

//===========================================
//VVVVVV Query iteration convenience VVVVVVVV
//===========================================

entity_t exd_entity_iter_next(exd_entity_iter_t * it);

#define foreach_entity(ENT_HANDLE, ENTITY_ITER_PTR)\
	for(entity_t ENT_HANDLE = exd_entity_iter_next(ENTITY_ITER_PTR); ENT_HANDLE; ENT_HANDLE = exd_entity_iter_next(ENTITY_ITER_PTR))

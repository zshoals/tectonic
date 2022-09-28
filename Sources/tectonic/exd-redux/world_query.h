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
void exd_query_include(exd_query_t * q, exd_world_t * world, size_t component_index);
void exd_query_optional_include(exd_query_t * q, exd_world_t * world, size_t component_index);
void exd_query_exclude(exd_query_t * q, exd_world_t * world, size_t component_index);
exd_entity_iter_t exd_query_compile(exd_query_t * q);

//===========================================
//VVVVVV Query iteration convenience VVVVVVVV
//===========================================

#define foreach_entity(ENTITY_ITER)\
	for(size_t i = 0; i < EXD_MAX_ENTITIES; ++i) //TODO(zshoals): FIXME I DON'T DO ANYTHING YET

entity_t exd_entity_iter_next(exd_entity_iter_t * it);
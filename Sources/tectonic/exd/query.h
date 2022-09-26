
#pragma once

#include "entset.h"

typedef entset_t query_t;

#define query_build(QUERY_NAME, ENTITIES_ENTSET, ITER_NAME) \
	query_t QUERY_NAME; \
	entset_init_from(QUERY_NAME, ENTITIES_ENTSET); \
	for_entset(ITER_NAME)

#define query_INCLUDE(QUERY, COMPONENT_BITSET, ITER_NAME) \
	entset_and_slot(QUERY, COMPONENT_BITSET, ITER_NAME)

#define query_MAYBE(QUERY, COMPONENT_BITSET, ITER_NAME) \
	entset_or_slot(QUERY, COMPONENT_BITSET, ITER_NAME)

//Note: This is order dependent. Exclude queries should always be last.
#define query_EXCLUDE(QUERY, COMPONENT_BITSET, ITER_NAME) \
	entset_not_slot(QUERY, COMPONENT_BITSET, ITER_NAME)


typedef struct entity_iter
{
	query_t * q;
	u16 current_idx;
}
entity_iter_t;

#define for_entities(ENT_HANDLE, ENTITY_ITER_PTR)\
	for(u16 ENT_HANDLE = 0; entity_iter_has_next(COMPONENT_ITER_PTR); ENT_HANDLE = component_iter_next(COMPONENT_ITER_PTR) )

static inline u16 entity_iter_next(entity_iter_t * it)
{
	return it->current_idx;
}

static inline bool entity_iter_has_next(entity_iter_t * it)
{
	while (!entset_slot_is_set(it->q, it->current_idx) && it->current_idx < EXD_MAX_ENTITIES)
	{
		it->current_idx++;
	}

	//if the above loop exited before hitting EXD_MAX_ENTITIES, we have found a live entity at an index
	return (it->current_idx != EXD_MAX_ENTITIES - 1);
}

static inline entity_iter_t query_compile(query_t * query)
{
	return (entity_iter_t){
		.q = query,
		.current_idx = 0
	};
}

//Usage Examples below:

// query_build(q, entities_entset, i)
// {
// 	query_include(q, positions_entset, i);
// 	query_include(q, rotations_entset, i);
// }

// entity_iter_t it = query_compile(q);

// for_entities(ent, it)
// {
// 	position_t const * pos = genarr_positions_get(positions, ent);
// 	position_t * rot = genarr_rotations_get(rotations, ent);
// }
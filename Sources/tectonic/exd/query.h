
#pragma once

#include "entset.h"
#include "genarray.h"
#include "exd.h"
#include "entity_manifest.h"
#include "tectonic/tcommon.h"

typedef struct query
{
	entity_manifest_t * entities_list;
	entset_t matching_entities;
} 
query_t;

#define query_build(QUERY_NAME, ENTITIES_MANIFEST, ITER_NAME) \
	query_t __LOC_#QUERY_NAME; \
	query_t * QUERY_NAME = &__LOC_#QUERY_NAME;\
	QUERY_NAME->entities_list = ENTITIES_MANIFEST;\
	entset_init_from(&QUERY_NAME->matching_entities, &ENTITIES_MANIFEST->entities); \
	for_entset(ITER_NAME)

#define query_INCLUDE(QUERY, COMPONENT, ITER_NAME) \
	entset_and_slot(&QUERY->matching_entities, &COMPONENT->entity_list, ITER_NAME)

#define query_OPTIONAL_INCLUDE(QUERY, COMPONENT, ITER_NAME) \
	entset_or_slot(&QUERY->matching_entities, &COMPONENT->entity_list, ITER_NAME)

//Note: This is order dependent. Exclude queries should always be last.
#define query_EXCLUDE(QUERY, COMPONENT, ITER_NAME) \
	entset_not_slot(&QUERY->matching_entities, &COMPONENT->entity_list, ITER_NAME)

static inline entity_iter_t query_compile(query_t * query)
{
	return (entity_iter_t){
		.q = query,
		.current_idx = 0
	};
}


typedef struct entity_iter
{
	query_t * q;
	u16 current_idx;
}
entity_iter_t;

//The u16 ent handle needs to be the actual entity id now in u64; when iterating, we want to be able to store the id
#define foreach_entities(ENT_HANDLE, ENTITY_ITER_PTR)\
	for(entity_t ENT_HANDLE = entity_iter_next(ENTITY_ITER_PTR); ENT_HANDLE; ENT_HANDLE = entity_iter_next(ENTITY_ITER_PTR) )

static inline entity_t entity_iter_next(entity_manifest_t * ents, entity_iter_t * it)
{
	//Progress forward through the entire bitset until we encounter a live entity (a bit that is set, literally!)
	while (entset_slot_is_not_set(it->q, it->current_idx) && it->current_idx < EXD_MAX_ENTITIES)
	{
		//TODO(zshoals): we need to actually retrieve the entity handle here as we do in fact need the generation now 
		it->current_idx++;
	}

	//If we exceed max_entities, we return 0 by masking against max_entities to signal that we're done with the loop
	return entity_manifest_resolve_slot(it->q->entities_list, it->current_idx & EXD_MAX_ENTITIES_MASK);
}

//Usage Examples below:

// query_build(q, entities_entset, i)
// {
// 	query_INCLUDE(q, positions_es, i);
// 	query_INCLUDE(q, rotations_es, i);
//	query_EXCLUDE(q, movables_tag_es, i);
// }

// entity_iter_t it = query_compile(q);

// for_entities(ent, it)
// {
// 	position_t const * pos = genarr_positions_get(positions, ent);
// 	rotation_t * rot = genarr_rotations_get_mut(rotations, ent);
// }
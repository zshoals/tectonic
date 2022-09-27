#include "entity_manifest.h"
#include "tectonic/validation.h"

static void entity_manifest_increment_entity_generation(entity_manifest_t * ents, entity_t ent)
{
	ents->entities[EXD_ENTITY_ID(ent)] = exd_increment_entity_generation(ent);
}

void entity_manifest_init(entity_manifest_t * ents)
{
	for(size_t i = 0; i < EXD_MAX_ENTITIES; ++i)
	{
		ents->entities[i] = i;
		ents->freelist[EXD_MAX_ENTITIES - i] = (i + 1) & EXD_MAX_ENTITIES;
	}

	ents->first_free = EXD_MAX_ENTITIES - 1;
	entset_init(&ents->entities_in_use);
}

entity_t entity_manifest_resolve_slot(entity_manifest_t * ents, u16 id)
{
	return ents->entities[id];
}

void entity_manifest_get_first_free(entity_manifest_t * ents)
{
	DEBUG_ENSURE_UINT_GTZERO(ents->first_free, "Decrementing this entset value would result in an underflow while getting first free ent");
	size_t first_free_idx = ents->freelist[ents->first_free];
	ents->first_free--;
	entity_t entity = ents->entities[first_free_idx];
	ENSURE_UINT_GTZERO(EXD_ENTITY_ID(entity), "ERROR: Depleted all available entities.");
	entset_set_slot(&ents->entities_in_use, entity);

	return entity;
}

void entity_manifest_free_entity(entity_manifest_t * ents, entity_t ent)
{
	DEBUG_ENSURE_UINT_LT(ents->first_free, EXD_MAX_ENTITIES, "Releasing this entity would result in more entities than exist in the world");
	DEBUG_ENSURE_UINT_GTZERO(EXD_ENTITY_ID(ent), "Attempted to free an invalid entity (INVALID_ENTITY, aka 0)");

	ents->first_free++;
	ents->freelist[ents->first_free] = ent;
	entset_clear_slot(&ents->entities_in_use, ent);
	entity_manifest_increment_entity_generation(ents, ent);
}

bool entity_manifest_entity_is_current(entity_manifest_t * ents, entity_t ent)
{
	//Grab the entity slot by taking the lower id bits of the entity;
	//A slot stores the entity id and its generation also
	//If the current manifest generation doesn't match the provided entity's generation, there is a mismatch
	//and the provided entity must not be up to date with the manifest
	return ents->entities[EXD_ENTITY_ID(ent)] == ent;
}

u64 entity_manifest_current_highest_generation(entity_manifest_t * ents)
{
	u64 highest_generation = 0;
	for (size_t i = 0; i < EXD_MAX_ENTITIES; ++i)
	{
		u64 current_generation = EXD_ENTITY_GENERATION(ents->entities[i]);
		if (current_generation > highest_generation)
		{
			current_generation = highest_generation;
		}
	}

	return highest_generation;
}

void entity_manifest_set_all_generations_to(entity_manifest_t * ents, size_t value)
{
	for (size_t i = 0; i < EXD_MAX_ENTITIES; ++i)
	{
		u64 upshifted_generation = value << EXD_ENTITY_ID_BITS;
		u64 entity_with_cleared_generation = EXD_ENTITY_ID(ents->entities[i]);
		ents->entities[i] = upshifted_generation | entity_with_cleared_generation;
	}
}


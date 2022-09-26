
#pragma once

//This is the E C SSSSSSSSSS

#include "tectonic/tcommon.h"
#include "tectonic/validation.h"

#ifndef EXD_MAX_ENTITIES
	#define EXD_MAX_ENTITIES -1337
	//This is basically an error so a max entity count of -1337 will probably explode
#endif
#define EXD_MAX_ENTITIES_MASK (EXD_MAX_ENTITIES - 1)

#define INVALID_ENTITY 0

typedef u64 entity_t;

#define EXD_ENTITY_ID_BITS 13
#define EXD_ENTITY_ID_MASK (1 << EXD_ENTITY_ID_BITS)
#define EXD_ENTITY_GENERATION_BITS (64 - EXD_ENTITY_ID_BITS)

#define EXD_ENTITY_GENERATION(ENTITY) ((ENTITY) >> EXD_ENTITY_ID_BITS)
#define EXD_ENTITY_ID(ENTITY) ((ENTITY) & EXD_ENTITY_ID_MASK)

static inline entity_t exd_increment_entity_generation(entity_t ent)
{
	u64 generation = EXD_ENTITY_GENERATION(ent);
	DEBUG_ENSURE_UINT_LT(generation, (1 << EXD_ENTITY_GENERATION_BITS) - 1, "CRITICAL ERROR: Somehow, through some miracle, exhausted entity generation bits....");
	generation++;

	u64 upshifted_generation = generation << EXD_ENTITY_ID_BITS;

	return upshifted_generation | EXD_ENTITY_ID(ent);
}

typedef struct exd_world
{
	entity_manifest_t * entities;
}
exd_world_t;
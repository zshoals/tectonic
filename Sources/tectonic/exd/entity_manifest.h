
#pragma once

#include <stdbool.h>
#include "exd.h"
#include "entset.h"

#define EXD_MAX_ENTITIES 9999

typedef struct entity_manifest
{
	entity_t entities[EXD_MAX_ENTITIES];
	entset_t entities_in_use;
	size_t freelist[EXD_MAX_ENTITIES];
	size_t first_free;
}
entity_manifest_t;

void entity_manifest_init(entity_manifest_t * ents);
void entity_manifest_get_first_free(entity_manifest_t * ents);
void entity_manifest_free_entity(entity_manifest_t * ents, entity_t ent);
bool entity_manifest_entity_is_current(entity_manifest_t * ents, entity_t ent);
u64 entity_manifest_current_highest_generation(entity_manifest_t * ents);
void entity_manifest_set_all_generations_to(entity_manifest_t * ents, size_t value);

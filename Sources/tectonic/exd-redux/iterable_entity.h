#pragma once

#include "entity.h"

//Query iteration generates this entity type which is compatible with unsafe component accesses
typedef struct exd_iterable_entity
{
	entity_t id;
}
exd_iterable_entity_t;

static inline entity_t exd_iterable_entity_to_normal_entity(exd_iterable_entity_t ent) { return ent.id; }
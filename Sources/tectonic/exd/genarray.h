

#pragma once

#include "exd.h"
#include "entset.h"
#include "tectonic/tcommon.h"
#include "tectonic/ds/allocator.h"

typedef struct genarray
{
	entset_t entity_list;
	size_t per_element_size;
	void * data;
}
genarray_t;

//Potentially wrap with even more convenient names
//ent_create(component, ent), etc
//As before, killing the entity is the tough part

void genarray_init(genarray_t * components, allocator_t * mem, size_t per_element_size);
void genarray_init_as_tag_container(genarray_t * components, allocator_t * mem);
void genarray_clear(genarray_t * components);
void const * genarray_untyped_get(genarray_t * components, entity_t ent);
void const * genarray_untyped_get_unsafe(genarray_t * components, entity_t ent);
void * genarray_untyped_get_mut(genarray_t * components, entity_t ent);
void * genarray_untyped_get_mut_unsafe(genarray_t * components, entity_t ent);
void * genarray_untyped_set(genarray_t * components, entity_t ent);
void genarray_untyped_unset(genarray_t * components, entity_t ent);
bool genarray_untyped_has(genarray_t * components, entity_t ent);

#define genarray_get(GENARRAY, TYPE, ENTITY) (TYPE const *)(genarray_untyped_get(GENARRAY, ENTITY))
#define genarray_get_unsafe(GENARRAY, TYPE, ENTITY) (TYPE const *)(genarray_untyped_get_unsafe(GENARRAY, ENTITY))
#define genarray_get_mut(GENARRAY, TYPE, ENTITY) (TYPE *)(genarray_untyped_get_mut(GENARRAY, ENTITY))
#define genarray_get_mut_unsafe(GENARRAY, TYPE, ENTITY) (TYPE *)(genarray_untyped_get_mut_unsafe(GENARRAY, ENTITY))
#define genarray_set(GENARRAY, TYPE, ENTITY) (TYPE *)(genarray_untyped_set(GENARRAY, ENTITY))
#define genarray_unset(GENARRAY, ENTITY) genarray_untyped_set(GENARRAY, ENTITY)
#define genarray_has(GENARRAY, ENTITY) genarray_untyped_has(GENARRAY, ENTITY)
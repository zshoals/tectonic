

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

#define genarray_get(GENARRAY, TYPE, ENTITY) (TYPE const *)(genarray_untyped_get(GENARRAY, ENTITY))
#define genarray_get_unsafe(GENARRAY, TYPE, ENTITY) (TYPE const *)(genarray_untyped_get_unsafe(GENARRAY, ENTITY))
#define genarray_get_mut(GENARRAY, TYPE, ENTITY) (TYPE *)(genarray_untyped_get_mut(GENARRAY, ENTITY))
#define genarray_get_mut_unsafe(GENARRAY, TYPE, ENTITY) (TYPE *)(genarray_untyped_get_mut_unsafe(GENARRAY, ENTITY))

void genarray_init(genarray_t * components, allocator_t * mem, size_t per_element_size, size_t count);
void genarray_clear(genarray_t * components);
void const * genarray_untyped_get(genarray_t * components, entity_t ent);
void const * genarray_untyped_get_unsafe(genarray_t * components, entity_t ent);
void * genarray_untyped_get_mut(genarray_t * components, entity_t ent);
void * genarray_untyped_get_mut_unsafe(genarray_t * components, entity_t ent);


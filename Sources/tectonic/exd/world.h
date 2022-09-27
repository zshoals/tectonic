
// #pragma once

// #include "entity_manifest.h"
// #include "genarray.h"
// #include "tectonic/ds/allocator.h"

// typedef struct exd_world
// {
// 	entity_manifest_t entities;
// 	allocator_t * allocator;
// 	genarray_t positions;
// 	genarray_t rotations;
// }
// exd_world_t;


// genarray_t * positions = allocator_malloc(default_frame_allocator(), genarray_t);
// genarray_init(positions, default_frame_allocator, sizeof(position_t), EXD_MAX_ENTITIES);


// move_system(entity_manifest_t * entities, genarray_t * positions, genarray_t * rotations)
// {
// 	query_build(q, entities, i)
// 	{
// 		query_INCLUDE(&q, positions, i);
// 		query_INCLUDE(&q, rotations, i);
// 		query_INCLUDE(&q, movables, i);
// 		query_EXCLUDE(&q, enemies, i);
// 	}

// 	entity_iter_t it = query_compile(&q);

// 	foreach_entities(ent, it)
// 	{
// 		position const * pos = genarray_get(positions, position, ent);
// 		rotation const * rot = genarray_get(rotations, rotation, ent);

// 		pos->x += 99;
// 		pos->y += 100;

// 		rot += 0.1;
// 	}
// }
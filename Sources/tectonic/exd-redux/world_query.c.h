#include "world_query.h"

#include "tectonic/ds/allocator.h"

void exd_query_init_from(exd_query_t * q, exd_world_t * world, allocator_t * mem)
{
	exd_entset_init(&q->matcher, mem);
	exd_entset_copy_data_from(&q->matcher, &world->entities.entity_states);
	q->world = world;
}

void exd_query_include(exd_query_t * q, size_t component_index)
{
	assert(component_index < q->world->current_max_components);
	exd_entset_and(&q->matcher, &q->world->component_arrays[component_index].in_use_components);
}

void exd_query_optional_include(exd_query_t * q, size_t component_index)
{
	assert(component_index < q->world->current_max_components);
	exd_entset_or(&q->matcher, &q->world->component_arrays[component_index].in_use_components);
}

void exd_query_exclude(exd_query_t * q, size_t component_index)
{
	assert(component_index < q->world->current_max_components);
	exd_entset_not(&q->matcher, &q->world->component_arrays[component_index].in_use_components);
}

exd_query_iter_t exd_query_compile(exd_query_t * q)
{
	return (exd_query_iter_t){
		.q = q,
		.current_index = 0
	};
}



//====================================
//          Entity iter ops
//====================================

exd_iterable_entity_t exd_query_iter_next(exd_query_iter_t * it)
{
	exd_entset_t * iteration_list = &it->q->matcher;

	while(exd_entset_slot_is_not_set(iteration_list, it->current_index) && it->current_index < EXD_MAX_ENTITIES)
	{
		it->current_index++;
	}

	u16 enabled_entity_slot = it->current_index;
	it->current_index++;

	return (exd_iterable_entity_t){
		.id = exd_entity_list_resolve_index(&it->q->world->entities, enabled_entity_slot)
	};
}

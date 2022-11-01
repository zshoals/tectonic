

//DO NOT use pragma once here, this file is intended to be included multiple times

#include "../dscommon.h"
#include "string.h"


#ifndef ds_type
	#define ds_type ds_ERROR_TYPE
#endif

#ifndef ds_element_count
	#define ds_element_count 0
#endif

#define ds_pool_self POOL_TYPE(ds_type, ds_element_count)
#define ds_pool_key POOL_KEY_TYPE(ds_type, ds_element_count)
#define ds_pool_union_type POOL_TYPE(val_or_ptr, ds_element_count)

#define DS_POOL_DEPLETED SIZE_MAX

typedef union ds_pool_union_type
{
	ds_type value;
	size_t next_free;
}
ds_pool_union_type;

typedef struct ds_pool_self
{
	ds_pool_union_type pool[ds_element_count];
	size_t count_in_use;
	size_t first_free;
}
ds_pool_self;

typedef struct ds_pool_key
{
	size_t handle;
}
ds_pool_key;

#define pool_init(DECLARED_TYPE, POOL_PTR) POOL_FUNC(DECLARED_TYPE, _init)(POOL_PTR)
#define pool_clear(DECLARED_TYPE, POOL_PTR) POOL_FUNC(DECLARED_TYPE, _clear)(POOL_PTR)
#define pool_take(DECLARED_TYPE, POOL_PTR) POOL_FUNC(DECLARED_TYPE, _take)(POOL_PTR)
#define pool_release(DECLARED_TYPE, POOL_PTR, POOL_KEY) POOL_FUNC(DECLARED_TYPE, _release)(POOL_PTR, POOL_KEY)
#define pool_resolve_key(DECLARED_TYPE, POOL_PTR, POOL_KEY) POOL_FUNC(DECLARED_TYPE, _resolve_key)(POOL_PTR, POOL_KEY)
#define pool_capacity(DECLARED_TYPE) POOL_FUNC(DECLARED_TYPE, _capacity)()
#define pool_count_free(DECLARED_TYPE, POOL_PTR), POOL_FUNC(DECLARED_TYPE, _count_free)(POOL_PTR)

DS_INLINE size_t POOL_FUNC(ds_pool_self, _capacity)(void)
{
	return ds_element_count;
}

DS_INLINE size_t POOL_FUNC(ds_pool_self, _count_free)(ds_pool_self * pool)
{
	return pool_capacity(ds_pool_self) - pool->count_in_use;
}

DS_INLINE void POOL_FUNC(ds_pool_self, _init)(ds_pool_self * pool)
{
	DEBUG_ENSURE_PTR_NOT_NULL(pool, "Pool was null!");

	memset(&pool->pool, 0, sizeof(ds_pool_union_type) * ds_element_count);

	//Exclude the very last index; the final index being exhausted indicates an empty pool
	for_range_var(i, pool_capacity(ds_pool_self) - 1)
	{
		pool->pool[i].next_free = i + 1;
	}
	pool->pool[pool_capacity(ds_pool_self) - 1].next_free = DS_POOL_DEPLETED;

	pool->first_free = 0;
	pool->count_in_use = 0;
}

DS_INLINE void POOL_FUNC(ds_pool_self, _clear)(ds_pool_self * pool)
{
	DEBUG_ENSURE_PTR_NOT_NULL(pool, "Pool was null!");
	pool_init(ds_pool_self, pool);
}

DS_INLINE ds_type * POOL_FUNC(ds_pool_self, _resolve_key)(ds_pool_self * pool, ds_pool_key key)
{
	DEBUG_ENSURE_PTR_NOT_NULL(pool, "Pool was null!");

	return &pool->pool[key.handle].value;
}

DS_INLINE ds_pool_key POOL_FUNC(ds_pool_self, _take)(ds_pool_self * pool)
{
	DEBUG_ENSURE_PTR_NOT_NULL(pool, "Pool was null!");
	DEBUG_ENSURE_TRUE(pool->first_free != DS_POOL_DEPLETED, "Exhausted all available pool items.");

	ds_pool_key key = {.handle = pool->first_free };
	//This hurts to read
	//This sets the pools current first free targeted slot to the next available free slot
	pool->first_free = pool->pool[pool->first_free].next_free;
	pool->count_in_use++;

	return key;
}

DS_INLINE void POOL_FUNC(ds_pool_self, _release)(ds_pool_self * pool, ds_pool_key key)
{
	DEBUG_ENSURE_PTR_NOT_NULL(pool, "Pool was null!");
	DEBUG_ENSURE_UINT_LTE(pool->count_in_use + 1, pool_capacity(ds_pool_self, pool), "Pool performed a double release somewhere.");

	ds_pool_union_type * element = &pool->pool[key.handle];
	element->next_free = pool->first_free;
	pool->first_free = key.handle;
	pool->count_in_use--;

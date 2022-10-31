
#pragma once

#include "tectonic/ds/allocator.h"
#include "exd-common.h"
#include "entity.h"
#include "iterable_entity.h"

//EXD_ENTSET_BITWIDTH_SHIFT is used for certain fast division and modulo operations
//This value represents the backing integer size, before a (1 << shift) operation
#define EXD_HIENTSET_BITWIDTH_SHIFT 5
#define EXD_HIENTSET_BITWIDTH (1 << EXD_HIENTSET_BITWIDTH_SHIFT)
//The total amount of integers for storage of layer0 
#define EXD_HIENTSET_ELEMENT_COUNT (EXD_MAX_ENTITIES / EXD_HIENTSET_BITWIDTH)

//Represents how many integer blocks are in each layer
#define EXD_HIENTSET_LAYER0_SIZE EXD_HIENTSET_ELEMENT_COUNT
#define EXD_HIENTSET_LAYER1_SIZE (EXD_HIENTSET_LAYER0_SIZE / EXD_HIENTSET_BITWIDTH)
#define EXD_HIENTSET_LAYER2_SIZE (EXD_HIENTSET_LAYER1_SIZE / EXD_HIENTSET_BITWIDTH)
#define EXD_HIENTSET_LAYER3_SIZE (1)

//Used to determine which array block to land in
#define EXD_HIENTSET_LAYER0_SHIFT (EXD_HIENTSET_BITWIDTH_SHIFT)
#define EXD_HIENTSET_LAYER1_SHIFT (EXD_HIENTSET_LAYER0_SHIFT + EXD_HIENTSET_BITWIDTH_SHIFT)
#define EXD_HIENTSET_LAYER2_SHIFT (EXD_HIENTSET_LAYER1_SHIFT + EXD_HIENTSET_BITWIDTH_SHIFT)
#define EXD_HIENTSET_LAYER3_SHIFT (EXD_HIENTSET_LAYER2_SHIFT + EXD_HIENTSET_BITWIDTH_SHIFT)

#define EXD_HIENTSET_LAYER0_ITER_ADVANCE 1
#define EXD_HIENTSET_LAYER1_ITER_ADVANCE (1 << EXD_HIENTSET_LAYER1_SHIFT)
#define EXD_HIENTSET_LAYER2_ITER_ADVANCE (1 << EXD_HIENTSET_LAYER2_SHIFT)
#define EXD_HIENTSET_LAYER3_ITER_ADVANCE (1 << EXD_HIENTSET_LAYER3_SHIFT)

typedef struct exd_hientset
{
	u32 layer3;
	u32 * layer2;
	u32 * layer1;
	u32 * layer0;
}
exd_hientset_t;

void exd_hientset_init(allocator_t * mem, exd_hientset_t * ents);
void exd_hientset_copy_data_from(exd_hientset_t * destination, exd_hientset_t * source);

void exd_hientset_set_slot(exd_hientset_t * ents, exd_entity_t slot);
void exd_hientset_clear_slot(exd_hientset_t * ents, exd_entity_t slot);

void exd_hientset_and(exd_hientset_t * destination, exd_hientset_t * source);
void exd_hientset_or(exd_hientset_t * destination, exd_hientset_t * source);
void exd_hientset_not(exd_hientset_t * destination, exd_hientset_t * source);

bool exd_hientset_slot_is_set(exd_hientset_t * ents, exd_entity_t slot);
bool exd_hientset_slot_is_not_set(exd_hientset_t * ents, exd_entity_t slot);

//===================
//     Iterator
//===================

typedef struct exd_hientset_iter
{
	exd_hientset_t * entset;
	u32 current_idx;
}
exd_hientset_iter_t;

u32 exd_hientset_iter_next(exd_hientset_iter_t * it);
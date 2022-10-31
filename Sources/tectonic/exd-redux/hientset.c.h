#include <string.h>
#include "hientset.h"

//==========================
//Bit block this entity fell into
//==========================
static inline u32 layer_idx(exd_entity_t id, u32 shift)
{
	// Note: "pow2_divide" is equivalent to
	// entity_id / entset_bitwidth, entset_bitwidth is likely 32bits so
	// entity_id / 32, which calculates the array index that our entity falls into

	// Using "pow2_divide" is significantly faster in debug builds, but makes no difference in release
	return exd_math_pow2_divide(exd_entity_extract_id(id), shift);
}
//Note: Layer0 index is always 0...there is no array here actually
static inline u32 layer0_idx(exd_entity_t id) { return layer_idx(id, EXD_HIENTSET_LAYER0_SHIFT); }
static inline u32 layer1_idx(exd_entity_t id) { return layer_idx(id, EXD_HIENTSET_LAYER1_SHIFT); }
static inline u32 layer2_idx(exd_entity_t id) { return layer_idx(id, EXD_HIENTSET_LAYER2_SHIFT); }
static inline u32 layer3_idx(exd_entity_t id) { return layer_idx(id, EXD_HIENTSET_LAYER3_SHIFT); }

//==========================
//Position in bit block containing the entity
//==========================
static inline u32 layer_mask(exd_entity_t id, u32 shift)
{
	// Note: "pow2_modulo" is equivalent to
	// entity_id % entset_bitwidth, entset_bitwidth is likely 32bits so
	// entity_id % 32, which calculates the remainder of the block size and therefore
	// how offset into the 32 bit integer we are

	// Using "pow2_modulo" is significantly faster in debug builds, but makes no difference in release
	u8 offset_in_block = exd_math_pow2_modulo(exd_entity_extract_id(id), shift);
	u32 slot_mask = exd_bits32_rotate_left(1, offset_in_block);
	return slot_mask;
}
static inline u32 layer0_mask(exd_entity_t id) { return layer_mask(id, EXD_HIENTSET_LAYER0_SHIFT); }
static inline u32 layer1_mask(exd_entity_t id) { return layer_mask(id, EXD_HIENTSET_LAYER1_SHIFT); }
static inline u32 layer2_mask(exd_entity_t id) { return layer_mask(id, EXD_HIENTSET_LAYER2_SHIFT); }
static inline u32 layer3_mask(exd_entity_t id) { return layer_mask(id, EXD_HIENTSET_LAYER3_SHIFT); }

//==========================
//Layer contains id or not
//==========================
static inline bool layer0_has(exd_hientset_t * ents, exd_entity_t id)
{
	return (ents->layer0[layer0_idx(id)] & layer0_mask(id)); 
}
static inline bool layer1_has(exd_hientset_t * ents, exd_entity_t id)
{
	return (ents->layer1[layer1_idx(id)] & layer1_mask(id)); 
}
static inline bool layer2_has(exd_hientset_t * ents, exd_entity_t id)
{
	return (ents->layer2[layer2_idx(id)] & layer2_mask(id)); 
}
static inline bool layer3_has(exd_hientset_t * ents, exd_entity_t id)
{
	return (ents->layer3 & layer3_mask(id)); 
}

//==========================
//Clear layer slots
//==========================
static inline void clear_slot(u32 * bitset, size_t idx, u32 mask)
{
	bitset[idx] &= ~mask;
}

static inline void clear_slot_layer0(exd_hientset_t * ents, exd_entity_t id)
{
	u32 mask = layer0_mask(id);
	u32 idx = layer0_idx(id);
	clear_slot(ents->layer0, idx, mask);
}

//Note: Clearing slots is not this simple, and involves a series of checks against all slots
//In order to properly and safely clear the summary layers

// static inline void clear_slot_layer1(exd_hientset_t * ents, exd_entity_t id)
// {
// 	u32 mask = layer1_mask(id);
// 	u32 idx = layer1_idx(id);
// 	clear_slot(ents->layer1, idx, mask);
// }
// static inline void clear_slot_layer2(exd_hientset_t * ents, exd_entity_t id)
// {
// 	u32 mask = layer2_mask(id);
// 	u32 idx = layer2_idx(id);
// 	clear_slot(ents->layer2, idx, mask);
// }
// static inline void clear_slot_layer3(exd_hientset_t * ents, exd_entity_t id)
// {
// 	u32 mask = layer3_mask(id);
// 	//Note: Layer 3 is not an array, just a single u32
// 	clear_slot(&ents->layer3, 0, mask);
// }

//==========================
//Set layer slots
//==========================
static inline void set_slot(u32 * bitset, size_t idx, u32 mask)
{
	bitset[idx] |= mask;
}
static inline void set_slot_layer0(exd_hientset_t * ents, exd_entity_t id)
{
	u32 mask = layer0_mask(id);
	u32 idx = layer0_idx(id);
	set_slot(ents->layer0, idx, mask);
}
static inline void set_slot_layer1(exd_hientset_t * ents, exd_entity_t id)
{
	u32 mask = layer1_mask(id);
	u32 idx = layer1_idx(id);
	set_slot(ents->layer1, idx, mask);
}
static inline void set_slot_layer2(exd_hientset_t * ents, exd_entity_t id)
{
	u32 mask = layer2_mask(id);
	u32 idx = layer2_idx(id);
	set_slot(ents->layer2, idx, mask);
}
static inline void set_slot_layer3(exd_hientset_t * ents, exd_entity_t id)
{
	u32 mask = layer3_mask(id);
	//Note: Layer3 is just a single value, not an array
	set_slot(&ents->layer3, 0, mask);
}





//==================================
//Now, actually provide user facing functions
//==================================

void exd_hientset_init(allocator_t * mem, exd_hientset_t * ents)
{
	ents->layer3 = 0;
	ents->layer2 = allocator_malloc(mem, u32, EXD_HIENTSET_LAYER2_SIZE); 
	ents->layer1 = allocator_malloc(mem, u32, EXD_HIENTSET_LAYER1_SIZE); 
	ents->layer0 = allocator_malloc(mem, u32, EXD_HIENTSET_LAYER0_SIZE);

	memset(ents->layer2, 0, sizeof(u32) * sizeof(EXD_HIENTSET_LAYER2_SIZE));
	memset(ents->layer1, 0, sizeof(u32) * sizeof(EXD_HIENTSET_LAYER1_SIZE));
	memset(ents->layer0, 0, sizeof(u32) * sizeof(EXD_HIENTSET_LAYER0_SIZE));

}

void exd_hientset_copy_data_from(exd_hientset_t * destination, exd_hientset_t * source)
{
	destination->layer3 = source->layer3;
	memcpy(destination->layer2, source->layer2, sizeof(u32) * sizeof(EXD_HIENTSET_LAYER2_SIZE));
	memcpy(destination->layer1, source->layer1, sizeof(u32) * sizeof(EXD_HIENTSET_LAYER1_SIZE));
	memcpy(destination->layer0, source->layer0, sizeof(u32) * sizeof(EXD_HIENTSET_LAYER0_SIZE));
}

void exd_hientset_set_slot(exd_hientset_t * ents, exd_entity_t slot)
{
	set_slot_layer0(ents, slot);
	set_slot_layer1(ents, slot);
	set_slot_layer2(ents, slot);
	set_slot_layer3(ents, slot);
}

void exd_hientset_clear_slot(exd_hientset_t * ents, exd_entity_t slot)
{
	// clear_slot_layer0(ents, slot);
	// if (ents->layer0[layer0_idx(slot)] == 0)
	// {
	// 	ents->layer1[layer1_idx(slot)] &= ~layer1_mask(slot);
	// }
	// if (ents->layer1[layer1_idx(slot)] == 0)
	// {
	// 	ents->layer2[layer2_idx(slot)] &= ~layer2_mask(slot);
	// }
	// if (ents->layer2[layer2_idx(slot)] == 0)
	// {
	// 	ents->layer3 &= ~layer3_mask(slot);
	// }


	//Attempt at a branchless clear
	clear_slot_layer0(ents, slot);

	u32 state = ents->layer0[layer0_idx(slot)];
	ents->layer1[layer1_idx(slot)] &= ~(layer1_mask(slot) * (state > 0));

	state = ents->layer1[layer1_idx(slot)];
	ents->layer2[layer2_idx(slot)] &= ~(layer2_mask(slot) * (state > 0));

	state = ents->layer2[layer2_idx(slot)];
	ents->layer3 &= ~(layer3_mask(slot) * (state > 0));

}

void exd_hientset_and(exd_hientset_t * destination, exd_hientset_t * source)
{
	exd_for_range_var(i, EXD_HIENTSET_LAYER0_SIZE)
	{
		destination->layer0[i] &= source->layer0[i];
	}
	exd_for_range_var(i, EXD_HIENTSET_LAYER1_SIZE)
	{
		destination->layer1[i] &= source->layer1[i];
	}
	exd_for_range_var(i, EXD_HIENTSET_LAYER2_SIZE)
	{
		destination->layer2[i] &= source->layer2[i];
	}
	destination->layer3 &= source->layer3;
}

void exd_hientset_not(exd_hientset_t * destination, exd_hientset_t * source)
{
	exd_for_range_var(i, EXD_HIENTSET_LAYER0_SIZE)
	{
		destination->layer0[i] &= ~(source->layer0[i]);
	}
	exd_for_range_var(i, EXD_HIENTSET_LAYER1_SIZE)
	{
		destination->layer1[i] &= ~(source->layer1[i]);
	}
	exd_for_range_var(i, EXD_HIENTSET_LAYER2_SIZE)
	{
		destination->layer2[i] &= ~(source->layer2[i]);
	}
	destination->layer3 &= ~(source->layer3);
}

bool exd_hientset_slot_is_set(exd_hientset_t * ents, exd_entity_t slot)
{
	return layer0_has(ents, slot);
}

bool exd_hientset_slot_is_not_set(exd_hientset_t * ents, exd_entity_t slot)
{
	return !layer0_has(ents, slot);
}

//===================
//     Iterator
//===================
u32 exd_hientset_iter_next(exd_hientset_iter_t * it)
{
	while (!layer3_has(it->entset, it->current_idx) && it->current_idx < EXD_HIENTSET_LAYER3_SIZE)
	{
		it->current_idx += EXD_HIENTSET_LAYER3_ITER_ADVANCE;
	}
	while (!layer2_has(it->entset, it->current_idx) && it->current_idx < EXD_HIENTSET_LAYER2_SIZE)
	{
		it->current_idx += EXD_HIENTSET_LAYER2_ITER_ADVANCE;
	}
	while (!layer1_has(it->entset, it->current_idx) && it->current_idx < EXD_HIENTSET_LAYER1_SIZE)
	{
		it->current_idx += EXD_HIENTSET_LAYER1_ITER_ADVANCE;
	}
	while (!layer0_has(it->entset, it->current_idx) && it->current_idx < EXD_HIENTSET_LAYER0_SIZE)
	{
		it->current_idx += EXD_HIENTSET_LAYER0_ITER_ADVANCE;
	}

	u32 entity_idx = it->current_idx;
	++it->current_idx;

	return entity_idx;
}

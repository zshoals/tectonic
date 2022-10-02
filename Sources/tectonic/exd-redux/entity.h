
#pragma once

#include "exd-config.h"

#include "exd-common.h"
#include "bits.h"

typedef u64 exd_entity_t;

#define EXD_INVALID_ENTITY 0

#define EXD_ID_BITS (1 << EXD_ID_SHIFT)

#define EXD_ID_MASK (EXD_ID_BITS - 1)

static inline u64 exd_entity_extract_id(exd_entity_t ent) { return exd_bits64_extract_lower_bits(ent, EXD_ID_SHIFT); }
static inline u64 exd_entity_extract_generation(exd_entity_t ent) { return exd_bits64_extract_upper_bits(ent, EXD_ID_SHIFT); }

static inline exd_entity_t exd_entity_increment_generation(exd_entity_t ent) { return exd_bits64_increment_upper(ent, EXD_ID_SHIFT); }
static inline exd_entity_t exd_entity_reset_generation(exd_entity_t ent) { return exd_bits64_set_upper(ent, 0, EXD_ID_SHIFT); }

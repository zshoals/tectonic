#pragma once

#include <stdbool.h>
#include "kinc/math/matrix.h"
#include "kinc/graphics4/constantlocation.h"
#include "kinc/graphics4/textureunit.h"
#include "../assets/assets_references.h"

typedef struct tec_assets_storage tec_assets_storage_t;
typedef struct kinc_g4_pipeline kinc_g4_pipeline_t;
typedef struct kinc_g4_texture kinc_g4_texture_t;
typedef struct tec_pipeline_data tec_pipeline_data_t;

typedef enum
{
	TEC_UNIFORM_TYPE_NULL, //No uniform, no need to do anything

	TEC_UNIFORM_TYPE_BOOL,

	TEC_UNIFORM_TYPE_FLOAT,
	TEC_UNIFORM_TYPE_FLOAT2,
	TEC_UNIFORM_TYPE_FLOAT3,
	TEC_UNIFORM_TYPE_FLOAT4,
	//TEC_UNIFORM_TYPE_FLOATS, //No support yet? From my end, that is.

	TEC_UNIFORM_TYPE_INT,
	TEC_UNIFORM_TYPE_INT2,
	TEC_UNIFORM_TYPE_INT3,
	TEC_UNIFORM_TYPE_INT4,
	//TEC_UNIFORM_TYPE_INTS, //No support yet?

	TEC_UNIFORM_TYPE_MAT3,
	TEC_UNIFORM_TYPE_MAT4,
}
tec_material_uniform_type_e;

typedef enum
{
	TEC_TEX_UNIT_SLOT_0,
	TEC_TEX_UNIT_SLOT_1,
	TEC_TEX_UNIT_SLOT_2,
	TEC_TEX_UNIT_SLOT_3,
	TEC_TEX_UNIT_SLOT_4,
	TEC_TEX_UNIT_SLOT_5,
	TEC_TEX_UNIT_SLOT_6,
	TEC_TEX_UNIT_SLOT_7,
}
tec_material_tex_unit_slot_e;

typedef enum
{
	TEC_UNIFORM_SLOT_0,
	TEC_UNIFORM_SLOT_1,
	TEC_UNIFORM_SLOT_2,
	TEC_UNIFORM_SLOT_3,
	TEC_UNIFORM_SLOT_4,
	TEC_UNIFORM_SLOT_5,
	TEC_UNIFORM_SLOT_6,
	TEC_UNIFORM_SLOT_7,
	TEC_UNIFORM_SLOT_8,
	TEC_UNIFORM_SLOT_9,
	TEC_UNIFORM_SLOT_10,
	TEC_UNIFORM_SLOT_11,
	TEC_UNIFORM_SLOT_12,
	TEC_UNIFORM_SLOT_13,
	TEC_UNIFORM_SLOT_14,
	TEC_UNIFORM_SLOT_15,
}
tec_material_uniform_slot_e;

typedef enum
{
	TEC_TEXTURE_NULL,
	TEC_TEXTURE_PRESENT,
} 
tec_material_texture_presence_e;

//Note: The expectation for the uniform name at this time is that it's set via string literal, not extracted from a file
typedef union
tec_material_uniform_data
{
	kinc_matrix4x4_t mat4_value;
	kinc_matrix3x3_t mat3_value;
	int int_values[4];
	float float_values[4];
	bool bool_value;
}
tec_material_uniform_data_u;

typedef struct
tec_material_uniform
{
	tec_material_uniform_data_u data;
	char const * name;
	kinc_g4_constant_location_t location;
	tec_material_uniform_type_e type;
}
tec_material_uniform_t;

#define TEC_MATERIAL_MAX_TEXTURE_UNITS 8
#define TEC_MATERIAL_MAX_UNIFORMS 16

typedef struct
tec_material_texture_data
{
	kinc_g4_texture_unit_t texture_units[TEC_MATERIAL_MAX_TEXTURE_UNITS]; //Can theoretically support more, but no thanks
	kinc_g4_texture_t * textures[TEC_MATERIAL_MAX_TEXTURE_UNITS];
	tec_material_texture_presence_e present[TEC_MATERIAL_MAX_TEXTURE_UNITS];
}
tec_material_texture_data_t;

typedef struct
tec_material_material
{
	char const * name;
	tec_material_texture_data_t tex_data;
	tec_pipeline_data_t * pipeline;
	//This should be a bfstack too
	tec_material_uniform_t uniforms[TEC_MATERIAL_MAX_UNIFORMS]; //Same as above
}
tec_material_t;

tec_assref_material_t tec_material_create_material(tec_assets_storage_t * assets, char const * name, tec_assref_shader_program_t pipeline);
tec_assref_material_t tec_material_create_material_by_copy(tec_assets_storage_t * assets, char const * name, tec_assref_material_t original_material);
void tec_material_assign_texture(tec_assets_storage_t * assets, tec_assref_material_t mat, char const * tex_unit_name, tec_assref_texture_t tex, tec_material_tex_unit_slot_e slot);
void tec_material_assign_uniform
(
	tec_assets_storage_t * assets, 
	tec_assref_material_t mat, 
	char const * uniform_name, 
	tec_material_uniform_data_u data, 
	tec_material_uniform_type_e type, 
	tec_material_uniform_slot_e slot
);
void tec_material_update_uniform(tec_assets_storage_t * assets, tec_assref_material_t mat, char const * uniform_name, tec_material_uniform_data_u data);
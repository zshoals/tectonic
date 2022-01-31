#pragma once

#include <stdbool.h>
#include "kinc/math/matrix.h"
#include "kinc/graphics4/pipeline.h"
#include "kinc/graphics4/texture.h"

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
	TEC_TEXTURE_NULL,
	TEC_TEXTURE_PRESENT,
} tec_material_texture_presence_e;

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
	kinc_g4_texture_t textures[TEC_MATERIAL_MAX_TEXTURE_UNITS];
	tec_material_texture_presence_e present[TEC_MATERIAL_MAX_TEXTURE_UNITS];
}
tec_material_texture_data_t;

typedef struct
tec_material_material
{
	char const * name;
	tec_material_texture_data_t tex_data;
	kinc_g4_pipeline_t pipeline;
	tec_material_uniform_t uniforms[TEC_MATERIAL_MAX_UNIFORMS]; //Same as above
}
tec_material_material_t;

void tec_material_initialize(tec_material_material_t * mat, char const * name, kinc_g4_pipeline_t pipeline);
//Currently, materials can only be assigned. Trying to null them or something will be bad news. Don't try it.
void tec_material_assign_texture(tec_material_material_t * mat, kinc_g4_texture_t texture, size_t slot);
void tec_material_assign_uniform(tec_material_material_t * mat, char const * name, tec_material_uniform_data_u data, tec_material_uniform_type_e type, size_t slot);
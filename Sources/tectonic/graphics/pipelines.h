#pragma once

#include "kinc/graphics4/pipeline.h"
#include "kinc/graphics4/vertexbuffer.h"
#include "kinc/graphics4/vertexstructure.h"
#include "kinc/graphics4/shader.h"
#include "../util/memkit.h"
#include "../assets/assets_references.h"

typedef struct tec_assets_storage tec_assets_storage_t;

//typedef struct tec_assets_storage tec_assets_storage_t;

/*! default hardcoded shader pipelines with various blending modes.
We don't really need that much, so hardcoding it is the simply and obvious solution.
*/

typedef struct
tec_vertex_shader
{
	tec_byte_t data[TEC_KILOBYTES(256)];
	kinc_g4_shader_t vert;
	size_t data_length;
	char const * name;
}
tec_vertex_shader_t;

typedef struct
tec_fragment_shader
{
	tec_byte_t data[TEC_KILOBYTES(256)];
	kinc_g4_shader_t frag;
	size_t data_length;
	char const * name;
}
tec_fragment_shader_t;

typedef enum
{
	TEC_VERT_TEXTURED,
}
tec_pipelines_vertex_programs_e;

typedef enum
{
	TEC_FRAG_TEXTURED,
}
tec_pipelines_fragment_programs_e;

typedef enum
{
	TEC_BLENDING_DISABLED,
	//Normal assumes you are using a shader with premultiplied alpha
	TEC_BLENDING_NORMAL,
	TEC_BLENDING_ADD,
	TEC_BLENDING_MULTIPLY,
	//I have no idea what this blend mode is, but it causes the underlying image to only be drawn to non-fully-transparent regions in the image posted above it
	//Very useful for imitating lighting by putting a "lighting" layer UNDER the draw layer
	TEC_BLENDING_MASK_WITH_COLOR,
	TEC_BLENDING_MASK,
}
tec_pipeline_blending_e;

typedef struct
tec_pipeline_data
{
	char const * name;
	kinc_g4_vertex_structure_t vertex_structure;
	kinc_g4_pipeline_t pipeline;
}
tec_pipeline_data_t;

tec_assref_shader_program_t tec_pipeline_create_program
(
	tec_assets_storage_t * assets,
	char const * name, 
	tec_assref_vertex_shader_t vert, 
	tec_assref_fragment_shader_t frag, 
	kinc_g4_vertex_structure_t vs, 
	tec_pipeline_blending_e blend_mode
);
void tec_pipeline_compile_program(tec_assets_storage_t * assets, tec_assref_shader_program_t program);





void tec_internal_pipeline_blend_mode_helper(kinc_g4_pipeline_t * pipeline, tec_pipeline_blending_e blending_mode);
void tec_internal_pipeline_initialize_fragment_shader(tec_fragment_shader_t * frag, char const * name, tec_byte_t * copy_from, size_t data_length);
void tec_internal_pipeline_initialize_vertex_shader(tec_vertex_shader_t * vert, char const * name, tec_byte_t * copy_from, size_t data_length);
void tec_internal_pipeline_compile_fragment_shader(tec_fragment_shader_t * frag);
void tec_internal_pipeline_compile_vertex_shader(tec_vertex_shader_t * vert);
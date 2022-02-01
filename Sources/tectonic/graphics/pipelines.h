#pragma once

#include "material.h"
#include "kinc/graphics4/pipeline.h"
#include "kinc/graphics4/vertexbuffer.h"
#include "kinc/graphics4/vertexstructure.h"
#include "../util/memkit.h"

/*! default hardcoded shader pipelines with various blending modes.
We don't really need that much, so hardcoding it is the simply and obvious solution.
*/

typedef struct
tec_vertex_shader
{
	tec_byte_t bytes[TEC_KILOBYTES(256)];
	char const * name;
}
tec_vertex_shader_t;

typedef struct
tec_fragment_shader
{
	tec_byte_t bytes[TEC_KILOBYTES(256)];
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

#define TEC_MAX_SHADERS 16

#define template_type tec_vertex_shader_t
#define template_array_size TEC_MAX_SHADERS
#define template_searchable
#include "../ds/bfstack.h"

#define template_type tec_fragment_shader_t
#define template_array_size TEC_MAX_SHADERS
#define template_searchable
#include "../ds/bfstack.h"

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


kinc_g4_pipeline_t tec_pipeline_create_defaults(void);
void tec_pipeline_blend_mode_helper(kinc_g4_pipeline_t * pipeline, tec_pipeline_blending_e blending_mode);
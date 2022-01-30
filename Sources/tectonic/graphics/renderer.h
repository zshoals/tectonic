#pragma once

#include "kinc/graphics4/graphics.h"
#include "kinc/graphics4/vertexbuffer.h"
#include "kinc/graphics4/indexbuffer.h"
#include "kinc/graphics4/pipeline.h"
#include "kinc/graphics4/texture.h"
#include "kinc/math/matrix.h"
#include "../util/string.h"
#include <stdbool.h>

typedef enum 
{
	TEC_RENDERER_CONTINUE_DRAW,
	TEC_RENDERER_DRAW_THEN_SWAP_BUFFER,
}
tec_renderer_draw_mode_e;

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
tec_renderer_uniform_type_e;

typedef enum
{
	TEC_TEXTURE_NULL,
	TEC_TEXTURE_PRESENT,
} tec_renderer_texture_presence_e;

//Note: The expectation for the uniform name at this time is that it's set via string literal, not extracted from a file
typedef struct
tec_renderer_uniform
{
	union {
		kinc_matrix4x4_t mat4_value;
		kinc_matrix3x3_t mat3_value;
		int int_values[4];
		float float_values[4];
		bool bool_value;
	};
	char const * name;
	kinc_g4_constant_location_t location;
	tec_renderer_uniform_type_e type;
}
tec_renderer_uniform_t;


//RECTS
//VBO
//	From - To count for verts
//IBO
//	From - to count ?
//Draw target/render target
//Active Texture
//Compiled Pipeline
//	Unique name/identifier
//	associated uniforms
#define TEC_RENDERER_MAX_TEXTURE_UNITS 8
#define TEC_RENDERER_MAX_UNIFORMS 16

typedef struct
tec_renderer_texture_data
{
	kinc_g4_texture_unit_t texture_units[TEC_RENDERER_MAX_TEXTURE_UNITS]; //Can theoretically support more, but no thanks
	kinc_g4_texture_t textures[TEC_RENDERER_MAX_TEXTURE_UNITS];
	tec_renderer_texture_presence_e present[TEC_RENDERER_MAX_TEXTURE_UNITS];
}
tec_renderer_texture_data_t;

typedef struct
tec_renderer_material
{
	char const * name;
	tec_renderer_texture_data_t tex_data;
	kinc_g4_pipeline_t pipeline;
	tec_renderer_uniform_t uniforms[TEC_RENDERER_MAX_UNIFORMS]; //Same as above
}
tec_renderer_material_t;

typedef struct
tec_renderer_context
{
	kinc_g4_vertex_buffer_t vbo;
	size_t vbo_offset;

	kinc_g4_index_buffer_t ibo;
	size_t ibo_offset;

	size_t requested_draw_count;

	//Handle NULL special case, as the framebuffer can't be drawn to directly this way
	kinc_g4_render_target_t * surface;
	//All materials need to be stored in the heap somewhere, this should probably be a pointer
	tec_renderer_material_t * material;
}
tec_renderer_context_t;


//This thing should be as dumb as possible
//It will probably handle compositing all rendertargets...I think
//G2 will handle organizing and submitting all necessary draw calls for this thing to draw

//Cache the previous graphics state so that we can see if things changed
//if they did, swap pipelines and everything
//then draw
//state is implied by properly created sort keys?

void tec_renderer_draw(tec_renderer_context_t context, tec_renderer_draw_mode_e draw_mode);
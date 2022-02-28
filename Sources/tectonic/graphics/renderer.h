#pragma once

#include "kinc/graphics4/vertexbuffer.h"
#include "kinc/graphics4/indexbuffer.h"
#include "material.h"

typedef struct kinc_g4_render_target kinc_g4_render_target_t;

typedef enum 
{
	TEC_RENDERER_CONTINUE_DRAW,
	TEC_RENDERER_DRAW_THEN_SWAP_BUFFER,
}
tec_renderer_draw_mode_e;

typedef struct
tec_renderer_context
{
	kinc_g4_vertex_buffer_t vbo_textured;
	kinc_g4_vertex_buffer_t vbo_lightmap;
	size_t vbo_textured_offset;
	size_t vbo_lightmap_offset;
	float * v_textured_data;
	float * v_lightmap_data;

	kinc_g4_index_buffer_t ibo_textured;
	kinc_g4_index_buffer_t ibo_lightmap;
	size_t ibo_textured_offset;
	size_t ibo_lightmap_offset;
	float * i_textured_data;
	float * i_lightmap_data;

	size_t requested_draw_count;

	//Handle NULL special case, as the framebuffer can't be drawn to directly this way
	kinc_g4_render_target_t * surface;
	//All materials need to be stored in the heap somewhere, this should probably be a pointer
	tec_material_t * material;
}
tec_renderer_context_t;


//This thing should be as dumb as possible
//It will probably handle compositing all rendertargets...I think
//G2 will handle organizing and submitting all necessary draw calls for this thing to draw

//Cache the previous graphics state so that we can see if things changed
//if they did, swap pipelines and everything
//then draw
//state is implied by properly created sort keys?

//We should have an array of VBOs. One gets pushed whenever there is a new vertex structure
void renderer_create_and_cache_new_vbo(void);
void tec_renderer_draw(tec_renderer_context_t * context);
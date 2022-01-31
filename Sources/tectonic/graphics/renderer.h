#pragma once

#include "kinc/graphics4/vertexbuffer.h"
#include "kinc/graphics4/indexbuffer.h"
#include "material.h"

typedef enum 
{
	TEC_RENDERER_CONTINUE_DRAW,
	TEC_RENDERER_DRAW_THEN_SWAP_BUFFER,
}
tec_renderer_draw_mode_e;

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
	tec_material_material_t * material;
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
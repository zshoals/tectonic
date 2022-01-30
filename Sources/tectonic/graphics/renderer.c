#include "renderer.h"
#include "kinc/graphics4/graphics.h"
#include "../debug/log.h"
#include "assert.h"

void tec_renderer_draw(tec_renderer_context_t ctx, tec_renderer_draw_mode_e draw_mode)
{
	//We don't kinc_begin(0) here...it needs to be somewhere else...g2?
	//This one looks dangerous, uses multi targets?
	kinc_g4_set_render_targets(&ctx.surface, 1);
	kinc_g4_set_pipeline(&ctx.material->pipeline);
	//Need to set appropriate uniforms somehow
	//kinc_g4_set_mat3 etc.
	kinc_g4_set_vertex_buffer(&ctx.vbo);
	kinc_g4_set_index_buffer(&ctx.ibo);
	//Need to figure out how to determine what textures need to be used
	kinc_g4_set_texture(ctx.material->texture_units[0], &ctx.material->textures[0]);
	//Mag filter needs set up in the context
	kinc_g4_set_texture_magnification_filter(ctx.material->texture_units[0], KINC_G4_MIPMAP_FILTER_POINT);
	kinc_g4_draw_indexed_vertices_from_to(ctx.ibo_offset, ctx.requested_draw_count);
	
	switch (draw_mode)
	{
		case TEC_RENDERER_CONTINUE_DRAW:
			//Do nothing, we still have to draw
			break;
		case TEC_RENDERER_DRAW_THEN_SWAP_BUFFER:
			//We're done, swap the buffers and end
			kinc_g4_swap_buffers();
			kinc_g4_end(0);
		default:
			assert(0 && "Somehow reached the default case in tec_renderer draw, should not be possible");
			break;
	}
}
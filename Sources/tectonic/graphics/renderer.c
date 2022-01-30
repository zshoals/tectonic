#include "renderer.h"
#include "kinc/graphics4/graphics.h"
#include "../debug/log.h"
#include "assert.h"
#include "../frequent.h"

local_func void
renderer_assign_uniforms(tec_renderer_material_t * mat)
{
	for (int i = 0; i < TEC_RENDERER_MAX_UNIFORMS; i++)
	{
		tec_renderer_uniform_t * uniform = &mat->uniforms[i];
		switch (uniform->type)
		{
			//BASIC===========================
			//================================
			case TEC_UNIFORM_TYPE_NULL:
				//We have nothing to set, skip it.
				break;

			case TEC_UNIFORM_TYPE_BOOL:
				kinc_g4_set_bool(uniform->location, uniform->bool_value);
				break;
			//FLOATS==========================
			//================================
			case TEC_UNIFORM_TYPE_FLOAT:
				kinc_g4_set_float
				(
					uniform->location, 
					uniform->float_values[0]
				);
				break;

			case TEC_UNIFORM_TYPE_FLOAT2:
				kinc_g4_set_float2
				(
					uniform->location, 
					uniform->float_values[0], 
					uniform->float_values[1]
				);
				break;

			case TEC_UNIFORM_TYPE_FLOAT3:
				kinc_g4_set_float3
				(
					uniform->location, 
					uniform->float_values[0], 
					uniform->float_values[1],
					uniform->float_values[2]
				);
				break;

			case TEC_UNIFORM_TYPE_FLOAT4:
				kinc_g4_set_float4
				(
					uniform->location, 
					uniform->float_values[0], 
					uniform->float_values[1], 
					uniform->float_values[2], 
					uniform->float_values[3]
				);
				break;

			//INTS============================
			//================================
			case TEC_UNIFORM_TYPE_INT:
				kinc_g4_set_int
				(
					uniform->location, 
					uniform->int_values[0]
				);
				break;

			case TEC_UNIFORM_TYPE_INT2:
				kinc_g4_set_int2
				(
					uniform->location, 
					uniform->int_values[0], 
					uniform->int_values[1]
				);
				break;

			case TEC_UNIFORM_TYPE_INT3:
				kinc_g4_set_int3
				(
					uniform->location, 
					uniform->int_values[0], 
					uniform->int_values[1], 
					uniform->int_values[2]
				);
				break;

			case TEC_UNIFORM_TYPE_INT4:
				kinc_g4_set_int4
				(
					uniform->location, 
					uniform->int_values[0], 
					uniform->int_values[1], 
					uniform->int_values[2], 
					uniform->int_values[3]
				);
				break;
			//MATRIX==========================
			//================================
			case TEC_UNIFORM_TYPE_MAT3:
				kinc_g4_set_matrix3
				(
					uniform->location,
					&uniform->mat3_value
				);
				break;

			case TEC_UNIFORM_TYPE_MAT4:
				kinc_g4_set_matrix4
				(
					uniform->location,
					&uniform->mat4_value
				);
				break;

			default:
				assert(0 && "We should never hit the default in assign_uniforms (renderer)");
				break;
		}
	}
}

void 
tec_renderer_draw(tec_renderer_context_t * ctx, tec_renderer_draw_mode_e draw_mode)
{
	//We don't kinc_begin(0) here...it needs to be somewhere else...g2?
	//This one looks dangerous, uses multi targets?
	if (ctx->surface == NULL)
	{
		//No surface present in the context means that we want to draw to the framebuffer
		kinc_g4_restore_render_target(); 
	}
	else
	{
		//Set the appropriate render target to draw to that the context requests
		kinc_g4_set_render_targets(&ctx->surface, 1);
	}

	kinc_g4_set_pipeline(&ctx->material->pipeline);
	renderer_assign_uniforms(ctx->material);
	kinc_g4_set_vertex_buffer(&ctx->vbo);
	kinc_g4_set_index_buffer(&ctx->ibo);

	//Apply textures to all required texture units
	for (int i = 0; i < TEC_RENDERER_MAX_TEXTURE_UNITS; i++)
	{
		tec_renderer_texture_data_t * data = &ctx->material->tex_data;
		if (data->present[i] == TEC_TEXTURE_PRESENT)
		{
			kinc_g4_set_texture(ctx->material->tex_data.texture_units[i], &ctx->material->tex_data.textures[i]);
		}
	}

	//Mag filter needs set up in the context, maybe needs hashed also
	kinc_g4_set_texture_magnification_filter(ctx->material->tex_data.texture_units[0], KINC_G4_MIPMAP_FILTER_POINT);
	kinc_g4_draw_indexed_vertices_from_to(ctx->ibo_offset, ctx->requested_draw_count);
	
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
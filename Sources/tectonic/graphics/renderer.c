#include "renderer.h"
#include "kinc/graphics4/graphics.h"
#include "../debug/log.h"
#include "assert.h"
#include "../frequent.h"
#include "material.h"
#include "pipelines.h"
#include "texture.h"

local_func void
renderer_assign_uniforms(tec_material_t * mat)
{
	for (int i = 0; i < TEC_MATERIAL_MAX_UNIFORMS; i++)
	{
		tec_material_uniform_t * uniform = &mat->uniforms[i];
		switch (uniform->type)
		{
			//BASIC===========================
			//================================
			case TEC_UNIFORM_TYPE_NULL:
				//We have nothing to set, skip it.
				break;

			case TEC_UNIFORM_TYPE_BOOL:
				kinc_g4_set_bool(uniform->location, uniform->data.bool_value);
				break;

			//FLOATS==========================
			//================================
			case TEC_UNIFORM_TYPE_FLOAT:
				kinc_g4_set_float
				(
					uniform->location, 
					uniform->data.float_values[0]
				);
				break;

			case TEC_UNIFORM_TYPE_FLOAT2:
				kinc_g4_set_float2
				(
					uniform->location, 
					uniform->data.float_values[0], 
					uniform->data.float_values[1]
				);
				break;

			case TEC_UNIFORM_TYPE_FLOAT3:
				kinc_g4_set_float3
				(
					uniform->location, 
					uniform->data.float_values[0], 
					uniform->data.float_values[1],
					uniform->data.float_values[2]
				);
				break;

			case TEC_UNIFORM_TYPE_FLOAT4:
				kinc_g4_set_float4
				(
					uniform->location, 
					uniform->data.float_values[0], 
					uniform->data.float_values[1], 
					uniform->data.float_values[2], 
					uniform->data.float_values[3]
				);
				break;

			//INTS============================
			//================================
			case TEC_UNIFORM_TYPE_INT:
				kinc_g4_set_int
				(
					uniform->location, 
					uniform->data.int_values[0]
				);
				break;

			case TEC_UNIFORM_TYPE_INT2:
				kinc_g4_set_int2
				(
					uniform->location, 
					uniform->data.int_values[0], 
					uniform->data.int_values[1]
				);
				break;

			case TEC_UNIFORM_TYPE_INT3:
				kinc_g4_set_int3
				(
					uniform->location, 
					uniform->data.int_values[0], 
					uniform->data.int_values[1], 
					uniform->data.int_values[2]
				);
				break;

			case TEC_UNIFORM_TYPE_INT4:
				kinc_g4_set_int4
				(
					uniform->location, 
					uniform->data.int_values[0], 
					uniform->data.int_values[1], 
					uniform->data.int_values[2], 
					uniform->data.int_values[3]
				);
				break;
				
			//MATRIX==========================
			//================================
			case TEC_UNIFORM_TYPE_MAT3:
				kinc_g4_set_matrix3
				(
					uniform->location,
					&uniform->data.mat3_value
				);
				break;

			case TEC_UNIFORM_TYPE_MAT4:
				kinc_g4_set_matrix4
				(
					uniform->location,
					&uniform->data.mat4_value
				);
				break;

			default:
				assert(0 && "We should never hit the default in assign_uniforms (renderer)");
				break;
		}
	}
}

// typedef struct
// tec_internal_renderer_context_cache
// {
// 	kinc_g4_vertex_buffer_t * cached_vbo;
// 	kinc_g4_index_buffer_t * cached_ibo;
// 	kinc_g4_render_target_t * cached_surface;
// 	tec_material_t * cached_material;
// }
// tec_internal_renderer_context_cache_t;

// local_data tec_internal_renderer_context_cache_t render_cache = {0};

// void
// cache_vbo_location(kinc_g4_vertex_buffer_t * vbo)
// {
// 	render_cache.cached_vbo = vbo;
// }

// void
// cache_ibo_location(kinc_g4_index_buffer_t * ibo)
// {
// 	render_cache.cached_ibo = ibo;
// }

// void
// cache_surface_location(kinc_g4_render_target_t * surface)
// {
// 	render_cache.cached_surface = surface;
// }

// void
// cache_material_location(tec_material_t * mat)
// {
// 	render_cache.cached_material = mat;
// }

void 
tec_renderer_draw(tec_renderer_context_t * ctx, tec_renderer_draw_mode_e draw_mode)
{
	//Forget the caching for a moment
	/*
		setpipeline
		settexture, just do 0 for now
		assign uniforms
		
		EVENTUALLY, handle rendertarget switching

		assign VBO
		assign IBO

		set texture magnification filter, should be attached to each texture's slot in a material
		draw from -> to indexed vertices
	*/

	kinc_g4_set_pipeline(&ctx->material->pipeline->pipeline);
	kinc_g4_set_texture(ctx->material->tex_data.texture_units[0], ctx->material->tex_data.textures[0]);
	renderer_assign_uniforms(ctx->material);
	kinc_g4_set_vertex_buffer(&ctx->vbo);
	kinc_g4_set_index_buffer(&ctx->ibo);
	//Mag filter needs set up in the context, maybe needs hashed also
	//This is actual a material configuration, I get it now.
	kinc_g4_set_texture_magnification_filter(ctx->material->tex_data.texture_units[0], KINC_G4_MIPMAP_FILTER_POINT);
	//kinc_g4_draw_indexed_vertices_from_to(ctx->ibo_offset, ctx->requested_draw_count);
	//kinc_g4_draw_indexed_vertices_from_to(0, 6);
	kinc_g4_draw_indexed_vertices();
	
	switch (draw_mode)
	{
		case TEC_RENDERER_CONTINUE_DRAW:
			//Do nothing, we still have to draw
			break;
		case TEC_RENDERER_DRAW_THEN_SWAP_BUFFER:
			//We're done, swap the buffers and end
			kinc_g4_end(0);
			kinc_g4_swap_buffers();
			break;
		default:
			//This assert saved me
			//We must always assert switch cases, end of story.
			assert(0 && "Somehow reached the default case in tec_renderer draw, should not be possible");
			break;
	}
}
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

typedef struct
tec_internal_renderer_context_cache
{
	kinc_g4_vertex_buffer_t * cached_vbo;
	kinc_g4_index_buffer_t * cached_ibo;
	kinc_g4_render_target_t * cached_surface;
	tec_renderer_material_t * cached_material;
}
tec_internal_renderer_context_cache_t;

local_data tec_internal_renderer_context_cache_t render_cache = {0};

void
cache_vbo_location(kinc_g4_vertex_buffer_t * vbo)
{
	render_cache.cached_vbo = vbo;
}

void
cache_ibo_location(kinc_g4_index_buffer_t * ibo)
{
	render_cache.cached_ibo = ibo;
}

void
cache_surface_location(kinc_g4_render_target_t * surface)
{
	render_cache.cached_surface = surface;
}

void
cache_material_location(tec_renderer_material_t * mat)
{
	render_cache.cached_material = mat;
}

void 
tec_renderer_draw(tec_renderer_context_t * ctx, tec_renderer_draw_mode_e draw_mode)
{
	//No material match, so we must refresh uniforms, textures, pipelines, etc.
	//Could probably be broken down more but admittedly I'm a bit lazy
	if (ctx->material != render_cache.cached_material) 
	{
		cache_material_location(ctx->material);

		kinc_g4_set_pipeline(&ctx->material->pipeline);

		for (int i = 0; i < TEC_RENDERER_MAX_TEXTURE_UNITS; i++)
		{
			tec_renderer_texture_data_t * data = &ctx->material->tex_data;
			if (data->present[i] == TEC_TEXTURE_PRESENT)
			{
				kinc_g4_set_texture(ctx->material->tex_data.texture_units[i], &ctx->material->tex_data.textures[i]);
			}
		}

		renderer_assign_uniforms(ctx->material);
	}

	//The render target or framebuffer got swapped, so we need to set it now
	if (ctx->surface != render_cache.cached_surface)
	{
		if (ctx->surface == NULL)
		{
			//No surface present in the context means that we want to draw to the framebuffer
			cache_surface_location(NULL);
			kinc_g4_restore_render_target(); 
		}
		else
		{
			//Set the appropriate render target to draw to that the context requests
			cache_surface_location(ctx->surface);
			kinc_g4_set_render_targets(&ctx->surface, 1);
		}
	}

	//The vertex buffer got swapped (very unlikely, excluding first run), so it needs updated
	if (&ctx->vbo != render_cache.cached_vbo)
	{
		cache_vbo_location(&ctx->vbo);
		kinc_g4_set_vertex_buffer(&ctx->vbo);
	}

	//The index buffer got swapped (also very unlikely), so it needs updated
	if (&ctx->ibo != render_cache.cached_ibo)
	{
		cache_ibo_location(&ctx->ibo);
		kinc_g4_set_index_buffer(&ctx->ibo);
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
#include "g2.h"
#include "../frequent.h"
#include "../lib/HandmadeMath.h"
#include "../math/matrix.h"
#include <stdbool.h>
#include <assert.h>
#include "kinc/graphics4/graphics.h"
#include "kinc/graphics4/vertexbuffer.h"
#include "../assets/assets.h"
#include "../debug/log.h"

#define TEC_LOG_MODULE_NAME "G2"

local_data tec_g2_context_t * active_context;
local_data tec_assets_storage_t * active_assets;

local_func float *
get_current_pre_vbo_position(void)
{
	return &active_context->pre_vbo[active_context->pre_vbo_offset];
}

local_func void 
push_vert_textured(hmm_v3 vert, tec_color_t color, float u, float v)
{
	active_context->pre_vbo[active_context->pre_vbo_offset++] = vert.X;
	active_context->pre_vbo[active_context->pre_vbo_offset++] = vert.Y;
	active_context->pre_vbo[active_context->pre_vbo_offset++] = vert.Z;

	active_context->pre_vbo[active_context->pre_vbo_offset++] = tec_color_ARGB_r(color);
	active_context->pre_vbo[active_context->pre_vbo_offset++] = tec_color_ARGB_g(color);
	active_context->pre_vbo[active_context->pre_vbo_offset++] = tec_color_ARGB_b(color);
	active_context->pre_vbo[active_context->pre_vbo_offset++] = tec_color_ARGB_a(color);

	active_context->pre_vbo[active_context->pre_vbo_offset++] = u;
	active_context->pre_vbo[active_context->pre_vbo_offset++] = v;
}

local_func void
push_draw_command
(
	tec_g2_draw_type_e type, 
	float * data_location, 
	int layer_offset, 
	tec_sortkey_sublayer_e sublayer, 
	tec_assref_material_t material
)
{
	tec_sortkey_t key = tec_sortkey_create();
	key = tec_sortkey_set_layer(key, layer_offset);
	key = tec_sortkey_set_sublayer(key, sublayer);
	key = tec_sortkey_set_material(key, material);

	tec_g2_draw_package_t package = {.sortkey = key, .type = type, .draw_data = data_location};

	assert(active_context->draw_commands_offset < TEC_G2_MAX_COMMANDS && "Overran draw command buffer for the current frame.");

	active_context->draw_commands[active_context->draw_commands_offset++] = package;
}


void 
tec_g2_initialize(tec_g2_context_t * context)
{
	tec_assref_material_t active_material = tec_assets_find_material(active_assets, "DEFAULT_TEXTURED");
	tec_material_t * matdata = tec_internal_assets_retrieve_material_data_location(active_assets, active_material);

	//VBO for textured data (the overwhelming majority of our stuff, with any luck)
	kinc_g4_index_buffer_init(&active_context->r_ctx.ibo_textured, TEC_G2_MAX_TEXTURED_INDICES, KINC_G4_INDEX_BUFFER_FORMAT_16BIT, KINC_G4_USAGE_DYNAMIC);
	kinc_g4_vertex_buffer_init(&active_context->r_ctx.vbo_textured, TEC_G2_MAX_TEXTURED_VERTS, &matdata->pipeline->vertex_structure, KINC_G4_USAGE_DYNAMIC, 0);

	//VBO for lightmapped data
	kinc_g4_index_buffer_init(&active_context->r_ctx.ibo_textured, TEC_G2_MAX_LIGHTMAPPED_INDICES, KINC_G4_INDEX_BUFFER_FORMAT_16BIT, KINC_G4_USAGE_DYNAMIC);
	kinc_g4_vertex_buffer_init(&active_context->r_ctx.vbo_textured, TEC_G2_MAX_LIGHTMAPPED_VERTS, &matdata->pipeline->vertex_structure, KINC_G4_USAGE_DYNAMIC, 0);

	//Projection is linked up to normal draw for now...
	active_context->r_ctx.material = matdata;
}

//Provide a context to be used for the drawing cycle
void 
tec_g2_begin(tec_g2_context_t * context, tec_assets_storage_t * assets)
{
	//Matching kinc_g4_end(0) is in renderer.c
	//Kind of bad design, but should g2 be handling the buffer swap?
	kinc_g4_begin(0);
	kinc_g4_clear(KINC_G4_CLEAR_COLOR, 0, 0.0f, 0);
	assert(context != NULL && "Submitted g2 context was NULL and it definitely can't be that.");
	assert(active_context == NULL && "End before you begin again!");
	active_context = context;
	active_assets = assets;

	active_context->pre_vbo_offset = 0;
	active_context->draw_commands_offset = 0;
}

//Releases context, probably ends drawing
void 
tec_g2_end(void)
{
	assert(active_context != NULL && "Begin before you end again!");

	//The big one. This should actually loop until all draw commands are processed...
	tec_renderer_draw(&active_context->r_ctx);

	//Then, once everything's processed, we're done
	kinc_g4_end(0);
	kinc_g4_swap_buffers();

	active_context = NULL;
	active_assets = NULL;
}

void tec_g2_draw_image(uint FIXMEBITCH /*we don't have an image yet lol*/, hmm_v3 xyz, tec_color_t color);
void tec_g2_draw_subimage(uint FIXMEBITCH, hmm_v3 xyz, hmm_v2 sub_tl, hmm_v2 sub_br);
void tec_g2_draw_scaled_subimage(uint FIXMEBITCH, hmm_v3 xyz, hmm_v2 sub_tl, hmm_v2 sub_br, float scale_factor_x, float scale_factor_y);

void 
tec_g2_draw_line(hmm_v3 p1, hmm_v3 p2, float thickness, tec_color_t color)
{
	assert(active_context != NULL && "G2 Context must have been begun and initialized before drawing operations.");
}

void 
tec_g2_draw_rect(hmm_v3 xyz, float width, float height, float thickness, tec_color_t color)
{
	assert(active_context != NULL && "G2 Context must have been begun and initialized before drawing operations.");
}

void 
tec_g2_draw_filled_rect(hmm_v3 xyz, float width, float height, tec_color_t color)
{
	assert(active_context != NULL && "G2 Context must have been begun and initialized before drawing operations.");

	
}


void 
tec_g2_draw_tri(hmm_v3 p1, hmm_v3 p2, hmm_v3 p3, tec_color_t color)
{
	assert(active_context != NULL && "G2 Context must have been begun and initialized before drawing operations.");
}

void 
tec_g2_draw_filled_tri(hmm_v3 p1, hmm_v3 p2, hmm_v3 p3, tec_color_t color)
{
	assert(active_context != NULL && "G2 Context must have been begun and initialized before drawing operations.");

	float * data = get_current_pre_vbo_position();
	push_vert_textured(p1, color, 0, 0);
	push_vert_textured(p2, color, 1, 1);
	push_vert_textured(p3, color, 0, 1);
	//push_draw_command(TEC_G2_FILLED_TRI, data);
}

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
local_data kinc_matrix4x4_t projection;
local_data first_run = true;
local_data counter = 0;

local_func inline void
push_vert(float x, float y, float z, float r, float g, float b, float a, float u, float v)
{
	//I'm overwriting the verts D:?????
	float * verts = active_context->r_ctx.v_data;
	size_t pos = 0;
	verts[counter++] = x;
	verts[counter++] = y;
	verts[counter++] = z;
	verts[counter++] = r;
	verts[counter++] = g;
	verts[counter++] = b;
	verts[counter++] = a;
	verts[counter++] = u;
	verts[counter++] = v;
}

void 
tec_g2_initialize(tec_g2_context_t * context)
{
	tec_assref_material_t active_material = tec_assets_find_material(active_assets, "Normal Draw");
	tec_material_t * matdata = tec_internal_assets_retrieve_material_data_location(active_assets, active_material);
	kinc_g4_index_buffer_init(&active_context->r_ctx.ibo_textured, TEC_G2_MAX_INDICES, KINC_G4_INDEX_BUFFER_FORMAT_16BIT, KINC_G4_USAGE_DYNAMIC);
	kinc_g4_vertex_buffer_init(&active_context->r_ctx.vbo_textured, TEC_G2_MAX_VERTS, &matdata->pipeline->vertex_structure, KINC_G4_USAGE_DYNAMIC, 0);

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
	//kinc_g4_restore_render_target();

	active_context->r_ctx.v_data = kinc_g4_vertex_buffer_lock_all(&active_context->r_ctx.vbo_textured);
	
	active_context->r_ctx.i_data = kinc_g4_index_buffer_lock(&active_context->r_ctx.ibo);
}

//Releases context, probably ends drawing
void 
tec_g2_end(void)
{
	assert(active_context != NULL && "Begin before you end again!");
	kinc_g4_vertex_buffer_unlock_all(&active_context->r_ctx.vbo_textured);
	kinc_g4_index_buffer_unlock(&active_context->r_ctx.ibo);

	//The big one.
	tec_renderer_draw(&active_context->r_ctx, TEC_RENDERER_DRAW_THEN_SWAP_BUFFER);

	active_context = NULL;
}

void 
tec_g2_draw_square(float cx, float cy, float size, tec_color_t color)
{
	// push_vert(-1, -1, 0.5, 1, 1, 1, 1, 0, 0); //bl
	// push_vert(1, -1, 0.5, 1, 1, 1, 1, 1, 0);//br
	// push_vert(-1, 1, 0.5, 1, 1, 1, 1, 0, 1);//tl

	push_vert(0, 0, 10., 1, 1, 1, 1, 0, 0); //bl
	push_vert(800, 600, 10., 1, 1, 1, 1, 1, 1);//br
	push_vert(0, 600, 10., 1, 1, 1, 1, 0, 1);//tl
	//push_vert(1, 1, 0.5, 1, 1, 1, 1, 1, 1);//bl
	push_vert(0, 0, 10., 1, 1, 1, 1, 0, 0);
	push_vert(800, 0, 10., 1, 1, 1, 1, 1, 0);
	push_vert(800, 600, 10., 1, 1, 1, 1, 1, 1);

	int * indexes = active_context->r_ctx.i_data;
	size_t pos = 0;
	indexes[pos++] = 0;
	indexes[pos++] = 1;
	indexes[pos++] = 2;
	indexes[pos++] = 3;
	indexes[pos++] = 4;
	indexes[pos++] = 5;
	//indexes[pos++] = 0;
	//indexes[pos++] = 2;
	//indexes[pos++] = 3;
	counter = 0;
}
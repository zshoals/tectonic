#pragma once

#include "../lib/HandmadeMath.h"
#include "color.h"
#include "renderer.h"
#include "../assets/assets_references.h"
#include "sortkey.h"
#include "stdbool.h"

#define TEC_G2_MAX_TEXTURED_VERTS 4000
#define TEC_G2_MAX_TEXTURED_INDICES 4000
#define TEC_G2_MAX_LIGHTMAPPED_VERTS 401
#define TEC_G2_MAX_LIGHTMAPPED_INDICES 401
//We might try and push this as hard as possible ;)
#define TEC_G2_MAX_COMMANDS 5000


//Contains commands for things like drawing rects and lines. Textured, untextured, etc.
//Batches and submits everything to renderer

typedef enum
{
	TEC_G2_FILLED_RECT,
	TEC_G2_RECT,
	TEC_G2_FILLED_TRI,
	TEC_G2_TRI,
	TEC_G2_IMAGE,
	TEC_G2_LINE,
}
tec_g2_draw_type_e;

typedef struct
tec_g2_draw_package
{	
	tec_sortkey_t sortkey;
	tec_g2_draw_type_e type; //This essentially defines the "stride" of the data
	float * draw_data; //Hooks into pre_vbo
}
tec_g2_draw_package_t;

typedef struct
tec_g2_context
{
	tec_renderer_context_t r_ctx; //STUFF HERE
	//Make sure to handle special case of overrunning sort keys - we have to draw then start filling the storage again
	tec_g2_draw_package_t draw_commands[TEC_G2_MAX_COMMANDS];
	size_t draw_commands_offset;
	float pre_vbo[TEC_G2_MAX_TEXTURED_VERTS];
	size_t pre_vbo_offset;
}
tec_g2_context_t;
//G2 does not give a 6575475 about vbos and stuff, that's the renderer's job to filter through I guess.
//G2 should really only deal in abstract "draw commands" that tells what material to set, and what order to submit verts


//Initializes g2. G2 handles its own renderer context
//Uses the bog standard textured drawing material by default
void tec_g2_initialize(tec_g2_context_t * context);
//sets the context to use for drawing
//Everything is automatically spritebatched
void tec_g2_begin(tec_g2_context_t * context, tec_assets_storage_t * assets);
//Releases context, probably ends drawing
void tec_g2_end(void);


//Note: The depth (z) is used for certain effects, but the API is really just for 2d operations
void tec_g2_draw_image(uint FIXMEBITCH /*we don't have an image yet lol*/, hmm_v3 xyz, tec_color_t color);
void tec_g2_draw_subimage(uint FIXMEBITCH, hmm_v3 xyz, hmm_v2 sub_tl, hmm_v2 sub_br);
void tec_g2_draw_scaled_subimage(uint FIXMEBITCH, hmm_v3 xyz, hmm_v2 sub_tl, hmm_v2 sub_br, float scale_factor_x, float scale_factor_y);

void tec_g2_draw_line(hmm_v3 p1, hmm_v3 p2, float thickness, tec_color_t color);

void tec_g2_draw_rect(hmm_v3 xyz, hmm_v2 tl, hmm_v2 br, float thickness, tec_color_t color);
void tec_g2_draw_filled_rect(hmm_v3 xyz, hmm_v2 tl, hmm_v2 br, tec_color_t color);

void tec_g2_draw_tri(hmm_v3 p1, hmm_v3 p2, hmm_v3 p3, tec_color_t color);
void tec_g2_draw_filled_tri(hmm_v3 p1, hmm_v3 p2, hmm_v3 p3, tec_color_t color);

void tec_g2_command_switch_rendertarget(int render_target_identifier /* what is this? */);
void tec_g2_command_switch_material(int material_identifier);
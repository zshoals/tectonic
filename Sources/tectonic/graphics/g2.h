#pragma once

#include "../lib/HandmadeMath.h"
#include "color.h"
#include "renderer.h"
#include "../assets/assets_references.h"
#include "sortkey.h"

#define TEC_G2_MAX_VERTS 4000
#define TEC_G2_MAX_INDICES 4000
#define TEC_G2_MAX_COMMANDS (4000 / 3)


//Contains commands for things like drawing rects and lines. Textured, untextured, etc.
//Batches and submits everything to renderer


typedef struct
tec_g2_context
{
	tec_renderer_context_t r_ctx; //STUFF HERE
	//Make sure to handle special case of overrunning sort keys - we have to draw then start filling the storage again
	tec_sortkey_t sortkeys[TEC_G2_MAX_COMMANDS];
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


void tec_g2_draw_rect(float cx, float cy, float size, tec_color_t color);
void tec_g2_draw_square(float cx, float cy, float size, tec_color_t color);
void tec_g2_draw_line(hmm_v2 p1, hmm_v2 p2, float thickness, tec_color_t color);

void tec_g2_command_switch_rendertarget(int render_target_identifier /* what is this? */);
void tec_g2_command_switch_material(int material_identifier);
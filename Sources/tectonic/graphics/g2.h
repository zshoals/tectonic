#pragma once

#include "../lib/HandmadeMath.h"
#include "color.h"
#include "renderer.h"

//Contains commands for things like drawing rects and lines. Textured, untextured, etc.
//Batches and submits everything to renderer

//Rect -> Center positions, size, color (this one's untextured)
//Well actually they're all textured, we're going to make a 1x1 white pixel to avoid the shader program change
typedef struct
tec_g2_context
{
	tec_renderer_context_t r_ctx; //STUFF HERE
}
tec_g2_context_t;

//sets the context to use for drawing
//Everything is automatically spritebatched
void tec_g2_begin(tec_g2_context_t * context);
//Releases context, probably ends drawing
void tec_g2_end(void);


void tec_g2_draw_rect(float cx, float cy, float size, tec_color_t color);
void tec_g2_draw_line(hmm_v2 p1, hmm_v2 p2, float thickness, tec_color_t color);

void tec_g2_command_switch_rendertarget(int render_target_identifier /* what is this? */);
void tec_g2_command_switch_material(int material_identifier);
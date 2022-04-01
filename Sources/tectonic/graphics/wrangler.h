#pragma once

#include "sortkey.h"
#include "../assets/assets_references.h"

#define TEC_MAX_DRAW_COMMANDS 10000

#define template_type tec_draw_command_t
#define template_array_size TEC_MAX_DRAW_COMMANDS

typedef struct
tec_sprite_data
{
	int layer;
	int sublayer;
	tec_assref_material_t material;
}
tec_sprite_data_t;

typedef struct
tec_draw_command
{
	tec_sortkey_t sortkey;
	tec_sprite_data_t * sprite_data;
}
tec_draw_command_t;

typedef struct
tec_draw_command_group
{
	int i;
}
tec_draw_command_group_t;

//Not right
//This should just accept a draw command array and a length!!!!!
typedef struct
tec_wrangler
{
	tec_draw_command_t commands[TEC_MAX_DRAW_COMMANDS];
	tec_sprite_data_t * sprite_data_locations[TEC_MAX_DRAW_COMMANDS];
}
tec_wrangler_t;
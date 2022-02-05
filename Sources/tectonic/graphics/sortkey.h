#pragma once

#include "../assets/assets_references.h"
#include <stdint.h>
#include "../frequent.h"

typedef uint tec_sortkey_t;

//32 bit sort key

//|00|000|00|000000|0000|0|00000000000|000
//FSL-RT-Trns-Layer-SubL-CMD-Material-Pass
//OR
//|00|000|00|000000|0000|0|00000|000000000
//FSE-RT-Trns-Layer-SubL-CMD?-SEQ-COMMAND

//FSE = Full Screen Layer --- Fullscreen effect? HUD? Game world? 0-3 R: 30 - 31
//Render Target (maybe?) - 0-7 R: 27 - 29
//Translucency type, opaque or Add/Normal/Subtract transparent? 0-3 R: 25-26
//World layer/depth. 0-63 R: 19 - 24
//Sub layer - FX1, FX2, Decal, World, etc. 0-15 R: 15 - 18
//Command mode yes or no? 0-1 R: 14
//Material - Texture data, uniform state, shader program - 0-2047 R: 3-13
//Pass - not sure but we're keeping it - 0-7 R: 0-2

//Sequence - Which step in a command sequence this command is - 0-31 R: 9 - 13
//Command type - Which command to execute - 0-511 R: 0-8

typedef enum
{
	TEC_SORTKEY_FULLSCREEN_LAYER_GAMEWORLD,
	TEC_SORTKEY_FULLSCREEN_LAYER_EFFECT,
	TEC_SORTKEY_FULLSCREEN_LAYER_HUD,
}
tec_sortkey_fullscreen_layer_e;

//This may not work well
//We kind of need to switch at will as to what surface we're drawing on
//This might be better as commands.
typedef enum
{
	TEC_SORTKEY_RENDERTARGET_PIXEL_SURFACE,
	TEC_SORTKEY_RENDERTARGET_LIGHTING,
	TEC_SORTKEY_RENDERTARGET_HUD,
	TEC_SORTKEY_RENDERTARGET_FRAMEBUFFER,
}
tec_sortkey_rendertarget_e;

typedef enum
{
	TEC_SORTKEY_SUBLAYER_UNDER_DECAL1,
	TEC_SORTKEY_SUBLAYER_UNDER_DECAL2,
	TEC_SORTKEY_SUBLAYER_UNDER_DECAL3,

	TEC_SORTKEY_SUBLAYER_GAMELAYER,

	TEC_SORTKEY_SUBLAYER_DECAL1,
	TEC_SORTKEY_SUBLAYER_DECAL2,
	TEC_SORTKEY_SUBLAYER_DECAL3,

	TEC_SORTKEY_SUBLAYER_FX1,
	TEC_SORTKEY_SUBLAYER_FX2,
}
tec_sortkey_sublayer_e;

typedef enum
{
	TEC_SORTKEY_COMMAND_SWAP_SURFACE_FRAMEBUFFER,
	TEC_SORTKEY_COMMAND_SWAP_SURFACE_PIXELBUFFER,
	TEC_SORTKEY_COMMAND_SWAP_SURFACE_LIGHTING,
}
tec_sortkey_command_e;

tec_sortkey_t tec_sortkey_create(void);
tec_sortkey_t tec_sortkey_set_fullscreen_layer(tec_sortkey_t key, tec_sortkey_fullscreen_layer_e type);
//tec_sortkey_t tec_sortkey_set_rendertarget()
//tec_sortkey_t tec_sortkey_set_translucency_type() (kind of unneeded right now)

//This function is intended to be used by adding or subtracting from the "base layer" which is 31.
//Negative layers descend into the scene, positive layers ascend towards the camera
tec_sortkey_t tec_sortkey_set_layer(tec_sortkey_t key, int layer_offset);
tec_sortkey_t tec_sortkey_set_sublayer(tec_sortkey_t key, tec_sortkey_sublayer_e sublayer);

//How the hell do we figure this one out :/?
//Use the corresponding slot from assets :////????
//Actually, this works, this makes the material slot encoded into the sort key
tec_sortkey_t tec_sortkey_set_material(tec_sortkey_t key, tec_assref_material_t material);
tec_sortkey_t tec_sortkey_set_pass(tec_sortkey_t key, uint16_t pass);

tec_sortkey_t tec_sortkey_enable_command_mode(tec_sortkey_t key);
tec_sortkey_t tec_sortkey_disable_command_mode(tec_sortkey_t key);
tec_sortkey_t tec_sortkey_set_command(tec_sortkey_t key, uint16_t sequence_number, tec_sortkey_command_e command);



tec_sortkey_fullscreen_layer_e tec_sortkey_get_fullscreen_layer(tec_sortkey_t key);
uint tec_sortkey_get_layer(tec_sortkey_t key);
tec_sortkey_sublayer_e tec_sortkey_get_sublayer(tec_sortkey_t key);
size_t tec_sortkey_get_material(tec_sortkey_t key);
uint tec_sortkey_get_pass(tec_sortkey_t key);
uint tec_sortkey_get_command_mode(tec_sortkey_t key);
uint tec_sortkey_get_sequence(tec_sortkey_t key);
tec_sortkey_command_e tec_sortkey_get_command(tec_sortkey_t key);

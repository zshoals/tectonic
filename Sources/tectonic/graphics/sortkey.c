#include "sortkey.h"
#include "../frequent.h"
#include "../util/bits.h"

//|00|000|00|000000|0000|0|00000000000|000
//FSL-RT-Trns-Layer-SubL-CMD-Material-Pass
//OR
//|00|000|00|000000|0000|0|00000|000000000
//FSE-RT-Trns-Layer-SubL-CMD?-SEQ-COMMAND

tec_sortkey_t 
tec_sortkey_create(void)
{
	return (uint)0;
}

tec_sortkey_t 
tec_sortkey_set_fullscreen_layer(tec_sortkey_t key, tec_sortkey_fullscreen_layer_e type)
{
	tec_bits_set_range(key, 30, 31, type);
}

//tec_sortkey_t tec_sortkey_set_rendertarget()
//tec_sortkey_t tec_sortkey_set_translucency_type() (kind of unneeded right now)

//This function is intended to be used by adding or subtracting from the "base layer" which is 31.
//Negative layers descend into the scene, positive layers ascend towards the camera
tec_sortkey_t 
tec_sortkey_set_layer(tec_sortkey_t key, int layer_offset)
{
	return tec_bits_set_range(key, 19, 24, 31 + layer_offset);
}

tec_sortkey_t 
tec_sortkey_set_sublayer(tec_sortkey_t key, tec_sortkey_sublayer_e sublayer)
{
	return tec_bits_set_range(key, 15, 18, sublayer);
}


//How the hell do we figure this one out :/?
//Use the corresponding slot from assets :////????
//Actually, this works, this makes the material slot encoded into the sort key
tec_sortkey_t 
tec_sortkey_set_material(tec_sortkey_t key, tec_assref_material_t material)
{
	return tec_bits_set_range(key, 3, 13, material.asset_location);
}

tec_sortkey_t 
tec_sortkey_set_pass(tec_sortkey_t key, uint16_t pass)
{
	return tec_bits_set_range(key, 0, 2, pass);
}

tec_sortkey_t 
tec_sortkey_enable_command_mode(tec_sortkey_t key)
{
	return tec_bits_set_range(key, 14, 14, 1);
}

tec_sortkey_t 
tec_sortkey_disable_command_mode(tec_sortkey_t key)
{
	return tec_bits_set_range(key, 14, 14, 0);
}

tec_sortkey_t 
tec_sortkey_set_command(tec_sortkey_t key, uint16_t sequence_number, tec_sortkey_command_e command)
{
	key = tec_bits_set_range(key, 9, 13, sequence_number);
	return tec_bits_set_range(key, 0, 8, command);
}


tec_sortkey_fullscreen_layer_e 
tec_sortkey_get_fullscreen_layer(tec_sortkey_t key)
{
	return tec_bits_get_range(key, 30, 31);
}

uint 
tec_sortkey_get_layer(tec_sortkey_t key)
{
	return tec_bits_get_range(key, 19, 24);
}

tec_sortkey_sublayer_e 
tec_sortkey_get_sublayer(tec_sortkey_t key)
{
	return tec_bits_get_range(key, 15, 18);
}

size_t 
tec_sortkey_get_material(tec_sortkey_t key)
{
	return tec_bits_get_range(key, 3, 13);
}

uint 
tec_sortkey_get_pass(tec_sortkey_t key)
{
	return tec_bits_get_range(key, 0, 2);
}

uint 
tec_sortkey_get_command_mode(tec_sortkey_t key)
{
	return tec_bits_get_range(key, 14, 14);
}

uint 
tec_sortkey_get_sequence(tec_sortkey_t key)
{
	return tec_bits_get_range(key, 9, 13);
}

tec_sortkey_command_e 
tec_sortkey_get_command(tec_sortkey_t key)
{
	return tec_bits_get_range(key, 0, 8);
}

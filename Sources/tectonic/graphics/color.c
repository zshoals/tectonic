#include "color.h"
#include "../frequent.h"

local_func int 
color_clamp(int value, int min, int max)
{
	if (value < min)
	{
		value = min;
	}
	else if (value > max)
	{
		value = max;
	}

	return value;
}

local_func tec_color_t
pack_then_rotate(tec_color_t value, int add, int shift)
{
	value += add;
	return value <<= shift;
}

local_func int
unpack(tec_color_t color, int mask, int shift)
{
	color &= mask;
	color >>= shift;
	return color;
}

int 
tec_color_ARGB_r(tec_color_t color)
{
	return unpack(color, TEC_RED_MASK, TEC_RED_ARGB_SHIFT);
}

int 
tec_color_ARGB_g(tec_color_t color)
{
	return unpack(color, TEC_GREEN_MASK, TEC_GREEN_ARGB_SHIFT);
}

int 
tec_color_ARGB_b(tec_color_t color)
{
	return unpack(color, TEC_BLUE_MASK, TEC_BLUE_ARGB_SHIFT);
}

int 
tec_color_ARGB_a(tec_color_t color)
{
	return unpack(color, TEC_ALPHA_MASK, TEC_ALPHA_ARGB_SHIFT);
}

/*

	Normalized versions

*/

float
tec_color_ARGB_norm_r(tec_color_t color)
{
	return unpack(color, TEC_RED_MASK, TEC_RED_ARGB_SHIFT) / 255.0f;
}

float
tec_color_ARGB_norm_g(tec_color_t color)
{
	return unpack(color, TEC_GREEN_MASK, TEC_GREEN_ARGB_SHIFT) / 255.0f;
}

float 
tec_color_ARGB_norm_b(tec_color_t color)
{
	return unpack(color, TEC_BLUE_MASK, TEC_BLUE_ARGB_SHIFT) / 255.0f;
}

float
tec_color_ARGB_norm_a(tec_color_t color)
{
	return unpack(color, TEC_ALPHA_MASK, TEC_ALPHA_ARGB_SHIFT) / 255.0f;
}

tec_color_t 
tec_color_pack(int r, int g, int b, int a)
{
	a = color_clamp(a, 0, 255);
	r = color_clamp(r, 0, 255);
	g = color_clamp(g, 0, 255);
	b = color_clamp(b, 0, 255);

	tec_color_t color = 0;
	int bit_count = 8;

	pack_then_rotate(color, a, bit_count);
	pack_then_rotate(color, r, bit_count);
	pack_then_rotate(color, g, bit_count);
	pack_then_rotate(color, b, bit_count);

	return color;
}

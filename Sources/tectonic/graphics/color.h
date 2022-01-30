#pragma once

typedef int tec_color_t;

#define TEC_ALPHA_MASK 0xFF000000
#define TEC_RED_MASK 0x00FF0000
#define TEC_BLUE_MASK 0x0000FF00
#define TEC_GREEN_MASK 0x000000FF

#define TEC_ALPHA_ARGB_SHIFT 24
#define TEC_RED_ARGB_SHIFT 16
#define TEC_GREEN_ARGB_SHIFT 8
#define TEC_BLUE_ARGB_SHIFT 0

tec_color_t tec_color_pack_ARGB(int r, int g, int b, int a);

int tec_color_ARGB_r(tec_color_t color);
int tec_color_ARGB_g(tec_color_t color);
int tec_color_ARGB_b(tec_color_t color);
int tec_color_ARGB_a(tec_color_t color);

float tec_color_ARGB_norm_r(tec_color_t color);
float tec_color_ARGB_norm_g(tec_color_t color);
float tec_color_ARGB_norm_b(tec_color_t color);
float tec_color_ARGB_norm_a(tec_color_t color);

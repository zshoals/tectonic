#pragma once

#include "material.h"
#include "kinc/graphics4/pipeline.h"
#include "kinc/graphics4/vertexbuffer.h"
#include "kinc/graphics4/vertexstructure.h"

/*! default hardcoded shader pipelines with various blending modes.
We don't really need that much, so hardcoding it is the simply and obvious solution.
*/
typedef unsigned int pipeline_vert;
typedef unsigned int fragment_shader;


#ifdef bfarray_type
#undef bfarray_type
#endif
#define bfarray_type pipeline_vert
#define bfarray_size 16
#include "../ds/bfarray.h"

tec_bfarray_pipeline_vert_16_t storage;

#ifdef bfarray_type
#undef bfarray_type
#endif
#define bfarray_type fragment_vert
#define bfarray_size 16
#include "../ds/bfarray.h"

tec_bfarray_fragment_vert_16_t storage2;

typedef enum
{
	TEC_BLENDING_DISABLED,
	//Normal assumes you are using a shader with premultiplied alpha
	TEC_BLENDING_NORMAL,
	TEC_BLENDING_ADD,
	TEC_BLENDING_MULTIPLY,
	//I have no idea what this blend mode is, but it causes the underlying image to only be drawn to non-fully-transparent regions in the image posted above it
	//Very useful for imitating lighting by putting a "lighting" layer UNDER the draw layer
	TEC_BLENDING_MASK_WITH_COLOR,
	TEC_BLENDING_MASK,
}
tec_material_pipeline_blending_e;


kinc_g4_pipeline_t tec_pipeline_create_default_textured(void);
void tec_pipeline_blend_mode_helper(kinc_g4_pipeline_t * pipeline, tec_material_pipeline_blending_e blending_mode);
void tec_test(void)
{
	tec_bfarray_pipeline_vert_16_get(&storage, 6);
}
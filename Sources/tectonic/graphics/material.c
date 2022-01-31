#include "material.h"
#include "kinc/graphics4/pipeline.h"
#include <assert.h>

void 
tec_material_initialize(tec_material_material_t * mat, char const * name, kinc_g4_pipeline_t pipeline)
{
	mat->name = name;
	mat->pipeline = pipeline;

	for (int i = 0; i < TEC_MATERIAL_MAX_TEXTURE_UNITS; i++)
	{
		mat->tex_data.present[i] = TEC_TEXTURE_NULL;
	}

	for (int i = 0; i < TEC_MATERIAL_MAX_UNIFORMS; i++)
	{
		mat->uniforms[i].type = TEC_UNIFORM_TYPE_NULL;
	}
}

void 
tec_material_assign_texture(tec_material_material_t * mat, char const * name, kinc_g4_texture_t texture, size_t slot)
{
	mat->tex_data.textures[slot] = texture;
	mat->tex_data.texture_units[slot] = kinc_g4_pipeline_get_texture_unit(&mat->pipeline, name);
	mat->tex_data.present[slot] = TEC_TEXTURE_PRESENT;
}

void 
tec_material_assign_uniform(tec_material_material_t * mat, char const * name, tec_material_uniform_data_u data, tec_material_uniform_type_e type, size_t slot)
{
	mat->uniforms[slot].name = name;
	mat->uniforms[slot].data = data;
	mat->uniforms[slot].type = type;
	mat->uniforms[slot].location = kinc_g4_pipeline_get_constant_location(&mat->pipeline, name);
}

void
tec_material_pipeline_blend_mode_helper(kinc_g4_pipeline_t * pipeline, tec_material_pipeline_blending_e blending_mode)
{
	switch (blending_mode)
	{
		case TEC_BLENDING_DISABLED:
			pipeline->blend_source = KINC_G4_BLEND_ONE;
			pipeline->blend_destination = KINC_G4_BLEND_ZERO;
			break;

		case TEC_BLENDING_NORMAL:
			pipeline->blend_source = KINC_G4_BLEND_ONE;
			pipeline->blend_destination = KINC_G4_BLEND_INV_SOURCE_ALPHA;
			break;

		case TEC_BLENDING_ADD:
			pipeline->blend_source = KINC_G4_BLEND_ONE;
			pipeline->blend_destination = KINC_G4_BLEND_ONE;
			break;

		case TEC_BLENDING_MULTIPLY:
			pipeline->blend_source = KINC_G4_BLEND_DEST_COLOR;
			pipeline->blend_destination = KINC_G4_BLEND_INV_SOURCE_ALPHA;
			break;

		case TEC_BLENDING_MASK_WITH_COLOR:
			pipeline->blend_source = KINC_G4_BLEND_SOURCE_ALPHA;
			pipeline->blend_destination = KINC_G4_BLEND_SOURCE_ALPHA;
			break;

		case TEC_BLENDING_MASK:
			pipeline->blend_source = KINC_G4_BLEND_ZERO;
			pipeline->blend_destination = KINC_G4_BLEND_SOURCE_ALPHA;
			break;
		
		default:
			assert(0 && "Should not be able to reach default in blend_mode_helper");
	}

}

#include "material.h"
#include "kinc/graphics4/pipeline.h"
#include "kinc/graphics4/texture.h"
#include <assert.h>
#include "../frequent.h"

tec_material_t default_textured;

void 
tec_material_initialize(tec_material_t * mat, char const * name, kinc_g4_pipeline_t * pipeline)
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
tec_material_assign_texture(tec_material_t * mat, char const * name, kinc_g4_texture_t * texture, size_t slot)
{
	mat->tex_data.textures[slot] = texture;
	mat->tex_data.texture_units[slot] = kinc_g4_pipeline_get_texture_unit(mat->pipeline, name);
	mat->tex_data.present[slot] = TEC_TEXTURE_PRESENT;
}

void 
tec_material_assign_uniform(tec_material_t * mat, char const * name, tec_material_uniform_data_u data, tec_material_uniform_type_e type, size_t slot)
{
	mat->uniforms[slot].name = name;
	mat->uniforms[slot].data = data;
	mat->uniforms[slot].type = type;
	mat->uniforms[slot].location = kinc_g4_pipeline_get_constant_location(mat->pipeline, name);
}

#include "material.h"
#include "kinc/graphics4/pipeline.h"
#include "kinc/graphics4/texture.h"
#include "pipelines.h"
#include <assert.h>
#include "../frequent.h"
#include "../assets/assets.h"
#include "../debug/log.h"

tec_assref_material_t 
tec_material_create_material(tec_assets_storage_t * assets, char const * name, tec_assref_shader_program_t pipeline)
{
	tec_assref_material_t mat = tec_internal_assets_acquire_material_free_slot(assets);
	tec_material_t * matdata = tec_internal_assets_retrieve_material_data_location(assets, mat);

	matdata->name = name;
	matdata->pipeline = tec_internal_assets_retrieve_shader_program_data_location(assets, pipeline);

	for (int i = 0; i < TEC_MATERIAL_MAX_TEXTURE_UNITS; i++)
	{
		matdata->tex_data.present[i] = TEC_TEXTURE_NULL;
	}

	for (int i = 0; i < TEC_MATERIAL_MAX_UNIFORMS; i++)
	{
		matdata->uniforms[i].type = TEC_UNIFORM_TYPE_NULL;
	}

	tec_log_info("Created material \"%s\" in assets material storage slot %d.", name, mat.asset_location);

	return mat;
}

tec_assref_material_t 
tec_material_create_material_by_copy(tec_assets_storage_t * assets, char const * name, tec_assref_material_t original_material)
{
	tec_material_t * oldmat = tec_internal_assets_retrieve_material_data_location(assets, original_material);
	tec_assref_material_t newmat_reference = tec_internal_assets_acquire_material_free_slot(assets);
	tec_material_t * newmat = tec_internal_assets_retrieve_material_data_location(assets, newmat_reference);

	DEREF(newmat) = DEREF(oldmat);
	newmat->name = name;

	return newmat_reference;
}

void 
tec_material_assign_texture(tec_assets_storage_t * assets, tec_assref_material_t mat, char const * tex_unit_name, tec_assref_texture_t tex, size_t slot)
{
	tec_texture_t * texture = tec_internal_assets_retrieve_texture_data_location(assets, tex);
	tec_material_t * material = tec_internal_assets_retrieve_material_data_location(assets, mat);
	material->tex_data.textures[slot] = &texture->texture;
	material->tex_data.texture_units[slot] = kinc_g4_pipeline_get_texture_unit(&material->pipeline->pipeline, tex_unit_name);
	material->tex_data.present[slot] = TEC_TEXTURE_PRESENT;

	tec_log_info("Linked texture unit '%s' and texture '%s' (Slot %d) in material '%s'", tex_unit_name, texture->name, slot, material->name);
}

void 
tec_material_assign_uniform(tec_assets_storage_t * assets, tec_assref_material_t mat, char const * uniform_name, tec_material_uniform_data_u data, tec_material_uniform_type_e type, size_t slot)
{
	tec_material_t * material = tec_internal_assets_retrieve_material_data_location(assets, mat);
	material->uniforms[slot].name = uniform_name;
	material->uniforms[slot].type = type;
	material->uniforms[slot].data = data;
	material->uniforms[slot].location = kinc_g4_pipeline_get_constant_location(&material->pipeline, uniform_name);

	tec_log_info("Linked uniform '%s' in material '%s'", uniform_name, material->name);
}

void 
tec_material_update_uniform(tec_assets_storage_t * assets, tec_assref_material_t mat, char const * uniform_name, tec_material_uniform_data_u data)
{
	tec_material_t * material = tec_internal_assets_retrieve_material_data_location(assets, mat);
	
	for (int i = 0; i < TEC_MATERIAL_MAX_UNIFORMS; i++)
	{
		if (material->uniforms[i].type != TEC_UNIFORM_TYPE_NULL)
		{
			int located_uniform = strcmp(material->uniforms[i].name, uniform_name);
			if (located_uniform == 0)
			{
				material->uniforms[i].data = data;
				break;
			}
		}
	}


}

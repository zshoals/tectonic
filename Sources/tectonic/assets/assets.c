#include "assets.h"
#include "../debug/log.h"
#include "kinc/io/filereader.h"
#include "../frequent.h"

#include "kinc/graphics4/shader.h"
#include "kinc/image.h"
#include "kinc/graphics4/texture.h"

#define TEC_LOG_MODULE_NAME "Assets"

// local_func tec_byte_t *
// memory_allocate(tec_assets_storage_t * resources, size_t size)
// {

// }

//!TODO: With how this works currently, it's possible that functions using the
//resource loading buffer may access stale data. It might need to be zeroed each load
//but maybe not, data might terminate appropriately when loaded by kinc

local_func bool
asset_can_be_loaded(char const * asset)
{
	tec_log_info("Checking if asset \"%s\" is loadable...", asset);
	kinc_file_reader_t reader;
	
	bool loadable = false;
	if(kinc_file_reader_open(&reader, asset, KINC_FILE_TYPE_ASSET))
	{
		tec_log_info("Load ready: \"%s\" .", asset);
		kinc_file_reader_close(&reader);
		loadable = true;
	}
	else
	{
		tec_log_warn("Failed to find asset \"%s\".", asset);
		loadable = false;
	}

	return loadable;
}

local_func bool
save_can_be_loaded(char const * asset); //Not yet implemented

local_func size_t 
load_asset(tec_byte_t * buffer, char const * asset)
{
	tec_log_info("Attempting to open asset \"%s\".....", asset);
	kinc_file_reader_t reader;
	if(kinc_file_reader_open(&reader, asset, KINC_FILE_TYPE_ASSET))
	{
		tec_log_info("Successfully opened and copied asset \"%s\".", asset);
		size_t size = kinc_file_reader_size(&reader);
		kinc_file_reader_read(&reader, buffer, size);
		kinc_file_reader_close(&reader);
		return size;
	}
	else 
	{
		tec_log_warn("Failed to open asset \"%s\".", asset);
		size_t size = 0;
		return size;
	}
}

local_func size_t
load_save(tec_byte_t * buffer, char const * asset)
{
	tec_log_info("Attempting to open save \"%s\".....", asset);
	kinc_file_reader_t reader;
	if(kinc_file_reader_open(&reader, asset, KINC_FILE_TYPE_SAVE))
	{
		tec_log_info("Successfully opened save \"%s\".", asset);
		size_t size = kinc_file_reader_size(&reader);
		kinc_file_reader_read(&reader, buffer, size);
		kinc_file_reader_close(&reader);
		return size;
	}
	else 
	{
		tec_log_warn("Failed to open save \"%s\".", asset);
		size_t size = 0;
		return size;
	}
}

/*=======================

PIPELINES AND MATERIALS

========================*/

bool 
tec_assets_load_fragment_shader(tec_assets_storage_t * resources, char const * asset)
{
	if (asset_can_be_loaded(asset))
	{
		tec_fragment_shader_t frag;
		size_t size = load_asset(&resources->resource_loading_buffer, asset);
		tec_pipeline_initialize_fragment_shader(&frag, asset, &resources->resource_loading_buffer, size);
		tec_pipeline_compile_fragment_shader(&frag);

		bfstack_tec_fragment_shader_t_16_push(&resources->fragment_shaders, frag);

		return true;
	}
	return false;
}

bool 
tec_assets_load_vertex_shader(tec_assets_storage_t * resources, char const * asset)
{
	if (asset_can_be_loaded(asset))
	{
		tec_vertex_shader_t vert;
		size_t size = load_asset(&resources->resource_loading_buffer, asset);
		tec_pipeline_initialize_vertex_shader(&vert, asset, &resources->resource_loading_buffer, size);
		tec_pipeline_compile_vertex_shader(&vert);
		
		bfstack_tec_vertex_shader_t_16_push(&resources->vertex_shaders, vert);

		return true;
	}
	return false;
}

bool 
tec_assets_register_compiled_pipeline(tec_assets_storage_t * resources, tec_pipeline_data_t pipeline)
{
	bfstack_tec_pipeline_data_t_64_push(&resources->pipelines, pipeline);
	return true;
}

bool 
tec_assets_register_material(tec_assets_storage_t * resources, tec_material_t material)
{
	bfstack_tec_material_t_64_push(&resources->materials, material);
	return true;
}

/*=======================

IMAGES

========================*/

bool 
tec_assets_load_image_to_texture(tec_assets_storage_t * resources, char const * asset)
{
	if (asset_can_be_loaded(asset))
	{
		kinc_image_t image;
		size_t size = kinc_image_init_from_file(&image, &resources->resource_loading_buffer, asset);

		tec_texture_t tex;
		tex.name = asset;
		kinc_g4_texture_init_from_image(&tex.texture, &image);

		//This should actually be executed in register texture?
		bfstack_tec_texture_t_64_push(&resources->textures, tex);

		kinc_image_destroy(&image);

		return true;
	}
	return false;
}


/*=======================

AUDIO

========================*/
bool 
tec_assets_load_sfx(tec_assets_storage_t * resources, char const * asset)
{

}

bool 
tec_assets_load_music(tec_assets_storage_t * resources, char const * asset)
{

}


/*=======================

CONFIG/JSON/BYTE DATA

========================*/
bool 
tec_assets_load_config(tec_assets_storage_t * resources, char const * asset)
{

}

bool 
tec_assets_load_json(tec_assets_storage_t * resources, char const * asset)
{

}


/*

ASSET RETRIEVAL

*/

tec_assets_reference_fragment_shader_t
tec_assets_find_fragment_shader(tec_assets_storage_t * resources, char const * fragment_shader)
{
	int result = bfstack_tec_fragment_shader_t_16_search_linear(&resources->fragment_shaders, fragment_shader);

	if (result == -1)
	{
		tec_log_warn("Couldn't find fragment shader \"%s\"", fragment_shader);
		tec_assets_reference_fragment_shader_t ref = {.asset_location = SIZE_MAX, .status = TEC_ASSET_MISSING};
		return ref;
	}
	else
	{
		tec_log_info("Located fragment shader \"%s\" in slot %d.", fragment_shader, result);
		size_t location = bfstack_tec_fragment_shader_t_16_get_location(&resources->fragment_shaders, result);
		tec_assets_reference_fragment_shader_t ref = {.asset_location = location, .status = TEC_ASSET_PRESENT};
		return ref;
	}
}

tec_assets_reference_vertex_shader_t
tec_assets_find_vertex_shader(tec_assets_storage_t * resources, char const * vertex_shader)
{
	int result = bfstack_tec_vertex_shader_t_16_search_linear(&resources->vertex_shaders, vertex_shader);

	if (result == -1)
	{
		tec_log_warn("Couldn't find vertex shader \"%s\"", vertex_shader);
		tec_assets_reference_vertex_shader_t ref = {.asset_location = SIZE_MAX, .status = TEC_ASSET_MISSING};
		return ref;
	}
	else
	{
		tec_log_info("Located vertex shader \"%s\" in slot %d.", vertex_shader, result);
		size_t location = bfstack_tec_vertex_shader_t_16_get_location(&resources->vertex_shaders, result);
		tec_assets_reference_vertex_shader_t ref = {.asset_location = location, .status = TEC_ASSET_PRESENT};
		return ref;
	}
}

tec_assets_reference_compiled_pipeline_t
tec_assets_find_compiled_pipeline(tec_assets_storage_t * resources, char const * pipeline)
{
	int result = bfstack_tec_pipeline_data_t_64_search_linear(&resources->pipelines, pipeline);

	if (result == -1)
	{
		tec_log_warn("Couldn't find pipeline \"%s\"", pipeline);
		tec_assets_reference_compiled_pipeline_t ref = {.asset_location = SIZE_MAX, .status = TEC_ASSET_MISSING};
		return ref;
	}
	else
	{
		tec_log_info("Located pipeline \"%s\" in slot %d.", pipeline, result);
		size_t location = bfstack_tec_pipeline_data_t_64_get_location(&resources->pipelines, result);
		tec_assets_reference_compiled_pipeline_t ref = {.asset_location = location, .status = TEC_ASSET_PRESENT};
		return ref;
	}
}

tec_assets_reference_texture_t
tec_assets_find_texture(tec_assets_storage_t * resources, char const * texture)
{
	int result = bfstack_tec_texture_t_64_search_linear(&resources->textures, texture);

	if (result == -1)
	{
		tec_log_warn("Couldn't find texture \"%s\"", texture);
		tec_assets_reference_texture_t ref = {.asset_location = SIZE_MAX, .status = TEC_ASSET_MISSING};
		return ref;
	}
	else
	{
		tec_log_info("Located texture \"%s\" in slot %d.", texture, result);
		size_t location = bfstack_tec_texture_t_64_get_location(&resources->textures, result);
		tec_assets_reference_texture_t ref = {.asset_location = location, .status = TEC_ASSET_PRESENT};
		return ref;
	}
}

tec_assets_reference_material_t
tec_assets_find_material(tec_assets_storage_t * resources, char const * material)
{
	int result = bfstack_tec_material_t_64_search_linear(&resources->materials, material);

	if (result == -1)
	{
		tec_log_warn("Couldn't find material \"%s\"", material);
		tec_assets_reference_material_t ref = {.asset_location = SIZE_MAX, .status = TEC_ASSET_MISSING};
		return ref;
	}
	else
	{
		tec_log_info("Located material \"%s\" in slot %d.", material, result);
		size_t location = bfstack_tec_material_t_64_get_location(&resources->materials, result);
		tec_assets_reference_material_t ref = {.asset_location = location, .status = TEC_ASSET_PRESENT};
		return ref;
	}
}



tec_fragment_shader_t * 
tec_internal_assets_retrieve_fragment_shader_data_location(tec_assets_storage_t * resources, tec_assets_reference_fragment_shader_t ref)
{
	assert(ref.status == TEC_ASSET_PRESENT && "Tried to retrieve a non-existent fragment shader.");
	return &resources->fragment_shaders.data[ref.asset_location];
}

tec_vertex_shader_t * 
tec_internal_assets_retrieve_vertex_shader_data_location(tec_assets_storage_t * resources, tec_assets_reference_vertex_shader_t ref)
{
	assert(ref.status == TEC_ASSET_PRESENT && "Tried to retrieve a non-existent vertex shader.");
	return &resources->vertex_shaders.data[ref.asset_location];
}

tec_pipeline_data_t * 
tec_internal_assets_retrieve_compiled_pipeline_data_location(tec_assets_storage_t * resources, tec_assets_reference_compiled_pipeline_t ref)
{
	assert(ref.status == TEC_ASSET_PRESENT && "Tried to retrieve a non-existent compiled pipeline");
	return &resources->pipelines.data[ref.asset_location];
}

tec_texture_t * 
tec_internal_assets_retrieve_texture_data_location(tec_assets_storage_t * resources, tec_assets_reference_texture_t ref)
{
	assert(ref.status == TEC_ASSET_PRESENT && "Tried to retrieve a non-existent texture.");
	return &resources->textures.data[ref.asset_location];
}

tec_material_t * 
tec_internal_assets_retrieve_material_data_location(tec_assets_storage_t * resources, tec_assets_reference_material_t ref)
{
	assert(ref.status == TEC_ASSET_PRESENT && "Tried to retrieve a non-existent material");
	return &resources->materials.data[ref.asset_location];
}




void 
tec_assets_initialize(tec_assets_storage_t * resources)
{
	tec_log_info("Initializing asset storage...");
	bfstack_tec_texture_t_64_init(&resources->textures, "Texture Storage");
	bfstack_tec_vertex_shader_t_16_init(&resources->vertex_shaders, "Vertex Shader Storage");
	bfstack_tec_fragment_shader_t_16_init(&resources->fragment_shaders, "Fragment Shader Storage");
	bfstack_tec_material_t_64_init(&resources->materials, "Material Storage");
	bfstack_tec_pipeline_data_t_64_init(&resources->pipelines, "Pipeline Storage");
	tec_log_info("Asset storage initialized");

	//sfx
	//music, etc.
}


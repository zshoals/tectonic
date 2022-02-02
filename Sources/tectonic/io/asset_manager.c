#include "asset_manager.h"
#include "../debug/log.h"
#include "kinc/io/filereader.h"
#include "../frequent.h"

#include "kinc/graphics4/shader.h"
#include "kinc/image.h"
#include "kinc/graphics4/texture.h"

#define TEC_LOG_MODULE_NAME "Asset Loader"

// local_func tec_byte_t *
// memory_allocate(tec_asset_manager_storage_t * resources, size_t size)
// {

// }

local_func bool
asset_can_be_loaded(char const * asset)
{
	tec_log_info("Checking if asset \"%s\" is loadable...", asset);
	kinc_file_reader_t reader;
	
	bool loadable = false;
	if(kinc_file_reader_open(&reader, asset, KINC_FILE_TYPE_ASSET))
	{
		tec_log_info("Successfully opened asset \"%s\".", asset);
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
tec_asset_manager_load_fragment(tec_asset_manager_storage_t * resources, char const * asset)
{
	if (asset_can_be_loaded(asset))
	{
		tec_fragment_shader_t frag;
		size_t size = load_asset(&resources->resource_loading_buffer, asset);
		tec_pipeline_initialize_fragment_shader(&frag, asset, &resources->resource_loading_buffer, size);
		tec_pipeline_compile_fragment_shader(&frag);

		bfstack_tec_fragment_shader_t_16_push(&resources->fragment_programs, frag);

		return true;
	}
	return false;
}

bool 
tec_asset_manager_load_vertex(tec_asset_manager_storage_t * resources, char const * asset)
{
	if (asset_can_be_loaded(asset))
	{
		tec_vertex_shader_t vert;
		size_t size = load_asset(&resources->resource_loading_buffer, asset);
		tec_pipeline_initialize_vertex_shader(&vert, asset, &resources->resource_loading_buffer, size);
		tec_pipeline_compile_vertex_shader(&vert);
		
		bfstack_tec_vertex_shader_t_16_push(&resources->vertex_programs, vert);

		return true;
	}
	return false;
}

bool 
tec_asset_manager_register_pipeline(tec_asset_manager_storage_t * resources, char const * pipeline)
{

}

bool 
tec_asset_manager_register_material(tec_asset_manager_storage_t * resources, char const * material)
{

}

/*=======================

IMAGES

========================*/

bool 
tec_asset_manager_load_image_to_texture(tec_asset_manager_storage_t * resources, char const * asset)
{
	if (asset_can_be_loaded(asset))
	{
		kinc_image_t image;
		size_t size = kinc_image_init_from_file(&image, &resources->resource_loading_buffer, asset);

		tec_texture_t tex;
		tex.name = asset;
		kinc_g4_texture_init_from_image(&tex.texture, &image);

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
tec_asset_manager_load_sfx(tec_asset_manager_storage_t * resources, char const * asset)
{

}

bool 
tec_asset_manager_load_music(tec_asset_manager_storage_t * resources, char const * asset)
{

}


/*=======================

CONFIG/JSON/BYTE DATA

========================*/
bool 
tec_asset_manager_load_config(tec_asset_manager_storage_t * resources, char const * asset)
{

}

bool 
tec_asset_manager_load_json(tec_asset_manager_storage_t * resources, char const * asset)
{

}



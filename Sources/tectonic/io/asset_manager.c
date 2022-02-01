#include "asset_manager.h"
#include "../debug/log.h"
#include "kinc/io/filereader.h"
#include "../frequent.h"

#define TEC_LOG_MODULE_NAME "Asset Loader"

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

local_func bool 
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
		return true;
	}
	else 
	{
		tec_log_warn("Failed to open asset \"%s\".", asset);
		return false;
	}
}

local_func bool 
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
		return true;
	}
	else 
	{
		tec_log_warn("Failed to open save \"%s\".", asset);
		return false;
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
		frag.name = asset;
		load_asset(&frag.bytes, asset);
		bfstack_tec_fragment_shader_t_16_push(&resources->fragment_programs, frag);
	}
}

bool 
tec_asset_manager_load_vertex(tec_asset_manager_storage_t * resources, char const * asset)
{
	if (asset_can_be_loaded(asset))
	{
		tec_fragment_shader_t vert;
		vert.name = asset;
		load_asset(&vert.bytes, asset);
		bfstack_tec_fragment_shader_t_16_push(&resources->fragment_programs, vert);
	}
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
tec_asset_manager_load_image(tec_asset_manager_storage_t * resources, char const * asset)
{

}

bool 
tec_asset_manager_unload_image(tec_asset_manager_storage_t * resources, char const * asset)
{

}

bool 
tec_asset_manager_register_texture(tec_asset_manager_storage_t * resources, char const * texture)
{

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



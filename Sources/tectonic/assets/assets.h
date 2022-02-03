#pragma once

#include "../util/memkit.h"
#include <stdbool.h>

#include "../graphics/pipelines.h"
#include "../graphics/material.h"
#include "../graphics/texture.h"
#include "assets_references.h"

#include "../type_declarations.h"


//Resource manager?

typedef enum
{
	TEC_ASSET_TYPE_FRAGMENT_SHADER,
	TEC_ASSET_TYPE_VERTEX_SHADER,

	TEC_ASSET_TYPE_IMAGE,

	TEC_ASSET_TYPE_SFX,
	TEC_ASSET_TYPE_MUSIC,

	TEC_ASSET_TYPE_CONFIG,
	TEC_ASSET_TYPE_JSON,
}
tec_assets_asset_type_e;

//This is our primary data container
//It needs to hold enough memory to contain the entire game state
//Sketchy stuff

//Only this struct contains the "hard copies" of data
//Anything else needing something from this container should reference by pointer or index preferably
typedef struct
tec_assets_storage
{
	//66 megabytes of space allocated to load images in particular, a 4096x4096 image takes up 64mb but we give a little bit of headroom just in case
	tec_byte_t resource_loading_buffer[TEC_MEGABYTES(66)];

	bfstack_tec_pipeline_data_t_64 pipelines;
	bfstack_tec_vertex_shader_t_16 vertex_shaders;
	bfstack_tec_fragment_shader_t_16 fragment_shaders;
	bfstack_tec_texture_t_64 textures;
	bfstack_tec_material_t_64 materials;

	//Render Target / Surface container
	
	//SFX container
	
	//Music location container
	
	//config container
	//json container
}
tec_assets_storage_t;

void tec_assets_initialize(tec_assets_storage_t * resources);

//attempts to load an asset, returns false if not found
bool tec_assets_load_fragment_shader(tec_assets_storage_t * resources, char const * asset);
bool tec_assets_load_vertex_shader(tec_assets_storage_t * resources, char const * asset);

bool tec_assets_load_image_to_texture(tec_assets_storage_t * resources, char const * asset);

bool tec_assets_load_sfx(tec_assets_storage_t * resources, char const * asset);
bool tec_assets_load_music(tec_assets_storage_t * resources, char const * asset);

bool tec_assets_load_config(tec_assets_storage_t * resources, char const * asset);
bool tec_assets_load_json(tec_assets_storage_t * resources, char const * asset);

//Register functions ==COPY== all relevant data to the asset store
//This shouldn't work like this
//We should grant the user a slot from the data store to work with, we shouldn't copy some other data into a store
bool tec_assets_register_compiled_pipeline(tec_assets_storage_t * resources, tec_pipeline_data_t pipeline);
bool tec_assets_register_material(tec_assets_storage_t * resources, tec_material_t material);

//Probably not needed, we'll just load images directly to the GPU immediately
//Might need to be reworked to check various images on the disk
//If we detect an image on disk, we can then do a load for it
//Basically "load_images" stores references to images that are on the drive, but doesn't actually load the image necessarily
//All loading will just immediately push to the gpu
//bool tec_assets__register_texture(tec_assets_storage_t * resources, tec_texture_t texture);

/*
	Locating asset functions
*/

//Null if nothing found
tec_assets_reference_fragment_shader_t tec_assets_find_fragment_shader(tec_assets_storage_t * resources, char const * fragment_shader);
tec_assets_reference_vertex_shader_t tec_assets_find_vertex_shader(tec_assets_storage_t * resources, char const * vertex_shader);
tec_assets_reference_compiled_pipeline_t tec_assets_find_compiled_pipeline(tec_assets_storage_t * resources, char const * pipeline);
tec_assets_reference_texture_t tec_assets_find_texture(tec_assets_storage_t * resources, char const * texture);
tec_assets_reference_material_t tec_assets_find_material(tec_assets_storage_t * resources, char const * material);

tec_fragment_shader_t * tec_internal_assets_retrieve_fragment_shader_data_location(tec_assets_storage_t * resources, tec_assets_reference_fragment_shader_t ref);
tec_vertex_shader_t * tec_internal_assets_retrieve_vertex_shader_data_location(tec_assets_storage_t * resources, tec_assets_reference_vertex_shader_t ref);
tec_pipeline_data_t * tec_internal_assets_retrieve_compiled_pipeline_data_location(tec_assets_storage_t * resources, tec_assets_reference_compiled_pipeline_t ref);
tec_texture_t * tec_internal_assets_retrieve_texture_data_location(tec_assets_storage_t * resources, tec_assets_reference_texture_t ref);
tec_material_t * tec_internal_assets_retrieve_material_data_location(tec_assets_storage_t * resources, tec_assets_reference_material_t ref);
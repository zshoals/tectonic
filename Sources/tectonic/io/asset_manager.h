#pragma once

#include "../util/memkit.h"
#include <stdbool.h>

#include "../graphics/pipelines.h"

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
tec_asset_manager_asset_type_e;

//This is our primary data container
//It needs to hold enough memory to contain the entire game state
//Sketchy stuff

typedef struct
tec_asset_manager_storage
{
	//66 megabytes of space allocated to load images in particular, a 4096x4096 image takes up 64mb but we give a little bit of headroom just in case
	tec_byte_t resouce_loading_buffer[TEC_MEGABYTES(66)];

	bfstack_tec_vertex_shader_t_16 vertex_programs;
	bfstack_tec_fragment_shader_t_16 fragment_programs;
	//Image container
	//Texture container
	
	//SFX container
	
	//Music location container
	//Fragment container
	//Vertex container
	//material container
	//pipelines containe
	
	//config container
	//json container
}
tec_asset_manager_storage_t;

//attempts to load an asset, returns false if not found
bool tec_asset_manager_load_fragment(tec_asset_manager_storage_t * resources, char const * asset);
bool tec_asset_manager_load_vertex(tec_asset_manager_storage_t * resources, char const * asset);

bool tec_asset_manager_load_image(tec_asset_manager_storage_t * resources, char const * asset);
bool tec_asset_manager_unload_image(tec_asset_manager_storage_t * resources, char const * asset);

bool tec_asset_manager_load_sfx(tec_asset_manager_storage_t * resources, char const * asset);
bool tec_asset_manager_load_music(tec_asset_manager_storage_t * resources, char const * asset);

bool tec_asset_manager_load_config(tec_asset_manager_storage_t * resources, char const * asset);
bool tec_asset_manager_load_json(tec_asset_manager_storage_t * resources, char const * asset);

bool tec_asset_manager_register_pipeline(tec_asset_manager_storage_t * resources, char const * pipeline);
bool tec_asset_manager_register_material(tec_asset_manager_storage_t * resources, char const * material);
bool tec_asset_manager_register_texture(tec_asset_manager_storage_t * resources, char const * texture);
#pragma once

#include "../util/memkit.h"
#include <stdbool.h>

#include "../graphics/pipelines.h"
#include "../graphics/texture.h"
#include "../graphics/material.h"

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

#define TEC_MAX_SHADERS 16
#define TEC_MAX_TEXTURES 64
#define TEC_MAX_MATERIALS 64
#define TEC_MAX_PIPELINES 64

#define template_type tec_pipeline_data_t
#define template_array_size TEC_MAX_PIPELINES
#define template_searchable
#include "../ds/bfstack.h"

#define template_type tec_vertex_shader_t
#define template_array_size TEC_MAX_SHADERS
#define template_searchable
#include "../ds/bfstack.h"

#define template_type tec_fragment_shader_t
#define template_array_size TEC_MAX_SHADERS
#define template_searchable
#include "../ds/bfstack.h"

#define template_type tec_texture_t
#define template_array_size TEC_MAX_TEXTURES
#define template_searchable
#include "../ds/bfstack.h"

#define template_type tec_material_t
#define template_array_size TEC_MAX_MATERIALS
#define template_searchable
#include "../ds/bfstack.h"


//Only this struct contains the "hard copies" of data
//Anything else needing something from this container should reference by pointer or index preferably
typedef struct
tec_asset_manager_storage
{
	//66 megabytes of space allocated to load images in particular, a 4096x4096 image takes up 64mb but we give a little bit of headroom just in case
	tec_byte_t resource_loading_buffer[TEC_MEGABYTES(66)];

	bfstack_tec_pipeline_data_t_64 pipelines;
	bfstack_tec_vertex_shader_t_16 vertex_shaders;
	bfstack_tec_fragment_shader_t_16 fragment_shaders;
	bfstack_tec_texture_t_64 textures;
	bfstack_tec_material_t_64 materials;
	
	//SFX container
	
	//Music location container
	
	//config container
	//json container
}
tec_asset_manager_storage_t;

void tec_asset_manager_initialize(tec_asset_manager_storage_t * resources);

//attempts to load an asset, returns false if not found
bool tec_asset_manager_load_fragment(tec_asset_manager_storage_t * resources, char const * asset);
bool tec_asset_manager_load_vertex(tec_asset_manager_storage_t * resources, char const * asset);

bool tec_asset_manager_load_image_to_texture(tec_asset_manager_storage_t * resources, char const * asset);

bool tec_asset_manager_load_sfx(tec_asset_manager_storage_t * resources, char const * asset);
bool tec_asset_manager_load_music(tec_asset_manager_storage_t * resources, char const * asset);

bool tec_asset_manager_load_config(tec_asset_manager_storage_t * resources, char const * asset);
bool tec_asset_manager_load_json(tec_asset_manager_storage_t * resources, char const * asset);

bool tec_asset_manager_register_pipeline(tec_asset_manager_storage_t * resources, tec_pipeline_data_t pipeline);
bool tec_asset_manager_register_material(tec_asset_manager_storage_t * resources, tec_material_t material);
bool tec_asset_manager_register_texture(tec_asset_manager_storage_t * resources, tec_texture_t texture);

/*
	Locating asset functions
*/

//Null if nothing found
tec_fragment_shader_t * tec_asset_manager_find_fragment(tec_asset_manager_storage_t * resources, char const * fragment_shader);
tec_vertex_shader_t * tec_asset_manager_find_vertex(tec_asset_manager_storage_t * resources, char const * vertex_shader);
tec_pipeline_data_t * tec_asset_manager_find_pipeline(tec_asset_manager_storage_t * resources, char const * pipeline);
tec_texture_t * tec_asset_manager_find_texture(tec_asset_manager_storage_t * resources, char const * texture);
tec_material_t * tec_asset_manager_find_material(tec_asset_manager_storage_t * resources, char const * material);
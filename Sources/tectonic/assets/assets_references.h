#pragma once

#include <stddef.h>
/*

This interface is for the "user" side of the codebase.
Internally, various parts of Tectonic will "dereference" the reference, and grab the image from the asset storage location
PASS IN THE ASSET STORAGE REEE

*/

typedef enum
{
	TEC_ASSET_MISSING,
	TEC_ASSET_PRESENT,
}
tec_assets_reference_status_e;


typedef struct
tec_assets_reference_fragment
{
	size_t const asset_location;
	tec_assets_reference_status_e const status;
}
tec_assets_reference_fragment_shader_t;

typedef struct
tec_assets_reference_vertex_shader
{
	size_t const asset_location;
	tec_assets_reference_status_e const status;
}
tec_assets_reference_vertex_shader_t;

typedef struct
tec_assets_reference_compiled_pipeline
{
	size_t const asset_location;
	tec_assets_reference_status_e const status;
}
tec_assets_reference_compiled_pipeline_t;

typedef struct
tec_assets_reference_texture
{
	size_t const asset_location;
	tec_assets_reference_status_e const status;
}
tec_assets_reference_texture_t;

typedef struct
tec_assets_reference_material
{
	size_t const asset_location;
	tec_assets_reference_status_e const status;
}
tec_assets_reference_material_t;
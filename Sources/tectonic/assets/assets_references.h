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
tec_assref_status_e;


typedef struct
tec_assref_fragment
{
	size_t const asset_location;
	tec_assref_status_e const status;
}
tec_assref_fragment_shader_t;

typedef struct
tec_assref_vertex_shader
{
	size_t const asset_location;
	tec_assref_status_e const status;
}
tec_assref_vertex_shader_t;

typedef struct
tec_assref_compiled_pipeline
{
	size_t const asset_location;
	tec_assref_status_e const status;
}
tec_assref_shader_program_t;

typedef struct
tec_assref_texture
{
	size_t const asset_location;
	tec_assref_status_e const status;
}
tec_assref_texture_t;

typedef struct
tec_assref_material
{
	size_t const asset_location;
	tec_assref_status_e const status;
}
tec_assref_material_t;
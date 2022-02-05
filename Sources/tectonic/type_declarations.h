#pragma once

#define TEC_MAX_SHADERS 16
#define TEC_MAX_TEXTURES 64
#define TEC_MAX_MATERIALS 64
#define TEC_MAX_PIPELINES 64

#define template_type tec_pipeline_data_t
#define template_array_size TEC_MAX_PIPELINES
#define template_searchable
#include "ds/bfstack.h"

#define template_type tec_vertex_shader_t
#define template_array_size TEC_MAX_SHADERS
#define template_searchable
#include "ds/bfstack.h"

#define template_type tec_fragment_shader_t
#define template_array_size TEC_MAX_SHADERS
#define template_searchable
#include "ds/bfstack.h"

#define template_type tec_texture_t
#define template_array_size TEC_MAX_TEXTURES
#define template_searchable
#include "ds/bfstack.h"

#define template_type tec_material_t
#define template_array_size TEC_MAX_MATERIALS
#define template_searchable
#include "ds/bfstack.h"
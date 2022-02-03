#include "pipelines.h"
#include <assert.h>
#include <stddef.h>
#include "kinc/graphics4/pipeline.h"
#include "kinc/graphics4/vertexstructure.h"
#include "kinc/graphics4/shader.h"
#include "../util/memkit.h"
#include "../assets/assets.h"
#include "../assets/assets_references.h"
#include "../debug/log.h"

tec_assref_shader_program_t
tec_pipeline_create_program
(
	tec_assets_storage_t * assets, 
	char const * name, 
	tec_assref_vertex_shader_t vert,
	tec_assref_fragment_shader_t frag, 
	kinc_g4_vertex_structure_t vs, 
	tec_pipeline_blending_e blend_mode
)
{
	tec_assref_shader_program_t shader_location = tec_internal_assets_acquire_shader_program_free_slot(assets);
	tec_pipeline_data_t * pipeline = tec_internal_assets_retrieve_shader_program_data_location(assets, shader_location);

	pipeline->name = name;
	pipeline->vertex_structure = vs;

	kinc_g4_pipeline_init(&pipeline->pipeline);

	pipeline->pipeline.input_layout[0] = &pipeline->vertex_structure;
	pipeline->pipeline.input_layout[1] = NULL;
	pipeline->pipeline.vertex_shader = &vert;
	pipeline->pipeline.fragment_shader = &frag;

	tec_internal_pipeline_blend_mode_helper(&pipeline->pipeline, TEC_BLENDING_NORMAL);

	tec_log_info("Created shader program %s.", pipeline->name);

	return shader_location;
}

void 
tec_pipeline_compile_program(tec_assets_storage_t * assets, tec_assref_shader_program_t program)
{
	tec_pipeline_data_t * pipe = tec_internal_assets_retrieve_shader_program_data_location(assets, program);
	kinc_g4_pipeline_compile(&pipe->pipeline);
	tec_log_info("Compiled shader program %s.", pipe->name);
}

void
tec_pipeline_blend_mode_helper(kinc_g4_pipeline_t * pipeline, tec_pipeline_blending_e blending_mode)
{
	switch (blending_mode)
	{
		case TEC_BLENDING_DISABLED:
			pipeline->blend_source = KINC_G4_BLEND_ONE;
			pipeline->blend_destination = KINC_G4_BLEND_ZERO;
			break;

		case TEC_BLENDING_NORMAL:
			pipeline->blend_source = KINC_G4_BLEND_ONE;
			pipeline->blend_destination = KINC_G4_BLEND_INV_SOURCE_ALPHA;
			break;

		case TEC_BLENDING_ADD:
			pipeline->blend_source = KINC_G4_BLEND_ONE;
			pipeline->blend_destination = KINC_G4_BLEND_ONE;
			break;

		case TEC_BLENDING_MULTIPLY:
			pipeline->blend_source = KINC_G4_BLEND_DEST_COLOR;
			pipeline->blend_destination = KINC_G4_BLEND_INV_SOURCE_ALPHA;
			break;

		case TEC_BLENDING_MASK_WITH_COLOR:
			pipeline->blend_source = KINC_G4_BLEND_SOURCE_ALPHA;
			pipeline->blend_destination = KINC_G4_BLEND_SOURCE_ALPHA;
			break;

		case TEC_BLENDING_MASK:
			pipeline->blend_source = KINC_G4_BLEND_ZERO;
			pipeline->blend_destination = KINC_G4_BLEND_SOURCE_ALPHA;
			break;
		
		default:
			assert(0 && "Should not be able to reach default in blend_mode_helper");
	}

}


void tec_pipeline_initialize_fragment_shader(tec_fragment_shader_t * frag, char const * name, tec_byte_t * copy_from, size_t data_length)
{
	frag->name = name;
	frag->data_length = data_length;
	memcpy(&frag->data, copy_from, data_length);
}
void tec_pipeline_initialize_vertex_shader(tec_vertex_shader_t * vert, char const * name, tec_byte_t * copy_from, size_t data_length)
{
	vert->name = name;
	vert->data_length = data_length;
	memcpy(&vert->data, copy_from, data_length);
};

void 
tec_pipeline_compile_fragment_shader(tec_fragment_shader_t * frag)
{
	kinc_g4_shader_init(&frag->frag, &frag->data, frag->data_length, KINC_G4_SHADER_TYPE_FRAGMENT);
}

void 
tec_pipeline_compile_vertex_shader(tec_vertex_shader_t * vert)
{
	kinc_g4_shader_init(&vert->vert, &vert->data, vert->data_length, KINC_G4_SHADER_TYPE_VERTEX);
}

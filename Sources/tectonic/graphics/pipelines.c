#include "pipelines.h"
#include <assert.h>
#include "kinc/graphics4/pipeline.h"
#include "../util/memkit.h"
#include <stddef.h>
#include "kinc/graphics4/vertexstructure.h"
#include "kinc/graphics4/shader.h"

tec_pipeline_data_t 
tec_pipeline_create_program(char const * name, tec_vertex_shader_t * vert, tec_fragment_shader_t * frag, kinc_g4_vertex_structure_t vs, tec_pipeline_blending_e blend_mode)
{
	kinc_g4_pipeline_t kpipe;

	tec_pipeline_data_t pipeline;
	pipeline.name = name;
	pipeline.vertex_structure = vs;
	pipeline.pipeline = kpipe;

	kinc_g4_pipeline_init(&pipeline.pipeline);

	pipeline.pipeline.input_layout[0] = &pipeline.vertex_structure;
	pipeline.pipeline.input_layout[1] = NULL;
	pipeline.pipeline.vertex_shader = &vert;
	pipeline.pipeline.fragment_shader = &frag;

	tec_pipeline_blend_mode_helper(&pipeline.pipeline, TEC_BLENDING_NORMAL);

	return pipeline;
}

void 
tec_pipeline_compile_program(tec_pipeline_data_t * program)
{
	kinc_g4_pipeline_compile(&program->pipeline);
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

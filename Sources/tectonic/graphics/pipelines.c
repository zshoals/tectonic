#include "pipelines.h"
#include <assert.h>
#include "kinc/graphics4/pipeline.h"
#include "../util/memkit.h"
#include "kinc/io/filereader.h"
#include <stddef.h>
#include "kinc/graphics4/vertexstructure.h"

tec_byte_t * vert_shader;
tec_byte_t * frag_shader;
kinc_g4_vertex_structure_t vert_format;

void
load_textured_vert_and_frag(void)
{
	{
		kinc_file_reader_t reader_vert;
		kinc_file_reader_open(&reader_vert, "textured-standard.vert", KINC_FILE_TYPE_ASSET);
		size_t size_vert = kinc_file_reader_size(&reader_vert);
		vert_shader = malloc(size_vert);
		kinc_file_reader_read(&reader_vert, vert_shader, size_vert);
		kinc_file_reader_close(&reader_vert);
	}

	{
		kinc_file_reader_t reader_frag;
		kinc_file_reader_open(&reader_frag, "textured-standard.frag", KINC_FILE_TYPE_ASSET);
		size_t size_frag = kinc_file_reader_size(&reader_frag);
		frag_shader = malloc(size_frag);
		kinc_file_reader_read(&reader_frag, frag_shader, size_frag);
		kinc_file_reader_close(&reader_frag);
	}
}

kinc_g4_pipeline_t 
tec_pipeline_create_default_textured(void)
{
	load_textured_vert_and_frag();

	kinc_g4_vertex_structure_init(&vert_format);
	kinc_g4_vertex_structure_add(&vert_format, "vertexPosition", KINC_G4_VERTEX_DATA_FLOAT3);
	kinc_g4_vertex_structure_add(&vert_format, "vertexColor", KINC_G4_VERTEX_DATA_FLOAT4);
	kinc_g4_vertex_structure_add(&vert_format, "projectionMatrix", KINC_G4_VERTEX_DATA_FLOAT4X4);

	kinc_g4_pipeline_t program;
	kinc_g4_pipeline_init(&program);

	program.vertex_shader = vert_shader;
	program.fragment_shader = frag_shader;
	program.input_layout[0] = &vert_format;
	program.input_layout[1] = NULL;

	tec_pipeline_blend_mode_helper(&program, TEC_BLENDING_NORMAL);
	
	kinc_g4_pipeline_compile(&program);
}

void
tec_pipeline_blend_mode_helper(kinc_g4_pipeline_t * pipeline, tec_material_pipeline_blending_e blending_mode)
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
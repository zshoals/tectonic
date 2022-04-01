#include "indexed_vertices_buffer.h"
#include <assert.h>

void tec_indexed_vertices_buffer_init(tec_indexed_vertices_buffer_t * ivb, kinc_g4_vertex_structure_t vs, size_t vertex_count, size_t indices_count)
{
	ivb->structure = vs;
	kinc_g4_vertex_buffer_init(&ivb->vbo, vertex_count, &ivb->structure, KINC_G4_USAGE_DYNAMIC, 0);
	kinc_g4_index_buffer_init(&ivb->ibo, indices_count, KINC_G4_INDEX_BUFFER_FORMAT_16BIT, KINC_G4_USAGE_DYNAMIC);
	ivb->vert_data = NULL;
	ivb->indices_data = NULL;
	ivb->verts_current_pos = 0;
	ivb->indices_current_pos = 0;
	ivb->verts_max = vertex_count;
	ivb->indices_max = indices_count;
}

void tec_indexed_vertices_buffer_clear(tec_indexed_vertices_buffer_t * ivb)
{
	ivb->verts_current_pos = 0;
	ivb->indices_current_pos = 0;
}

void tec_indexed_vertices_buffer_lock(tec_indexed_vertices_buffer_t * ivb)
{
	ivb->vert_data = kinc_g4_vertex_buffer_lock_all(&ivb->vbo);
	ivb->indices_data = kinc_g4_index_buffer_lock(&ivb->ibo);
}

void tec_indexed_vertices_buffer_unlock(tec_indexed_vertices_buffer_t * ivb)
{
	kinc_g4_vertex_buffer_unlock_all(&ivb->vbo);
	kinc_g4_index_buffer_unlock(&ivb->ibo);
	ivb->vert_data = NULL;
	ivb->indices_data = NULL;
}

bool tec_indexed_vertices_buffer_assure_room(tec_indexed_vertices_buffer_t * ivb, size_t inbound_vert_data_count, size_t inbound_indices_count)
{
	bool status = true;

	if (ivb->verts_max - ivb->verts_current_pos < inbound_vert_data_count)
	{
		status = false;
	}
	if (ivb->indices_max - ivb->indices_current_pos < inbound_indices_count)
	{
		status = false;
	}

	return status;
}

void tec_indexed_vertices_buffer_push_float1(tec_indexed_vertices_buffer_t * ivb, float v1)
{
	assert(ivb->vert_data != NULL && "IVB was not locked before pushing data");
	ivb->vert_data[ivb->verts_current_pos++] = v1;
}

void tec_indexed_vertices_buffer_push_float2(tec_indexed_vertices_buffer_t * ivb, float v1, float v2)
{
	assert(ivb->vert_data != NULL && "IVB was not locked before pushing data");
	ivb->vert_data[ivb->verts_current_pos++] = v1;
	ivb->vert_data[ivb->verts_current_pos++] = v2;
}

void tec_indexed_vertices_buffer_push_float3(tec_indexed_vertices_buffer_t * ivb, float v1, float v2, float v3)
{
	assert(ivb->vert_data != NULL && "IVB was not locked before pushing data");
	ivb->vert_data[ivb->verts_current_pos++] = v1;
	ivb->vert_data[ivb->verts_current_pos++] = v2;
	ivb->vert_data[ivb->verts_current_pos++] = v3;
}

void tec_indexed_vertices_buffer_make_tri_indices(tec_indexed_vertices_buffer_t * ivb)
{
	assert(ivb->indices_data != NULL && "IVB was not locked before making tri indices");
	for (size_t i = 0; i < 3; i++)
	{
		ivb->indices_data[ivb->indices_current_pos] = ivb->indices_current_pos;
		ivb->indices_current_pos++;
	}
}

void tec_indexed_vertices_buffer_make_rect_indices(tec_indexed_vertices_buffer_t * ivb)
{
	assert(ivb->indices_data != NULL && "IVB was not locked before making rect indices");
	size_t origin = ivb->indices_current_pos;
	//left tri
	ivb->indices_data[ivb->indices_current_pos++] = origin + 0;
	ivb->indices_data[ivb->indices_current_pos++] = origin + 1;
	ivb->indices_data[ivb->indices_current_pos++] = origin + 2;
	//right tri
	ivb->indices_data[ivb->indices_current_pos++] = origin + 2;
	ivb->indices_data[ivb->indices_current_pos++] = origin + 1;
	ivb->indices_data[ivb->indices_current_pos++] = origin + 3;
}

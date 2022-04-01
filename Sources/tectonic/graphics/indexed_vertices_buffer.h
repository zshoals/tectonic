#pragma once

#include <stdbool.h>
#include "kinc/graphics4/vertexbuffer.h"
#include "kinc/graphics4/vertexstructure.h"
#include "kinc/graphics4/indexbuffer.h"

typedef struct 
tec_indexed_vertices_buffer
{
	kinc_g4_vertex_buffer_t vbo;
	kinc_g4_index_buffer_t ibo;
	kinc_g4_vertex_structure_t structure;
	float * vert_data;
	float * indices_data;
	size_t verts_current_pos;
	size_t indices_current_pos;
	size_t verts_max;
	size_t indices_max;
}
tec_indexed_vertices_buffer_t;

//Allocates the various vertex and index buffers with their respective amounts
void tec_indexed_vertices_buffer_init(tec_indexed_vertices_buffer_t * ivb, kinc_g4_vertex_structure_t vs, size_t vertex_count, size_t indices_count);
void tec_indexed_vertices_buffer_clear(tec_indexed_vertices_buffer_t * ivb);

//Lock the vertex and index buffers for writing data. This must be done before pushing data or making shapes
void tec_indexed_vertices_buffer_lock(tec_indexed_vertices_buffer_t * ivb);
//Unlock the vertex and index buffers, making them unavailable for writing.
void tec_indexed_vertices_buffer_unlock(tec_indexed_vertices_buffer_t * ivb);
//Checks if the soon to be added vert data and indexes are within the storage limits for the vertex and index buffers
bool tec_indexed_vertices_buffer_assure_room(tec_indexed_vertices_buffer_t * ivb, size_t inbound_vert_data_count, size_t inbound_indices_count);

void tec_indexed_vertices_buffer_push_float1(tec_indexed_vertices_buffer_t * ivb, float v1);
void tec_indexed_vertices_buffer_push_float2(tec_indexed_vertices_buffer_t * ivb, float v1, float v2);
void tec_indexed_vertices_buffer_push_float3(tec_indexed_vertices_buffer_t * ivb, float v1, float v2, float v3);

void tec_indexed_vertices_buffer_make_tri_indices(tec_indexed_vertices_buffer_t * ivb);
void tec_indexed_vertices_buffer_make_rect_indices(tec_indexed_vertices_buffer_t * ivb);
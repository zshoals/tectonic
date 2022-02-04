#include "matrix.h"
#include "kinc/math/matrix.h"

kinc_matrix4x4_t 
tec_matrix_convert(hmm_m4 matrix)
{
	kinc_matrix4x4_t out;
	
	kinc_matrix4x4_set(&out, 0, 0, matrix.Elements[0][0]);
	kinc_matrix4x4_set(&out, 0, 1, matrix.Elements[0][1]);
	kinc_matrix4x4_set(&out, 0, 2, matrix.Elements[0][2]);
	kinc_matrix4x4_set(&out, 0, 3, matrix.Elements[0][3]);
	kinc_matrix4x4_set(&out, 1, 0, matrix.Elements[1][0]);
	kinc_matrix4x4_set(&out, 1, 1, matrix.Elements[1][1]);
	kinc_matrix4x4_set(&out, 1, 2, matrix.Elements[1][2]);
	kinc_matrix4x4_set(&out, 1, 3, matrix.Elements[1][3]);
	kinc_matrix4x4_set(&out, 2, 0, matrix.Elements[2][0]);
	kinc_matrix4x4_set(&out, 2, 1, matrix.Elements[2][1]);
	kinc_matrix4x4_set(&out, 2, 2, matrix.Elements[2][2]);
	kinc_matrix4x4_set(&out, 2, 3, matrix.Elements[2][3]);
	kinc_matrix4x4_set(&out, 3, 0, matrix.Elements[3][0]);
	kinc_matrix4x4_set(&out, 3, 1, matrix.Elements[3][1]);
	kinc_matrix4x4_set(&out, 3, 2, matrix.Elements[3][2]);
	kinc_matrix4x4_set(&out, 3, 3, matrix.Elements[3][3]);

	return out;
}

//It is a genuine mystery why this isn't in HMM to begin with.
//It is actually but with a dumb name.
hmm_m4 
HMM_Mat4Identity(void)
{
	return HMM_Mat4d(1.0);
}
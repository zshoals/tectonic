#pragma once

#include "../lib/HandmadeMath.h"
#include "kinc/math/matrix.h"
#include <string.h>

kinc_matrix4x4_t tec_matrix_convert(hmm_m4 matrix)
{
	kinc_matrix4x4_t out;
	//Might work...
	memcpy(&out, &matrix, 16);

	return out;
}
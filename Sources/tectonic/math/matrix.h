#pragma once

#include "../lib/HandmadeMath.h"
#include "kinc/math/matrix.h"
#include <string.h>

kinc_matrix4x4_t tec_matrix_convert(hmm_m4 matrix);

//It is a genuine mystery why this isn't in HMM to begin with.
//It is actually but with a dumb name.
hmm_m4 HMM_Mat4Identity(void);
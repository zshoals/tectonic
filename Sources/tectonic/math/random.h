#pragma once

//SFC32

#include <stdint.h>
#include "../frequent.h"

typedef struct
tec_random_state
{
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t counter;
}
tec_random_state_t;

local_data random;

void tec_random_init(uint32_t a, uint32_t b, uint32_t c);
int tec_random_get();
int tec_random_get_in(int min, int max);
void tec_random_get_in_fill(int * buffer, int count, int min, int max);

float tec_random_getf();
float tec_random_get_float_in(int min, int max);
void tec_random_get_float_in_fill(float * buffer, int count, float min, float max);
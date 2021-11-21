#pragma once

#include <stdbool.h>

typedef struct
tec_timediff 
{
	double begin;
	double end;
	bool running;
} 
tec_timediff_t;

void tec_timediff_init(tec_timediff_t * timer);
void tec_timediff_begin(tec_timediff_t * timer, double now);
double tec_timediff_end(tec_timediff_t * timer, double now);
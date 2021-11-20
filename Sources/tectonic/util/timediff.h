#pragma once

typedef struct
tec_timediff 
{
	double previous;
	double current;
} 
tec_timediff_t;

void tec_timediff_init(tec_timediff_t * timer);
void tec_timediff_advance(tec_timediff_t * timer, double now);
double tec_timediff_dt(tec_timediff_t * timer);
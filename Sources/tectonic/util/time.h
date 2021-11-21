#pragma once

typedef struct
tec_time
{
	double previous;
	double current;
	double timescale;
	double result_multiplier;
}
tec_time_t;

void tec_time_init(tec_time_t * time);
void tec_time_update(tec_time_t * time, double now);
void tec_time_set_timescale(tec_time_t * time, double multiplier);
void tec_time_set_result_multiplier(tec_time_t * time, double multiplier);

double tec_time_adjusted(tec_time_t * time);
double tec_time_dt(tec_time_t * time);


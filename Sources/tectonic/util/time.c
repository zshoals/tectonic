#include "time.h"

void 
tec_time_init(tec_time_t * time)
{
	time->previous = 0.0;
	time->current = 0.0;
	time->result_multiplier = 1.0;
	time->timescale = 1.0;
}

void 
tec_time_update(tec_time_t * time, double now)
{
	time->previous = time->current;
	time->current = now;
}

void 
tec_time_set_timescale(tec_time_t * time, double multiplier)
{
	time->timescale = multiplier;
}

void 
tec_time_set_result_multiplier(tec_time_t * time, double multiplier)
{
	time->result_multiplier = multiplier;
}

double 
tec_time_adjusted(tec_time_t * time)
{
	return (tec_time_dt(time) * time->result_multiplier * time->timescale);
}

double 
tec_time_dt(tec_time_t * time)
{
	return time->current - time->previous;
}
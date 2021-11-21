#include "timediff.h"

#include <assert.h>

void 
tec_timediff_init(tec_timediff_t * timer)
{
	timer->begin = 0.0;
	timer->end = 0.0;
	timer->running = false;
}

void
tec_timediff_begin(tec_timediff_t * timer, double now)
{
	assert(timer->running == false && "End timediff before you begin!");
	
	timer->running = true;
	timer->begin = now;
}

double 
tec_timediff_end(tec_timediff_t * timer, double now)
{
	assert((timer->running == true) && "Begin timediff before you end!");

	timer->running = false;
	timer->end = now;

	return timer->end - timer->begin;
}
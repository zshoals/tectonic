#include "timediff.h"

#include <assert.h>

void 
tec_timediff_init(tec_timediff_t * timer)
{
	timer->previous = 0.0;
	timer->current = 0.0;
}

void 
tec_timediff_advance(tec_timediff_t * timer, double now)
{
	timer->previous = timer->current;
	timer->current = now;

	assert(timer->current >= 0 && "Timediff overflow? %f %s %s", timer->current, __FILE__, __LINE__);
}

double 
tec_timediff_dt(tec_timediff_t * timer) 
{
	return timer->current - timer->previous;
}
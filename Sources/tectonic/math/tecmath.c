#include "tecmath.h"

bool 
fequals(float f1, float f2)
{
	return (f1 - f2 < TEC_EPSILON) ? true : false;
}

bool 
iequals(int i1, int i2)
{
	return (i1 == i2);
}

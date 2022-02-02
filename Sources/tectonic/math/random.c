#include "random.h"

local_func inline uint32_t 
raw32()
{
	enum {BARREL_SHIFT = 21, RSHIFT = 9, LSHIFT = 3};//good sets include {21,9,3},{15,8,3}; older versions used {25,8,3} which wasn't as good
	uint32_t tmp = random.a + random.b + random.counter++;
	random.a = random.b ^ (random.b >> RSHIFT);
	random.b = random.c + (random.c << LSHIFT);
	random.c = ((random.c << BARREL_SHIFT) | (random.c >> (32-BARREL_SHIFT))) + tmp;
	return tmp;
}

void
tec_random_init(uint32_t a, uint32_t b, uint32_t c)
{
	random.a = a;
	random.b = b;
	random.c = c;
	random.counter = 1;

	for (int i = 0; i < 15; i++)
	{
		raw32();
	}
}

int 
tec_random_get()
{
	return raw32();
}

int 
tec_random_get_in(int min, int max)
{
	return raw32() % (max + 1 - min) + min;
}

void
tec_random_get_in_fill(int * buffer, int count, int min, int max)
{
	for (int i = 0; i < count; i++)
	{
		buffer[i] = raw32() % (max + 1 - min) + min;
	}
}

float 
tec_random_getf()
{
	return raw32() / (float)0x7FFFFFFF;
}

float 
tec_random_get_float_in(float min, float max)
{
	return min + (raw32() / (float)0x7FFFFFFF) * (max - min);
}

void
tec_random_get_float_in_fill(float * buffer, int count, float min, float max)
{
	for (int i = 0; i < count; i++)
	{
		buffer[i] = min + (raw32() / (float)0x7FFFFFFF) * (max - min);
	}
}

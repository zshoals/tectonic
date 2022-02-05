#include "bits.h"

uint 
tec_bits_set_range(uint bits, size_t start, size_t end, uint value)
{
	uint ones = ~0;
	uint left = ones << (end + 1);
	uint right = ((1 << start) - 1);
	uint mask = left | right;

	uint clear_range = bits & mask;
	uint out = clear_range | (value << start);
	
	return out;
}
uint 
tec_bits_get_range(uint bits, size_t start, size_t end)
{
	return (bits >> start) & ~(~0 << (end - start + 1));
}

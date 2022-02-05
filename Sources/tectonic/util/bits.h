#pragma once

#include <stddef.h>
#include "../frequent.h"

uint tec_bits_set_range(uint bits, size_t start, size_t end, uint value);
uint tec_bits_get_range(uint bits, size_t start, size_t end);
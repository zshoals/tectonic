#pragma once

#include <stdbool.h>

//Contains functions pertaining to "declarative" style programming. That is, making certain operations sound like an English sentence

#define VALUE_IN_RANGE_INCLUSIVE(X, lower_bound, upper_bound) ((lower_bound) <= (X) && (X) <= (upper_bound))
#define VALUE_IN_RANGE_EXCLUSIVE(X, lower_bound, upper_bound) ((lower_bound) <= (X) && (X) < (upper_bound))
//#define VALUE_IN_RANGE_INCLUSIVE_LEFT(X, lower_bound, upper_bound) ((lower_bound) <= (X) && (X) < (upper_bound))
//#define VALUE_IN_RANGE_INCLUSIVE_RIGHT(X, lower_bound, upper_bound) ((lower_bound) < (X) && (X) <= (upper_bound))

#define PTR_NOT_NULL(PTR) ((PTR) != NULL)
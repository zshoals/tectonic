#pragma once

//Int compare example
static inline int int_compare(int * a, int * b)
{
	int n1 = *a;
	int n2 = *b;

	return (n2 < n1) - (n1 < n2);
}
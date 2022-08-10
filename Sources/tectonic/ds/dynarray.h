//no pragma once here, this file is intended to be included several times

#include <assert.h>
#include <stddef.h>

typedef struct dynarray_int
{
	int * data; //Mem slabs should have embedded length?
	size_t length;
	size_t ___next_push;
}
dynarray_int_t;

dynarray_int_t dynarray_int_create(int * buffer, size_t max_length)
{
	return (dynarray_int_t){
		.data = buffer,
		.length = max_length,
		.___next_push = 0
		};
}

int const * dynarray_int_get(dynarray_int_t * array, size_t idx)
{
	assert(idx < array->length);
	return &array->data[idx];
}

int dynarray_int_get_copy(dynarray_int_t * array, size_t idx)
{
	assert(idx < array->length);
	return array->data[idx];
}

void dynarray_int_push(dynarray_int_t * array, int value)
{
	assert(array->___next_push < array->length);
	array->data[array->___next_push] = value;
	array->___next_push++;
}

int dynarray_int_pop(dynarray_int_t * array)
{
	assert(array->___next_push > 0);
	array->___next_push--;
	return array->data[array->___next_push];
	
}

#include "trial_by_fire.h"
#include "test_generic_array.h"

#define ds_type int
#include "tectonic/ds/array.h"

void test_all_generic_array_functions(void)
{
	kinc_log(KINC_LOG_LEVEL_INFO, "====Test Group: Generic Fixed Arrays===");

	TEST("Test creating a simple array and messing with some values",
	{
		tec_bytes buf[10000] = {0};
		allocator_t mem = allocator_create(&buf[0], 10000, ALLOCATOR_MODE_ARENA);

		array_int_t ints;
		array_int_initialize(&ints, &mem, 100);

		for_array(i, &ints)
		{
			array_int_set(&ints, i, i);
		}

		size_t result = 0;
		for_array(i, &ints)
		{
			result += DEREF(array_int_get(&ints, i));
		}

		EXPECTING(
			result == 4950,
			"Added result should equal the iteration of values between 0 and 99",
			""
		);
	});
}
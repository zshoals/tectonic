
#include "trial_by_fire.h"
#include "test_generic_array.h"

#define ds_type int
#include "tectonic/ds/array.h"

void test_all_generic_array_functions(void)
{
	kinc_log(KINC_LOG_LEVEL_INFO, "====Test Group: Generic Fixed Arrays===");

	TEST("Test creating a simple array and pushing and popping values",
	{
		tec_bytes buf[10000] = {0};
		allocator_t mem = allocator_create(&buf[0], 10000, ALLOCATOR_MODE_ARENA);

		array_int_t ints;
		array_int_initalize(&ints, &mem, 100);

		array_int_push(&ints, 66);
		array_int_push(&ints, 6745);
		array_int_push(&ints, 65435);
		array_int_push(&ints, 999);
		
		EXPECTING(
			ints.current_top_offset == 4,
			"Stack offset should be 4 after 4 pushes",
			""
		);

		EXPECTING(
			array_int_pop(&ints) == 999,
			"Popping array values equals the tail end of the array values",
			""
		);

		array_int_pop(&ints);
		array_int_pop(&ints);
		array_int_pop(&ints);

		EXPECTING(
			ints.current_top_offset == 0,
			"Stack offset should be 0",
			""
		);
	});
}
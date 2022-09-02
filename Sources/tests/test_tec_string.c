#include <string.h>
#include "tests/test_tec_string.h"

#include "tectonic/ds/tec_string.h"
#include "tectonic/validation.h"
#include "trial_by_fire.h"

void test_all_tec_string_operations(void)
{
	kinc_log(KINC_LOG_LEVEL_INFO, "====Test Group: Tectonic Strings====");

	TEST("Create a string, do some ops",
	{
		tec_bytes buffer[1024] = {0};
		allocator_t mem = allocator_create(&buffer[0], 1024, ALLOCATOR_MODE_ARENA);

		tec_string_t statement = tec_string_create(&mem, "Hello, this is a string that we have here"); //41 char excluding null term

		EXPECTING(
			statement.length == 41,
			"String length should have been set correctly",
			""
		);

		EXPECTING(
			strncmp(statement.str, "Hello, this is a string that we have here", statement.length) == 0,
			"Strings should have been equivalent after creation, excluding null term",
			""
		);
	});

	TEST("Append a string",
	{
		tec_bytes buffer[1024] = {0};
		allocator_t mem = allocator_create(&buffer[0], 1024, ALLOCATOR_MODE_ARENA);

		tec_string_t a = tec_string_create(&mem, "Hi!");
		tec_string_t b = tec_string_create(&mem, " Bye!");

		tec_string_t combo = tec_string_append(&mem, a, b);

		EXPECTING(
			combo.length == 8,
			"Strings combined should match a length of 8",
			""
		);
	});
}

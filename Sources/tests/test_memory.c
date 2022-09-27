#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "test_memory.h"
#include "trial_by_fire.h"

#include "tectonic/memory/memory.h"
#include "tectonic/ds/allocator.h"

#include "kinc/log.h"

void test_all_memory_operations(void)
{
	kinc_log(KINC_LOG_LEVEL_INFO, "====Test Group: Memory====");

	TEST("Create an allocator from a stack buffer",
	{
		tec_bytes buf[1024] = { 0 };
		allocator_t mem = allocator_create(&buf[0], 1024, ALLOCATOR_MODE_ARENA);
		EXPECTING(&mem != NULL, "Buffer was null", "Optimized out? Creation issue?");
	});

	TEST("Allocate memory and print a message from the region",
	{
		tec_bytes buf[1024] = { 0 };
		allocator_t mem = allocator_create(&buf[0], 1024, ALLOCATOR_MODE_ARENA);
		int * ints = allocator_malloc(&mem, int, 4);
		ints[0] = 99;
		ints[1] = 9;
		ints[2] = 523;
		ints[3] = 99;

		kinc_log(KINC_LOG_LEVEL_INFO, "TEST LOG: Here's some added integers from an allocator: %d, %d, %d, %d", ints[0], ints[1], ints[2], ints[3]);

		EXPECTING(
			(uintptr_t)&ints[0] % tec_alignof(int) == 0 &&
			(uintptr_t)&ints[1] % tec_alignof(int) == 0 &&
			(uintptr_t)&ints[2] % tec_alignof(int) == 0 &&
			(uintptr_t)&ints[3] % tec_alignof(int) == 0,
			"All ints should be aligned to an appropriate memory address",
			""
		);

		EXPECTING(
			mem.memory_top_offset == sizeof(int) * 4,
			"Should have had a memory offset of 4 ints, as that's what we allocated",
			""
		);
	});

	TEST("Allocate memory, perform operations, validate memory sizes and status, and free",
	{
		tec_bytes buf[1024] = { 0 };
		allocator_t mem = allocator_create(&buf[0], 1024, ALLOCATOR_MODE_ARENA);
		unsigned char * string = allocator_malloc(&mem, unsigned char, 500);
		char const * string_test = "This is a long static string, which is spamming now: 64tp890 88grew hioiv m0v47n56027nv5620v26by2vb4ybv6n9v502n7v5032765n2v206vv62n0746v0j 4grew hioiv m0v47n56027nv5620v26by2vb4ybv6n9v502n7v5032765n2v206vv62n0746v0j 44444";

		size_t string_length = strlen(string_test);
		kinc_log(KINC_LOG_LEVEL_INFO, "String length: %zu", string_length);
		for (int i = 0; i < string_length + 1; ++i)
		{
			string[i] = string_test[i];
		}

		EXPECTING(
			strcmp(string, string_test) == 0,
			"The strings should match, the copy should have been valid and in a valid memory region.",
			"Overran buffer? Allocator issue?"
		);

		EXPECTING(
			mem.memory_top_offset == sizeof(unsigned char) * 500,
			"Memory top offset should match the actual allocated amount of unsigned chars",
			""
		);

		EXPECTING(
			mem.memory_size == 1024,
			"We should still have the correct amount of bytes from our initial allocation",
			""
		);

		EXPECTING(
			(uintptr_t)&buf[0] % 16 == 0,
			"With any luck, our stack allocated buffer is 16 byte aligned, otherwise we got some issues",
			""
		);

		//Free all memory right here....
		allocator_free_all(&mem);

		EXPECTING(
			mem.memory_size == 1024 && mem.memory_top_offset == 0,
			"We should still have the same arena max size and the top offset should now be 0",
			""
		);
	});

	TEST("Test malloc'd memory buffer",
	{
		tec_bytes * buffer = malloc(sizeof(tec_bytes) * TEC_KILOBYTES(100));

		allocator_t mem = allocator_create(buffer, sizeof(tec_bytes) * TEC_KILOBYTES(100), ALLOCATOR_MODE_ARENA);

		int * ints = allocator_malloc(&mem, int, 500);
		for (int i = 0; i < 500; ++i)
		{
			ints[i] = 56235;
		}

		float * floats = allocator_malloc(&mem, float, 500);
		for (int i = 0; i < 500; ++i)
		{
			floats[i] = 636463.1004f;
		}

		kinc_log(KINC_LOG_LEVEL_INFO, "Int: %d", ints[55]);
		kinc_log(KINC_LOG_LEVEL_INFO, "Float: %f", floats[55]);
		EXPECTING(
			ints[55] == 56235,
			"Expected the memory location to result in the correctly set int",
			""
		);

		EXPECTING(
			floats[55] == 636463.1004f,
			"Expected the memory location to result in the correctly set float",
			""
		);

		free(buffer);
	});
}

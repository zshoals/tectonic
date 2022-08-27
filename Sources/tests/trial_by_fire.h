
/*
	Simple testing suite
*/
#pragma once

#include <assert.h>
#include "kinc/log.h"

#define EXPECTING(EXPR, EXPECTED_MESSAGE, ERR_MESSAGE) do {\
	assert( (("Expected: " EXPECTED_MESSAGE), ("Possible Issues: " ERR_MESSAGE), (EXPR)) );\
} while (0)

//To use, create a function called by main/some program to run a group of tests, then add test cases as follows:
/*
	TEST("EXAMPLE NAME",
	{
		Do stuff in here...
		assert(Thing == True);
	});
*/
#define TEST(TEST_NAME, TEST_FUNCTION) do { \
	TEST_FUNCTION; \
	kinc_log(KINC_LOG_LEVEL_INFO, "Testing::%s --> Success.", TEST_NAME);\
} while (0)

/*
	Simple testing suite
*/
#pragma once

#include <stdbool.h>
#include <assert.h>
#include "kinc/log.h"


//reset the test_actually_exists flag to false
//Set the test name
//Perform the test and check if it returned true, if it didn't, the test doesn't even exist
//If everything checks out, print a dot
//Else, well, we assert and crash

typedef struct tbf_test
{
	char const * active_test_name;
}
tbf_test_t;

static tbf_test_t active_test = {0};

//To use, create a function to run various tests, then add test cases as follows:
/*
	TEST("EXAMPLE NAME",
	{
		Do stuff in here...
		assert(Thing == True);
	});
*/
#define EXPECTING(EXPR, EXPECTED_MESSAGE, ERR_MESSAGE) do {\
	assert( (("Expected: " EXPECTED_MESSAGE), ("Errored: " ERR_MESSAGE), (EXPR)) );\
} while (0)

#define TEST(TEST_NAME, TEST_FUNCTION) do { \
	active_test.active_test_name = TEST_NAME; \
	TEST_FUNCTION; \
	kinc_log(KINC_LOG_LEVEL_INFO, "Testing::%s --> Success.", active_test.active_test_name);\
} while (0)
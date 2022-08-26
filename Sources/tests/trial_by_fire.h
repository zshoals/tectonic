
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
	bool test_actually_exists;
}
tbf_test_t;

static tbf_test_t active_test = {0};

//Simple testing function. All tests should return a value of "true" when complete.
//Provide a name for the test, and a function taking no parameters, without parenthesis on the function
//Note, The bad path is unlikely to be hit because the compiler will just get angry. It's here just in case though.
#define TEST(TEST_NAME, TEST_FUNCTION) do { \
	active_test.active_test_name = TEST_NAME; \
	active_test.test_actually_exists = false; \
	active_test.test_actually_exists = TEST_FUNCTION(); \
	if (active_test.test_actually_exists) \
	{ \
		kinc_log(KINC_LOG_LEVEL_INFO, "Testing::%s::success.", active_test.active_test_name); \
	} \
	else \
	{ \
		kinc_log(KINC_LOG_LEVEL_ERROR, "MALFORMED TEST, DIDN'T RETURN TRUE OR INCORRECT TEST FUNCTION!!"); \
		assert(0); \
	} \
} while (0)
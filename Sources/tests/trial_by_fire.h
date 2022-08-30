
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
		EXPECTING(Thing == True, Expected_Message, Possible_Issues_Message);
	});
*/
#define TEST(TEST_NAME, TEST_FUNCTION) do { \
	TEST_FUNCTION; \
	kinc_log(KINC_LOG_LEVEL_INFO, "Testing::%s --> Success.", TEST_NAME);\
} while (0)

//Another way to structure tests, but kind of problematic with regards to errors.
//Also, might run into issues with a max amount of characters in a macro or something
// #define TEST_GROUP(GROUP_NAME, TESTS) do { \
// 	kinc_log(KINC_LOG_LEVEL_INFO, "====Test Group: %s====", GROUP_NAME); \
// 	TESTS; \
// } while (0)

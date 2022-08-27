#include <assert.h>
#include <stdbool.h>

#include "test_basics.h"
#include "trial_by_fire.h"


void test_all_integer_basic_operations(void)
{

	TEST("INT ADDITION",
	{
		int a = 1;
		int b = 2;
		int result = a + b;
		EXPECTING(
			result == 3,
			"Proper addition because it's built into the language itself",
			"Somehow the incorrect value came out of what we just did"
		);
	});

	TEST("INT SUBTRACTION",
	{
		int a = 580;
		int b = 80;
		int result = a - b;
		EXPECTING(
			result == 500,
			"Proper subtraction because it's built into the language itself",
			"Somehow the incorrect value came out of what we just did"
		);
	});

	TEST("INT MULTIPLICATION",
	{
		int a = 55;
		int b = 3;
		int result = a * b;
		EXPECTING(
			result == 165,
			"Proper multiplication because it's built into the language itself",
			"Somehow the incorrect value came out of what we just did"
		);
	});

	TEST("INT DIVISION",
	{
		int a = 300;
		int b = 150;
		int result = a / b;
		EXPECTING(
			result == 2,
			"Proper division because it's built into the language itself",
			"Somehow the incorrect value came out of what we just did"
		);
	});

}

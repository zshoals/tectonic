#include <assert.h>
#include <stdbool.h>

#include "test_basics.h"
#include "trial_by_fire.h"


void test_all_integer_basics(void)
{
	TEST("Int Addition", test_integer_addition);
	TEST("Int Subtraction", test_integer_subtraction);
	TEST("Int Division", test_integer_division);
	TEST("Int Multiplication", test_integer_multiplication);
}

bool test_integer_addition(void)
{
	int a = 99;
	int b = 1;
	int result = a + b;
	assert(result == 100);

	return true;
}

bool test_integer_subtraction(void)
{
	int a = 580;
	int b = 80;
	int result = a - b;
	assert(result == 500);

	return true;
}

bool test_integer_division(void)
{
	int a = 1000;
	int b = 500;
	int result = a / b;
	assert(result == 2);

	return true;
}

bool test_integer_multiplication(void)
{
	int a = 10;
	int b = 6;
	int result = a * b;
	assert(result == 60);

	return true;
}


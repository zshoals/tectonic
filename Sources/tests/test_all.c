#include "test_all.h"

//=========INCLUDE YOUR TESTS HERE============

#include "test_basics.h"
#include "test_bits.h"

//============================================

void tbf_run_all_tests(void)
{
	test_all_integer_basic_operations();
	test_all_bit_operations();
}
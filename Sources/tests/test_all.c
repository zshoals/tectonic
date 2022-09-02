#include "test_all.h"

//=========INCLUDE YOUR TESTS HERE============

#include "test_basics.h"
#include "test_bits.h"
#include "test_memory.h"
#include "test_generic_array.h"

//============================================
#include "kinc/log.h"

void tbf_run_all_tests(void)
{
	kinc_log(KINC_LOG_LEVEL_INFO, "[ Running Tests... ]");

	test_all_integer_basic_operations();
	test_all_bit_operations();
	test_all_memory_operations();
	test_all_generic_array_functions();

	kinc_log(KINC_LOG_LEVEL_INFO, "[ Testing completed successfully. ]");
}
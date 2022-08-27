#include "test_bits.h"
#include "trial_by_fire.h"

#include "tectonic/util/bits.h"

void test_all_bit_operations(void)
{

	TEST("Simple Bit Extraction",
	{
		bitflags32_t flags = tec_bits_create();
		//Set bits at the 4th and 8th positions
		flags |= TEC_BIT(4);
		flags |= TEC_BIT(8);
		bitflags32_t four_mask = tec_bits_create();
		four_mask |= TEC_BIT(4);
		bitflags32_t eight_mask = tec_bits_create();
		eight_mask |= TEC_BIT(8);

		EXPECTING(
			tec_bits_extract(flags, four_mask) == TEC_BIT(4),
			"Should have received the fourth bit in the value",
			"Didn't receive the fourth bit"
		);

 		EXPECTING(
			tec_bits_extract(flags, eight_mask) == TEC_BIT(8),
			"Should have received the eighth bit in the value",
			""
		);

	});

	TEST("Simple Bit Set",
	{
		bitflags32_t flags = tec_bits_create();
		flags = tec_bits_set(flags, TEC_BIT(12));
		bitflags32_t default_setting_test = tec_bits_create();
		default_setting_test |= TEC_BIT(12);

		EXPECTING(
			flags == default_setting_test,
			"Bit setting by function should have matched an \"Or Equal\" operation if it was working correctly",
			""
		);
	});

	TEST("Simple Bit Unset",
	{
		bitflags32_t flags = tec_bits_create();
		flags = tec_bits_set(flags, TEC_BIT(24));
		flags = tec_bits_unset(flags, TEC_BIT(24));

		EXPECTING(
			flags == tec_bits_create(),
			"Expected that unsetting the flags set bit would result in a default flag configuration",
			""
		);
	});

	TEST("Simple Bit Shift",
	{
		bitflags32_t flags = tec_bits_create();
		flags = tec_bits_set(flags, 32);

		EXPECTING(
			flags == TEC_BIT(5),
			"Expected the TEC_BIT macro to result in the appropriate value of 32 for a 5 bitshift",
			""
		);
	});

	TEST("Simple Match of All Bit Flags",
	{
		bitflags32_t flags = tec_bits_create();
		flags = tec_bits_set(flags, TEC_BIT(8));
		flags = tec_bits_set(flags, TEC_BIT(22));
		flags = tec_bits_set(flags, TEC_BIT(31));

		bitflags32_t matcher = tec_bits_create();
		matcher |= 256;
		matcher |= 4194304;
		matcher |= 2147483648;

		EXPECTING(
			tec_bits_has_all_flags(flags, matcher),
			"Flags and matcher should have had equivalent flags set",
			""
		);
	});

	TEST("Simple Match of Any Bit Flag When Flags Contain Multiple Flags",
	{
		bitflags32_t flags = tec_bits_create();
		flags = tec_bits_set(flags, TEC_BIT(8));
		flags = tec_bits_set(flags, TEC_BIT(22));
		flags = tec_bits_set(flags, TEC_BIT(31));

		bitflags32_t matcher = tec_bits_create();
		matcher = tec_bits_set(matcher, TEC_BIT(8));

		EXPECTING(
			tec_bits_has_any_flag(flags, matcher),
			"Was expecting at least one match between flags and matcher",
			""
		);
	});

	TEST("Simple NO match for all flags",
	{
		bitflags32_t flags = tec_bits_create();
		flags = tec_bits_set(flags, TEC_BIT(8));
		flags = tec_bits_set(flags, TEC_BIT(22));
		flags = tec_bits_set(flags, TEC_BIT(31));

		bitflags32_t matcher = tec_bits_create();
		matcher = tec_bits_set(matcher, TEC_BIT(8));

		EXPECTING(
			!(tec_bits_has_all_flags(flags, matcher)),
			"Was expecting that flags and matcher did not match due to missing bits in matcher",
			""
		);
	});

}
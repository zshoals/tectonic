#pragma once

#ifndef NDEBUG
	#include <assert.h>
#else //Assert was disabled, but we want our assertion kit to always be enabled
	#undef NDEBUG
	#include <assert.h>
	#define NDEBUG
#endif

#ifndef TEC_DISABLE_UNFORCED_ASSERTS
	#define V_PTR_NOT_NULL(Pointer, Message) assert((Message), (Pointer))
	#define V_IS_TRUE(Expression, Message) assert((Message), (Expression))
	#define V_IS_FALSE(Expression, Message) assert((Message), !(Expression))
	#define V_INT_EQUALS(Int1, Int2, Message) assert((Message), (Int1) == (Int2))
	#define V_NUMBER_IN_RANGE(Value, Lower, Upper, Message) assert( (Message), ((Lower) <= (Value) && (Value) <= (Upper)) )
	#define V_KILL_NOW(Message) assert( (Message), 0);
#else
	#define V_PTR_NOT_NULL(Pointer, Message) ((void)0)
	#define V_IS_TRUE(Expression, Message) ((void)0)
	#define V_IS_FALSE(Expression, Message) ((void)0)
	#define V_INT_EQUALS(Int1, Int2, Message) ((void)0)
	#define V_NUMBER_IN_RANGE(Value, Lower, Upper, Message) ((void)0)
	#define V_KILL_NOW(Message) ((void)0)
#endif


//These assertions are never disabled, even in release builds
#define V_ALWAYS_CHECK_PTR_NOT_NULL(Pointer, Message) assert((Message), (Pointer))
#define V_ALWAYS_CHECK_IS_TRUE(Expression, Message) assert((Message), (Expression))
#define V_ALWAYS_CHECK_IS_FALSE(Expression, Message) assert((Message), !(Expression))
#define V_ALWAYS_CHECK_INT_EQUALS(Int1, Int2, Message) assert((Message), (Int1) == (Int2))
#define V_ALWAYS_CHECK_NUMBER_IN_RANGE(Value, Lower, Upper, Message) assert( (Message), ((Lower) <= (Value) && (Value) <= (Upper)) )
#define V_ALWAYS_KILL_NOW(Message) assert( (Message), 0);

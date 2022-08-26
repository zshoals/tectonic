#pragma once

#ifndef NDEBUG
	#include <assert.h>
#else //Assert was disabled, but we want our assertion kit to always be enabled
	#undef NDEBUG
	#include <assert.h>
	#define NDEBUG
#endif

//NOTE: asserts with messages need to be wrapped with double parenthesis like this:
// assert (( MSG, EXPR ))
//in order to work properly. It makes sense, assert only takes a single parameter
#ifndef TEC_DISABLE_UNFORCED_ASSERTS
	#define DEBUG_ENSURE_PTR_NOT_NULL(Pointer, Message) assert(( (Message), (Pointer) ))
	#define DEBUG_ENSURE_TRUE(Expression, Message) assert(( (Message), (Expression) ))
	#define DEBUG_ENSURE_FALSE(Expression, Message) assert(( (Message), !(Expression) ))
	#define DEBUG_ENSURE_INT_EQUALS(Int1, Int2, Message) assert(( (Message), (Int1) == (Int2) ))
	#define DEBUG_ENSURE_NUMBER_IN_RANGE(Value, Lower, Upper, Message) \
		assert(( (Message), ((Lower) <= (Value) && (Value) <= (Upper)) ))
	#define DEBUG_ENSURE_KILL_NOW(Message) assert(( (Message), 0 ))
#else
	#define DEBUG_ENSURE_PTR_NOT_NULL(Pointer, Message) ((void)0)
	#define DEBUG_ENSURE_TRUE(Expression, Message) ((void)0)
	#define DEBUG_ENSURE_FALSE(Expression, Message) ((void)0)
	#define DEBUG_ENSURE_INT_EQUALS(Int1, Int2, Message) ((void)0)
	#define DEBUG_ENSURE_NUMBER_IN_RANGE(Value, Lower, Upper, Message) ((void)0)
	#define DEBUG_ENSURE_KILL_NOW(Message) ((void)0)
#endif


//These assertions are never disabled, even in release builds
#define ENSURE_PTR_NOT_NULL(Pointer, Message) assert(( (Message), (Pointer) ))
#define ENSURE_TRUE(Expression, Message) assert(( (Message), (Expression) ))
#define ENSURE_FALSE(Expression, Message) assert(( (Message), !(Expression) ))
#define ENSURE_INT_EQUALS(Int1, Int2, Message) assert(( (Message), (Int1) == (Int2) ))
#define ENSURE_NUMBER_IN_RANGE(Value, Lower, Upper, Message) \
	assert(( (Message), ((Lower) <= (Value) && (Value) <= (Upper)) ))
//For when you absolutely need to kill the program right now
#define ENSURE_KILL_NOW(Message) assert(( (Message), 0 ))
//Intended for things like switch cases with unreachable and unwanted default outcomes, for instance
#define ENSURE_UNREACHABLE(Message) assert(( (Message), 0 ))
//Intended for unimplemented functions and features, maybe we should add function name support
#define ENSURE_UNIMPLEMENTED() assert(( "Function is unimplemented.", 0 ))


#include "log.h"
#include "kinc/log.h"
#include <stdarg.h>
#include "../util/framestring.h"
#include "../frequent.h"

local_func void
tec_log_info_modify(char const * format, va_list args)
{
	tec_framestring_t new_format = tec_framestring_create("[TEC--INFO]::[" TEC_LOG_MODULE_NAME "] ");
	tec_framestring_t original = tec_framestring_create(format);
	tec_framestring_t final = tec_framestring_append(new_format, original);
	kinc_log_args(KINC_LOG_LEVEL_INFO, final.string, args);
}

local_func void
tec_log_warn_modify(char const * format, va_list args)
{
	tec_framestring_t new_format = tec_framestring_create("[TEC--WARN]::[" TEC_LOG_MODULE_NAME "] ");
	tec_framestring_t original = tec_framestring_create(format);
	tec_framestring_t final = tec_framestring_append(new_format, original);
	kinc_log_args(KINC_LOG_LEVEL_WARNING, final.string, args);
}

local_func void
tec_log_error_modify(char const * format, va_list args)
{
	tec_framestring_t new_format = tec_framestring_create("[TEC--ERROR]::[" TEC_LOG_MODULE_NAME "] ");
	tec_framestring_t original = tec_framestring_create(format);
	tec_framestring_t final = tec_framestring_append(new_format, original);
	kinc_log_args(KINC_LOG_LEVEL_ERROR, final.string, args);
}

void
tec_log_info(char const * format, ...)
{
	va_list args;
	va_start(args, format);
	tec_log_info_modify(format, args);
	va_end(args);
}

void 
tec_log_warn(char const * format, ...)
{
	va_list args;
	va_start(args, format);
	tec_log_warn_modify(format, args);
	va_end(args);
}

void 
tec_log_error(char const * format, ...)
{
	va_list args;
	va_start(args, format);
	tec_log_error_modify(format, args);
	va_end(args);
}
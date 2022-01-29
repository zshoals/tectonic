#include "log.h"
#include "kinc/log.h"
#include <stdarg.h>
#include "../util/framestring.h"
#include "../frequent.h"

//#define TEC_LOG_INFO_PREFIX "[TEC-INFO]::[" TEC_LOG_MODULE_NAME "] "
//#define TEC_LOG_INFO_VERBOSE_PREFIX "[TEC-INFO]::[" TEC_LOG_MODULE_NAME "]::[File-" __FILE__ "]::[Line-" TEC_EXPANDER(__LINE__) "] "
//
//#define TEC_LOG_WARN_PREFIX "[TEC-WARN]::[" TEC_LOG_MODULE_NAME "] "
//#define TEC_LOG_WARN_VERBOSE_PREFIX "[TEC-WARN]::[" TEC_LOG_MODULE_NAME "]::[File-" __FILE__ "]::[Line-" TEC_EXPANDER(__LINE__) "] "
//
//#define TEC_LOG_ERROR_PREFIX "[TEC-ERROR]::[" TEC_LOG_MODULE_NAME "] "
//#define TEC_LOG_ERROR_VERBOSE_PREFIX "[TEC-ERROR]::[" TEC_LOG_MODULE_NAME "]::[File-" __FILE__ "]::[Line-" TEC_EXPANDER(__LINE__) "] "

local_func void
tec_log_modify(char const * format, char const * prefix_string, kinc_log_level_t level, va_list args)
{
	tec_framestring_t new_format = tec_framestring_create(prefix_string);
	tec_framestring_t original = tec_framestring_create(format);
	tec_framestring_t final = tec_framestring_append(new_format, original);
	kinc_log_args(level, final.string, args);
}

#ifndef TEC_LOG_ALWAYS_VERBOSE
void
tec_log_internal_info(char const * format, char const * prefix, ...)
{
	va_list args;
	va_start(args, format);
	tec_log_modify(format, prefix, KINC_LOG_LEVEL_INFO, args);
	va_end(args);
}

void 
tec_log_internal_warn(char const * format, char const * prefix, ...)
{
	va_list args;
	va_start(args, format);
	tec_log_modify(format, prefix, KINC_LOG_LEVEL_WARNING, args);
	va_end(args);
}

void 
tec_log_internal_error(char const * format, char const * prefix, ...)
{
	va_list args;
	va_start(args, format);
	tec_log_modify(format, prefix, KINC_LOG_LEVEL_ERROR, args);
	va_end(args);
}
#else
tec_log_internal_info(char const * format, char const * prefix, ...)
{
	va_list args;
	va_start(args, format);
	tec_log_modify(format, prefix, KINC_LOG_LEVEL_INFO, args);
	va_end(args);
}

void 
tec_log_internal_warn(char const * format, char const * prefix, ...)
{
	va_list args;
	va_start(args, format);
	tec_log_modify(format, prefix, KINC_LOG_LEVEL_WARNING, args);
	va_end(args);
}

void 
tec_log_internal_error(char const * format, char const * prefix, ...)
{
	va_list args;
	va_start(args, format);
	tec_log_modify(format, prefix, KINC_LOG_LEVEL_ERROR, args);
	va_end(args);
}
#endif

void
tec_log_internal_info_verbose(char const * format, char const * prefix, ...)
{
	va_list args;
	va_start(args, format);
	tec_log_modify(format, prefix, KINC_LOG_LEVEL_INFO, args);
	va_end(args);
}

void 
tec_log_internal_warn_verbose(char const * format, char const * prefix, ...)
{
	va_list args;
	va_start(args, format);
	tec_log_modify(format, prefix, KINC_LOG_LEVEL_WARNING, args);
	va_end(args);
}

void 
tec_log_internal_error_verbose(char const * format, char const * prefix, ...)
{
	va_list args;
	va_start(args, format);
	tec_log_modify(format, prefix, KINC_LOG_LEVEL_ERROR, args);
	va_end(args);
}
#include "log.h"
#include "kinc/log.h"
#include <stdarg.h>
#include "../util/string.h"
#include "../frequent.h"
#include <stddef.h>
#include <assert.h>

//#define TEC_LOG_INFO_PREFIX "[TEC-INFO]::[" TEC_LOG_MODULE_NAME "] "
//#define TEC_LOG_INFO_VERBOSE_PREFIX "[TEC-INFO]::[" TEC_LOG_MODULE_NAME "]::[File-" __FILE__ "]::[Line-" TEC_EXPANDER(__LINE__) "] "
//
//#define TEC_LOG_WARN_PREFIX "[TEC-WARN]::[" TEC_LOG_MODULE_NAME "] "
//#define TEC_LOG_WARN_VERBOSE_PREFIX "[TEC-WARN]::[" TEC_LOG_MODULE_NAME "]::[File-" __FILE__ "]::[Line-" TEC_EXPANDER(__LINE__) "] "
//
//#define TEC_LOG_ERROR_PREFIX "[TEC-ERROR]::[" TEC_LOG_MODULE_NAME "] "
//#define TEC_LOG_ERROR_VERBOSE_PREFIX "[TEC-ERROR]::[" TEC_LOG_MODULE_NAME "]::[File-" __FILE__ "]::[Line-" TEC_EXPANDER(__LINE__) "] "

//Here resides a painful lesson about va_args:
//the second parameter to va_start is the ADDRESS of the LAST PARAMETER IN THE FUNCTION
//Proof that reading is indeed the most powerful ability

void
tec_log_modify(char const * prefix_string, char const * format, kinc_log_level_t level, va_list args)
{
	char buffer[4096];
	tec_string_t pre = tec_string_create(prefix_string);
	tec_string_t post = tec_string_create(format);
	tec_string_t combo = tec_string_append(buffer, pre, post);
	kinc_log_args(level, combo.string, args);
}

#ifndef TEC_LOG_ALWAYS_VERBOSE
void
tec_log_internal_info(char const * prefix, char const * format, ...)
{
	va_list args;
	va_start(args, format);
	tec_log_modify(prefix, format, KINC_LOG_LEVEL_INFO, args);
	va_end(args);
}

void 
tec_log_internal_warn(char const * prefix, char const * format, ...)
{
	va_list args;
	va_start(args, format);
	tec_log_modify(prefix, format, KINC_LOG_LEVEL_WARNING, args);
	va_end(args);
}

void 
tec_log_internal_error(char const * prefix, char const * format, ...)
{
	va_list args;
	va_start(args, format);
	tec_log_modify(prefix, format, KINC_LOG_LEVEL_ERROR, args);
	va_end(args);
}
#else
tec_log_internal_info(char const * prefix, char const * format, ...)
{
	va_list args;
	va_start(args, format);
	tec_log_modify(prefix, format, KINC_LOG_LEVEL_INFO, args);
	va_end(args);
}

void 
tec_log_internal_warn(char const * prefix, char const * format, ...)
{
	va_list args;
	va_start(args, format);
	tec_log_modify(prefix, format, KINC_LOG_LEVEL_WARNING, args);
	va_end(args);
}

void 
tec_log_internal_error(char const * prefix, char const * format, ...)
{
	va_list args;
	va_start(args, format);
	tec_log_modify(prefix, format, KINC_LOG_LEVEL_ERROR, args);
	va_end(args);
}
#endif

void
tec_log_internal_info_verbose(char const * prefix, char const * format, ...)
{
	va_list args;
	va_start(args, format);
	tec_log_modify(prefix, format, KINC_LOG_LEVEL_INFO, args);
	va_end(args);
}

void 
tec_log_internal_warn_verbose(char const * prefix, char const * format, ...)
{
	va_list args;
	va_start(args, format);
	tec_log_modify(prefix, format, KINC_LOG_LEVEL_WARNING, args);
	va_end(args);
}

void 
tec_log_internal_error_verbose(char const * prefix, char const * format, ...)
{
	va_list args;
	va_start(args, format);
	tec_log_modify(prefix, format, KINC_LOG_LEVEL_ERROR, args);
	va_end(args);
}
#pragma once

#include "../frequent.h"
#include "kinc/log.h"

#define TEC_LOG_MODULE_NAME "Undefined Module, please define me with TEC_LOG_MODULE_NAME."

#ifndef TEC_LOGGING_DISABLED
	#define tec_log_info(format, ...) kinc_log(KINC_LOG_LEVEL_INFO, "[TEC--INFO]::[" TEC_LOG_MODULE_NAME "] " format, __VA_ARGS__)
	#define tec_log_warn(format, ...) kinc_log(KINC_LOG_LEVEL_WARNING,"[TEC--WARN]::[" TEC_LOG_MODULE_NAME "] " format, __VA_ARGS__)
	#define tec_log_error(format, ...) kinc_log(KINC_LOG_LEVEL_ERROR,"[TEC--ERROR]::[" TEC_LOG_MODULE_NAME "] " format, __VA_ARGS__)

	#define tec_log_info_verbose(format, ...) kinc_log(KINC_LOG_LEVEL_INFO, "[TEC--INFO]::[" TEC_LOG_MODULE_NAME "]::[File--" __FILE__ "]::[Line--" TEC_EXPANDER(__LINE__) "] " format, __VA_ARGS__)
	#define tec_log_warn_verbose(format, ...) kinc_log(KINC_LOG_LEVEL_WARNING, "[TEC--WARN]::[" TEC_LOG_MODULE_NAME "]::[File--" __FILE__ "]::[Line--" TEC_EXPANDER(__LINE__) "] " format, __VA_ARGS__)
	#define tec_log_error_verbose(format, ...) kinc_log(KINC_LOG_LEVEL_ERROR, "[TEC--ERROR]::[" TEC_LOG_MODULE_NAME "]::[File--" __FILE__ "]::[Line--" TEC_EXPANDER(__LINE__) "] " format, __VA_ARGS__)
#else
	#define tec_log_info(format, ...)
	#define tec_log_warn(format, ...)
	#define tec_log_error(format, ...)

	#define tec_log_info_verbose(format, ...)
	#define tec_log_warn_verbose(format, ...)
	#define tec_log_error_verbose(format, ...)
#endif
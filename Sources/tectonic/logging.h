
#pragma once

#include <stdarg.h>
#include "kinc/log.h"
#include "tcommon.h"

#define TEC_LOG_MAX_BUFFER_LEN 1024
#define TEC_LOG_MAX_SUBBUFFER_LEN 256

#define LOG_ALL ~((tec_logging_flags)(0))
#define LOG_NO_EXCLUSIONS ((tec_logging_flags)(0))
typedef enum
{
	LOG_INFO = (1 << 0),
	LOG_WARNING = (1 << 1),
	LOG_ERROR = (1 << 2),
	LOG_VERBOSE = (1 << 3),

	LOG_ENGINE = (1 << 4),
	LOG_GAME = (1 << 5),
	LOG_ECS = (1 << 6),
	LOG_PHYSICS = (1 << 7),
	LOG_GRAPHICS = (1 << 8),
	LOG_INPUT = (1 << 9),
	LOG_PERFORMANCE = (1 << 10),
}      
tec_logging_filter_e;

typedef u64 tec_logging_flags;

//Pass a list of flags to allow. Log message with even a single flag present will print,
//exclusions will completely suppress a message with a selected tag
void tec_log_set_filtering(tec_logging_flags flags, tec_logging_flags exclusions, bool force_verbose);

void tec_internal_log_verbose(kinc_log_level_t level, tec_logging_flags flags, char const * format, char const * file, size_t line, va_list args);
void tec_internal_log(kinc_log_level_t level, tec_logging_flags flags, char const * format, char const * file, size_t line, va_list args);
void tec_log_filtered(tec_logging_flags flags, char const * format, ...);

#define TEC_LOG(FILTER, FORMAT, ...) tec_log_filtered(FILTER, FORMAT, __VA_ARGS__)
#define log_warn_verbose(FORMAT, FLAGS, ARGS) tec_internal_log_verbose(KINC_LOG_LEVEL_WARNING, FLAGS, FORMAT, __FILE__, __LINE__, ARGS)
#define log_info_verbose(FORMAT, FLAGS, ARGS) tec_internal_log_verbose(KINC_LOG_LEVEL_INFO, FLAGS, FORMAT, __FILE__, __LINE__, ARGS)
#define log_error_verbose(FORMAT, FLAGS, ARGS) tec_internal_log_verbose(KINC_LOG_LEVEL_ERROR, FLAGS, FORMAT, __FILE__, __LINE__, ARGS)

#define log_warn(FORMAT, FLAGS, ARGS) tec_internal_log(KINC_LOG_LEVEL_WARNING, FLAGS, FORMAT, __FILE__, __LINE__, ARGS)
#define log_info(FORMAT, FLAGS, ARGS) tec_internal_log(KINC_LOG_LEVEL_INFO, FLAGS, FORMAT, __FILE__, __LINE__, ARGS)
#define log_error(FORMAT, FLAGS, ARGS) tec_internal_log(KINC_LOG_LEVEL_ERROR, FLAGS, FORMAT, __FILE__, __LINE__, ARGS)

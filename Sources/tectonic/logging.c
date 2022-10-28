#include "logging.h"

#include <stdio.h>
#include "kinc/log.h"
#include "kinc/system.h"
#include "tectonic/validation.h"

//Allow all logs by default
static tec_logging_flags active_filter = ~0;
//Exclude nothing by default
static tec_logging_flags active_exclusions = 0;

void tec_internal_log_verbose(kinc_log_level_t level, char const * format, char const * file, size_t line, va_list args)
{
	char buffer[TEC_LOG_MAX_BUFFER_LEN];
	switch (level)
	{
		case KINC_LOG_LEVEL_INFO:
		{
			snprintf(buffer, TEC_LOG_MAX_BUFFER_LEN, "[Info: %0.5f]::[%s]::[File: %s]::[Line: %zu]", kinc_time(), format, file, line);
			break;
		}
		case KINC_LOG_LEVEL_WARNING:
		{
			snprintf(buffer, TEC_LOG_MAX_BUFFER_LEN, "[WARNING: %0.5f]::[%s]::[File: %s]::[Line: %zu]", kinc_time(), format, file, line);
			break;
		}
		case KINC_LOG_LEVEL_ERROR:
		{
			snprintf(buffer, TEC_LOG_MAX_BUFFER_LEN, "[ERROR: %0.5f]::[%s]::[File: %s]::[Line: %zu]", kinc_time(), format, file, line);
			break;
		}
		default:
			ENSURE_UNREACHABLE("Incorrect logging level set. Did you forget to select an appropriate Info, Warning, or Error filter for this log message?");
	}

	char const * string = &buffer[0];
	kinc_log_args(level, string, args);
}

void tec_internal_log(kinc_log_level_t level, char const * format, char const * file, size_t line, va_list args)
{
	char buffer[TEC_LOG_MAX_BUFFER_LEN];
	switch (level)
	{
		case KINC_LOG_LEVEL_INFO:
		{
			snprintf(buffer, TEC_LOG_MAX_BUFFER_LEN, "[Info: %0.5f]::[%s]", kinc_time(), format);
			break;
		}
		case KINC_LOG_LEVEL_WARNING:
		{
			snprintf(buffer, TEC_LOG_MAX_BUFFER_LEN, "[WARNING: %0.5f]::[%s]", kinc_time(), format);
			break;
		}
		case KINC_LOG_LEVEL_ERROR:
		{
			snprintf(buffer, TEC_LOG_MAX_BUFFER_LEN, "[ERROR: %0.5f]::[%s]", kinc_time(), format);
			break;
		}
		default:
			ENSURE_UNREACHABLE("Incorrect logging level set. Did you forget to select an appropriate Info, Warning, or Error filter for this log message?");
	}

	char const * string = &buffer[0];
	kinc_log_args(level, string, args);

}

void tec_log_set_filtering(tec_logging_flags flags, tec_logging_flags exclusions)
{
	active_filter = flags; 
	active_exclusions = exclusions;
}

void tec_log_filtered(tec_logging_flags flags, char const * format, ...)
{
	va_list args;
	va_start(args, format);

	tec_logging_flags filtered_flags;
	//If flags contains any flag that's currently excluded, this log message
	//will not be output
	if (flags & active_exclusions)
	{
		filtered_flags = 0;
	} 
	else
	{
		filtered_flags = flags;
	}

	if (filtered_flags & active_filter)
	{
		if (flags & LOG_VERBOSE)
		{
			if (flags & LOG_INFO)
			{
				log_info_verbose(format, args);
			}
			if (flags & LOG_WARNING)
			{
				log_warn_verbose(format, args);
			}
			if (flags & LOG_ERROR)
			{
				log_error_verbose(format, args);
			}
		}
		else
		{
			if (flags & LOG_INFO)
			{
				log_info(format, args);
			}
			if (flags & LOG_WARNING)
			{
				log_warn(format, args);
			}
			if (flags & LOG_ERROR)
			{
				log_error(format, args);
			}
		}
	}

	va_end(args);
}

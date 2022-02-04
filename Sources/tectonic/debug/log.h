#pragma once

#define TEC_LOG_MODULE_NAME "Undefined Module, please define me with TEC_LOG_MODULE_NAME"

#ifdef TEC_LOG_LOGGING_ENABLED

#define tec_log_info(format, ...) tec_log_internal_info("[TEC-INFO]::[" TEC_LOG_MODULE_NAME "] ", format, __VA_ARGS__)
#define tec_log_warn(format, ...) tec_log_internal_warn("[TEC-!!WARN!!]::[" TEC_LOG_MODULE_NAME "] ", format, __VA_ARGS__)
#define tec_log_error(format, ...) tec_log_internal_error("[TEC-!!!!!ERROR!!!!!]::[" TEC_LOG_MODULE_NAME "] ", format, __VA_ARGS__)

#define tec_log_info_verbose(format, ...) tec_log_internal_info_verbose("[TEC-INFO]::[" TEC_LOG_MODULE_NAME "]::[File-" __FILE__ "]::[Line-" TEC_EXPANDER(__LINE__) "] ", format, __VA_ARGS__)
#define tec_log_warn_verbose(format, ...) tec_log_internal_warn_verbose("[TEC-WARN]::[" TEC_LOG_MODULE_NAME "]::[File-" __FILE__ "]::[Line-" TEC_EXPANDER(__LINE__) "] ", format, __VA_ARGS__)
#define tec_log_error_verbose(format, ...) tec_log_internal_error_verbose("[TEC-ERROR]::[" TEC_LOG_MODULE_NAME "]::[File-" __FILE__ "]::[Line-" TEC_EXPANDER(__LINE__) "] ", format,  __VA_ARGS__)

#else

#define tec_log_info(format, ...)
#define tec_log_warn(format, ...)
#define tec_log_error(format, ...)

#define tec_log_info_verbose(format, ...)
#define tec_log_warn_verbose(format, ...)
#define tec_log_error_verbose(format, ...)

#endif
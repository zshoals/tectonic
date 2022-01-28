#pragma once

#define TEC_LOG_MODULE_NAME "Undefined Module, please define me with TEC_LOG_MODULE_NAME"

void tec_log_info(char const * format, ...);
void tec_log_warn(char const * format, ...);
void tec_log_error(char const * format, ...);

void tec_log_info_verbose(char const * format, ...);
void tec_log_warn_verbose(char const * format, ...);
void tec_log_error_verbose(char const * format, ...);

//Add verbose output
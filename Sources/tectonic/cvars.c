#include "cvars.h"

#include "frequent.h"
#include <assert.h>
#include "debug/log.h"
#include <string.h>
#include <kinc/system.h>

#define TEC_LOG_MODULE_NAME "CVars"

local_data tec_cvar_t cvars[64] = {0};

local_func void
set_string(tec_cvar_t * cvar, tec_cvar_value_t value)
{
	if (strlen(value.string_value) < TEC_CVARS_MAX_STRING_VALUE_LENGTH)
	{
		strcpy(cvar->value.string_value, value.string_value);
		tec_log_info("[CVar: String-value] %s set to %s", cvar->name, cvar->value.string_value);
	}
	else
	{
		tec_log_error("[CVar: String-value] %s was not set because the supplied string value was too long.", cvar->name);
	}
}

local_func void
set_int(tec_cvar_t * cvar, tec_cvar_value_t value)
{
	cvar->value.int_value = value.int_value;
	tec_log_info("[CVar: Int-value] %s set to %d", cvar->name, cvar->value.int_value);
}

local_func void
set_bool(tec_cvar_t * cvar, tec_cvar_value_t value)
{
	cvar->value.bool_value = value.bool_value;
	tec_log_info("[CVar: Bool-value] %s set to %d", cvar->name, cvar->value.bool_value);
}

void 
tec_cvars_set_cvar
(
	tec_cvars_identifier_e cvar, 
	tec_cvars_value_type_e value_type, 
	tec_cvar_value_t value
)
{
	tec_cvar_t * setting = &cvars[cvar];
	if (setting->value.value_type == value_type)
	{
		//Technically, this function could just do a strict copy of "value", but we can
		//dispatch log messages a little easier by doing it this way.
		switch (value_type)
		{
			case CVAR_VALUE_STRING:
				set_string(setting, value);
				break;
			case CVAR_VALUE_INT:
				set_int(setting, value);
				break;
			case CVAR_VALUE_BOOL:
				set_bool(setting, value);
				break;
			default:
				assert("We can never reach here");
		}
	}
	else
	{
		tec_log_error("Improper value_type supplied for setting CVar %s; CVar not set.", setting->name);
	}
}

tec_cvar_value_t 
tec_cvars_get_cvar(tec_cvars_identifier_e cvar)
{
	return cvars[cvar].value;
}

//Internal cvar configuration
local_func void
set_name(tec_cvars_identifier_e cvar, char const * name)
{
	strcpy(cvars[cvar].name, name);
}

local_func void
set_value_type(tec_cvars_identifier_e cvar, tec_cvars_value_type_e type)
{
	cvars[cvar].value.value_type = type;
}

local_func void
set_cvar_fast(tec_cvars_identifier_e cvar, char const * name, tec_cvar_value_t value)
{
	set_name(cvar, name);
	set_value_type(cvar, value.value_type);
	
	switch (value.value_type)
	{
		case CVAR_VALUE_STRING:
			set_string(&cvars[cvar], value);
			break;
		case CVAR_VALUE_INT:
			set_int(&cvars[cvar], value);
			break;
		case CVAR_VALUE_BOOL:
			set_bool(&cvars[cvar], value);
			break;
	}
}

local_func tec_cvar_value_t
make_value_string(char const * string)
{
	tec_cvar_value_t value;
	value.value_type = CVAR_VALUE_STRING;
	strcpy(value.string_value, string);

	return value;
}

local_func tec_cvar_value_t
make_value_int(int num)
{
	tec_cvar_value_t value;
	value.value_type = CVAR_VALUE_INT;
	value.int_value = num;

	return value;
}

local_func tec_cvar_value_t
make_value_bool(bool flag)
{
	tec_cvar_value_t value;
	value.value_type = CVAR_VALUE_BOOL;
	value.bool_value = flag;

	return value;
}
/*
	Window Cvars
*/
local_func void
set_window_defaults(void)
{
	set_cvar_fast(W_TITLE, "w_title", make_value_string("Tectonic Project"));
	set_cvar_fast(W_WIDTH, "w_width", make_value_int(800));
	set_cvar_fast(W_HEIGHT, "w_height", make_value_int(600));
	set_cvar_fast(W_VERTICAL_SYNCED, "w_vertical_synced", make_value_bool(true));
}

/*
	Full Default Initialization for all Cvar types
*/
void 
tec_internal_cvars_set_all_default(void)
{
	tec_log_info("Initializing all CVars to default values");
	set_window_defaults();
}
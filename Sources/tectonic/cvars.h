#pragma once

#include <stdbool.h>
#include "cvars_manifest.h"

#define TEC_CVARS_MAX_NAME_LENGTH 128
#define TEC_CVARS_MAX_STRING_VALUE_LENGTH 256

typedef enum
{
	CVAR_VALUE_BOOL,
	CVAR_VALUE_INT,
	CVAR_VALUE_STRING,
}
tec_cvars_value_type_e;

typedef struct
tec_cvar_value
{
	tec_cvars_value_type_e value_type;
	union
	{
		char string_value[TEC_CVARS_MAX_STRING_VALUE_LENGTH];
		int int_value;
		bool bool_value;
	};
}
tec_cvar_value_t;

typedef struct
tec_cvar
{
	char name[TEC_CVARS_MAX_NAME_LENGTH];
	tec_cvar_value_t value;
}
tec_cvar_t;

void tec_cvars_set_cvar(tec_cvars_identifier_e cvar, tec_cvar_value_t value);
tec_cvar_value_t tec_cvars_get_cvar(tec_cvars_identifier_e cvar);

void tec_internal_cvars_set_all_default(void);
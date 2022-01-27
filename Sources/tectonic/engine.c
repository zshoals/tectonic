#include "engine.h"
#include "util/timediff.h"
#include "util/time.h"

#include "kinc/system.h"
#include "kinc/log.h"

#include <string.h>

#include "lib/stc/ccommon.h"
#include "kinc/io/filewriter.h"
#include "kinc/io/filereader.h"

#include "io/json.h"
#include "util/framestring.h"

static tec_engine_context_t engine_context;

typedef struct 
tec_test_data
{
	int one;
	char string[500];
	double buff;
	double yep;
}
tec_test_data_t;

static tec_engine_loop_configuration_t engine_loop_config;
static double accumulator = 0.0;

//All of this should be in a performance struct?
static tec_timediff_t single_update_timediff;
static tec_timediff_t render_timediff;
static tec_timediff_t cycle_timediff;

static double time_single_update = 0.0;
static double time_render = 0.0;
static double time_cycle = 0.0;

void
tec_engine_main_loop(void)
{
	if (time_cycle > engine_loop_config.max_frametime_s)
	{
		time_cycle = engine_loop_config.max_frametime_s;
	}

	accumulator += time_cycle;

	tec_timediff_begin(&cycle_timediff);
	{
		//Full logic cycle
		while (accumulator >= engine_loop_config.logic_timestep_s) 
		{
			//Single logic update
			tec_timediff_begin(&single_update_timediff);

			engine_loop_config.update_callback(&engine_context, engine_loop_config.logic_timestep_s);
			accumulator -= engine_loop_config.logic_timestep_s;

			time_single_update = tec_timediff_end(&single_update_timediff);
		}

		//Full render cycle
		{
			tec_timediff_begin(&render_timediff);

			engine_loop_config.render_callback(&engine_context, accumulator /* should this subtract from something*/);

			time_render = tec_timediff_end(&render_timediff);
		}
	}
	time_cycle = tec_timediff_end(&cycle_timediff);

	tec_json_config_state_t config;
	tec_json_config_option_int_t options_int[64];
	int opt_int_count = 0;
	tec_json_config_option_bool_t options_bool[64];
	int opt_bool_count = 0;

	// if (tec_json_config_load_file(&config, "settings.json"))
	// {
	// 	for (int i = 0; i < config.options_count; i++) 
	// 	{
	// 		tec_json_element_type_t type = tec_json_config_read_element_type(&config);
	// 		switch (type)
	// 		{
	// 			case TEC_JSON_INT:
	// 				if (strcmp("OMEGASETTING", config.current_location->name->string) == 0) 
	// 				{
	// 					strcpy(options_int[opt_int_count].configuration_name, "OMEGASETTING");
	// 				}
	// 				break;
	// 			case TEC_JSON_BOOL:
	// 				break;
	// 		}

	// 		tec_json_config_advance(&config);
	// 	}
	// }

	tec_framestring_t string = tec_framestring_create("This is a test of the typing system");
	tec_framestring_t needle = tec_framestring_create("typing");
	kinc_log(KINC_LOG_LEVEL_INFO, "%s", string.string);
	tec_framestring_t string_copy = tec_framestring_copy(string);
	assert(string.string != string_copy.string);
	tec_framestring_t appended = tec_framestring_append(string, needle);

	kinc_log(KINC_LOG_LEVEL_INFO, "%s, %d", tec_framestring_find(string, needle).string, tec_framestring_find(string, needle).length);

	if (tec_framestring_compare(string, string_copy))
	{
		kinc_log(KINC_LOG_LEVEL_INFO, "FOUND A COPY OF IT!!@!!");
	}
	kinc_log(KINC_LOG_LEVEL_INFO, "%s", appended.string);

	kinc_stop();
}

void 
tec_engine_set_logic_timestep_s(double step)
{
	engine_loop_config.logic_timestep_s = step;
}

double 
tec_engine_get_render_time(void)
{
	return time_render;
}

double 
tec_engine_get_single_update_time(void)
{
	return time_single_update;
}

double 
tec_engine_get_cycle_time(void)
{
	return time_cycle;
}

void 
tec_engine_quake
(
	kinc_window_options_t * window_options, 
	kinc_framebuffer_options_t * framebuffer_options, 
	tec_engine_loop_configuration_t * loop_config
)
{
	kinc_init(window_options->title, window_options->width, window_options->height, window_options, framebuffer_options);

	tec_timediff_init(&single_update_timediff);
	tec_timediff_init(&render_timediff);
	tec_timediff_init(&cycle_timediff);

	engine_loop_config = *loop_config;

	//tec_graphics_init_context(render_context);
	//tec_audio_init_context(audio_context);
	//tec_mouse_init_context(mouse_context);
	//etc.

	kinc_set_update_callback(&tec_engine_main_loop);
	kinc_start();
}
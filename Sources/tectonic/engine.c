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
#include "debug/log.h"

#define TEC_LOG_MODULE_NAME "Engine"

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

	tec_framestring_t newstr1 = tec_framestring_create("This whatchu thinkin about grl %s");
	tec_framestring_t newstr2 = tec_framestring_create("That was %s really bad.");
	tec_framestring_t newstr3 = tec_framestring_create("God damnit");

	tec_log_info(newstr1.string, "Yeah 55555555 baby");

	//kinc_log(KINC_LOG_LEVEL_ERROR, newstr1.string, "YEAH");
	tec_log_warn(newstr2.string, "SHUT THE FUCK UP");
	tec_log_error(newstr3.string);

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
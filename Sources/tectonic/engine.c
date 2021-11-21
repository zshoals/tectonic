#include "engine.h"
#include "util/timediff.h"

#include "kinc/system.h"
#include "kinc/log.h"

#include "lib/stc/ccommon.h"

static tec_engine_context_t engine_context;

static tec_engine_loop_configuration_t * engine_loop_config;
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
	if (time_cycle > engine_loop_config->max_frametime_s)
	{
		time_cycle = engine_loop_config->max_frametime_s;
	}

	accumulator += time_cycle;

	tec_timediff_begin(&cycle_timediff, kinc_time());
	{
		//Full logic cycle
		while (accumulator >= engine_loop_config->logic_timestep_s) 
		{
			//Single logic update
			tec_timediff_begin(&single_update_timediff, kinc_time());

			engine_loop_config->update_callback(engine_context, engine_loop_config->logic_timestep_s);
			accumulator -= engine_loop_config->logic_timestep_s;

			time_single_update = tec_timediff_end(&single_update_timediff, kinc_time());
		}

		//Full render cycle
		{
			tec_timediff_begin(&render_timediff, kinc_time());

			engine_loop_config->render_callback(engine_context, accumulator /* should this subtract from something*/);

			time_render = tec_timediff_end(&render_timediff, kinc_time());
		}
	}
	time_cycle = tec_timediff_end(&cycle_timediff, kinc_time());
}

void 
tec_engine_set_logic_timestep_s(double step)
{
	engine_loop_config->logic_timestep_s = step;
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

	engine_loop_config = loop_config;
	//tec_graphics_init_context(render_context);
	//tec_audio_init_context(audio_context);
	//tec_mouse_init_context(mouse_context);
	//etc.

	kinc_set_update_callback(&tec_engine_main_loop);
	kinc_start();
}
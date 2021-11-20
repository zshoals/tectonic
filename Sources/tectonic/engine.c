#include "engine.h"
#include "util/timediff.h"

#include "kinc/system.h"
#include "kinc/log.h"

#include "lib/stc/ccommon.h"

static tec_engine_context_t engine_context;

static tec_engine_loop_configuration_t * engine_loop_config;
static double accumulator = 0.0;

static tec_timediff_t logic_timediff;
static tec_timediff_t render_timediff;
static tec_timediff_t cycle_timediff;

void
tec_engine_main_loop(void)
{

	c_autoscope(tec_timediff_advance(&logic_timediff, kinc_time()), tec_timediff_advance(&logic_timediff, kinc_time())) 
	{
		//standard decoupled fixed step/render thingy
		engine_loop_config->update_callback(engine_context, engine_loop_config->logic_timestep_s);
	}
	
	engine_loop_config->render_callback(engine_context, 0.0);
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

	tec_timediff_init(&logic_timediff);
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
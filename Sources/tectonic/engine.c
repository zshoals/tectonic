#include "engine.h"

#include "lib/stc/ccommon.h"

static tec_engine_context_t engine_context;

static tec_engine_loop_configuration_t * engine_loop_config;
static double accumulator = 0.0;

void
tec_engine_main_loop(void)
{
	//standard decoupled fixed step/render thingy
	engine_loop_config->update_callback(engine_context, engine_loop_config->logic_timestep_s);
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

	engine_loop_config = loop_config;
	//tec_graphics_init_context(render_context);
	//tec_audio_init_context(audio_context);
	//tec_mouse_init_context(mouse_context);
	//etc.

	kinc_set_update_callback(&tec_engine_main_loop);
	kinc_start();
}
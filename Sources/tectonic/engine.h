#pragma once

#include "kinc/window.h"

//Contains all necessary information to run the engine, including rendering context, loop configs, input systems, etc.
//Might be big enough to require malloc
typedef struct
tec_engine_context
{
	double bob;
	//Render context
	//Keyboard context
	//Mouse context
	//Etc.
}
tec_engine_context_t;

typedef struct 
tec_engine_loop_configuration
{
	double logic_timestep_s;
	double max_frametime_s;
	void (* update_callback)(tec_engine_context_t engine_context, double dt);
	void (* render_callback)(tec_engine_context_t engine_context, double alpha);
}
tec_engine_loop_configuration_t;

double tec_engine_get_full_logic_time(void);
void tec_engine_main_loop(void);
void tec_engine_quake(kinc_window_options_t * window_options, kinc_framebuffer_options_t * framebuffer_options, tec_engine_loop_configuration_t * loop_config);
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "kinc/window.h"
#include "kinc/system.h"
#include "kinc/display.h"
#include "kinc/log.h"
#include "kinc/graphics4/graphics.h"

#include "tectonic/engine.h"
#include "tests/test_all.h"

#include "tectonic/lib/stc/ccommon.h"
#include "tectonic/validation.h"

#include "tectonic/memory/memory.h"

#define TEC_LOG_MODULE_NAME "Main"

void game_update(tec_engine_context_t * engine_context, double dt) 
{
	//kinc_log(KINC_LOG_LEVEL_INFO, "RT %f", tec_engine_get_render_time());
}

void game_render(tec_assets_storage_t * assets, tec_engine_context_t * engine_context /*Should really just be render context only*/, double alpha) 
{
	//Possible error points:
	//	Orthomatrix
	//	Tri winding
	// Issue with clearing?
	// Issue with framebuffer initialization?
}

int kickstart(int argc, char** argv) 
{
	//=======RUN ALL TESTS======

	#ifndef TEC_DISABLE_TESTS
		tbf_run_all_tests();
		//we can return right here if we really want to
		//return 0;
	#endif

	//========TESTS END=========
	//TODO(zshoals): THIS NEEDS TO BE IN THE RIGHT LOCATION, NOT HERE REALLY
	//Although it's not a big deal to be here either I guess, but I think it should be in our engine layer
	// init_global_memory_buffers(TEC_MEGABYTES(10), TEC_MEGABYTES(10), TEC_MEGABYTES(10));
	kinc_display_init();

	char const * config_title = "Tectonic Project";
	int config_window_width = 800;
	int config_window_height = 600;
	bool config_vsync = true;

	//Initialize window and framebuffer options here with struct inits
	//No crazy construction functions, just do it manually
	//Eventually load settings from config file somewhere
	int features = 
		KINC_WINDOW_FEATURE_MAXIMIZABLE |
		KINC_WINDOW_FEATURE_MINIMIZABLE |
		KINC_WINDOW_FEATURE_RESIZEABLE;

	kinc_window_options_t wo = 
	{
		.display_index = kinc_primary_display(),
		.width = config_window_width,
		.height = config_window_height,
		.title = config_title,
		.visible = true,
		.window_features = features,
		.x = -1, //-1 = Mid Width
		.y = -1, //-1 = Mid Height
		.mode = KINC_WINDOW_MODE_WINDOW,
	};

	kinc_framebuffer_options_t fbo = 
	{
		.color_bits = 32,
		.depth_bits = 16,
		.frequency = 60, // This struct member is completely useless, does nothing
		.samples_per_pixel = 1,
		.stencil_bits = 8,
		.vertical_sync = config_vsync,
	};

	tec_engine_loop_configuration_t lc =
	{
		.logic_timestep_s = (1.0 / 60.0),
		.max_frametime_s = (1.0 / 4.0),
		.update_callback = &game_update,
		.render_callback = &game_render,
	};

	tec_engine_quake(&wo, &fbo, &lc);

	return 0;
}

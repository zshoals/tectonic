#include <stdbool.h>
#include <assert.h>

#include "kinc/window.h"
#include "kinc/system.h"
#include "kinc/display.h"
#include "kinc/log.h"
#include "kinc/graphics4/graphics.h"

#include "tectonic/engine.h"

#include "tectonic/lib/stc/ccommon.h"
#include "tectonic/cvars.h"
#include "tectonic/debug/log.h"

#define TEC_LOG_MODULE_NAME "Main"

void 
game_update(tec_engine_context_t * engine_context, double dt) 
{
	kinc_log(KINC_LOG_LEVEL_INFO, "RT %f", tec_engine_get_render_time());
}

void 
game_render(tec_engine_context_t * engine_context /*Should really just be render context only*/, double alpha) 
{
	kinc_g4_swap_buffers();
}

int 
kickstart(int argc, char** argv) 
{
	kinc_display_init();

	tec_internal_cvars_set_all_default();
	kinc_log(KINC_LOG_LEVEL_INFO, "%d", tec_cvars_get_cvar(W_VERTICAL_SYNCED).int_value);
	tec_log_info_verbose("YHep we are testing this %d", tec_cvars_get_cvar(W_WIDTH).int_value);

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
		.frequency = 1337, // This struct member is completely useless, does nothing
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

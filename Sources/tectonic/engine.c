#include "engine.h"

#include "kinc/system.h"
#include "kinc/log.h"

#include <string.h>

#include "lib/stc/ccommon.h"
#include "kinc/io/filewriter.h"
#include "kinc/io/filereader.h"


#include "kinc/graphics4/vertexstructure.h"
#include "kinc/image.h"

#include "math/matrix.h"
#include "lib/HandmadeMath.h"
#include "math/random.h"

#define TEC_LOG_MODULE_NAME "Engine"

static tec_engine_context_t engine_context;

static tec_assets_storage_t assets;


static tec_engine_loop_configuration_t engine_loop_config;
static double accumulator = 0.0;

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

	{
		//Full logic cycle
		while (accumulator >= engine_loop_config.logic_timestep_s) 
		{
			engine_loop_config.update_callback(&engine_context, engine_loop_config.logic_timestep_s);
			accumulator -= engine_loop_config.logic_timestep_s;
		}

		//Full render cycle
		{
			engine_loop_config.render_callback(&assets, &engine_context, accumulator /* should this subtract from something*/);
		}
	}
	//Kinc_stop()
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

	tec_random_init(0x86aef51a, 0x9134b3eb, 0xf2517abf);

	kinc_set_update_callback(&tec_engine_main_loop);
	kinc_start();
}
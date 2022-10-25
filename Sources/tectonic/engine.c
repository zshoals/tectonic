#include "engine.h"

#include "kinc/system.h"
#include "kinc/log.h"
#include "tectonic/simd/simd-ext.h"

#include <string.h>
#include <stdio.h>

#include "lib/stc/ccommon.h"
#include "kinc/io/filewriter.h"
#include "kinc/io/filereader.h"


#include "kinc/graphics4/vertexstructure.h"
#include "kinc/image.h"

#include "math/matrix.h"
#include "lib/HandmadeMath.h"
#include "math/random.h"

#include "validation.h"
#include "tectonic/memory/memory.h"

#include "tectonic/exd-redux/world.h"
#include "tectonic/exd-redux/world_query.h"

#include "game/components/position.h"
#include "game/components/rotation.h"

#define TEC_LOG_MODULE_NAME "Engine"

static tec_engine_context_t engine_context;

//static tec_assets_storage_t assets;


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
			//engine_loop_config.render_callback(&assets, &engine_context, accumulator /* should this subtract from something*/);
		}
	}
	
	// kinc_stop();
}

typedef enum
{
	COMP_POSITION,
	COMP_ROTATION,
	COMP_MOVABLE,
	COMP_WHATEVER
}
exd_component_e;

#include "ds/dscommon.h"


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

	engine_loop_config = *loop_config;

	allocator_t * a = default_permanent_allocator();

	exd_world_t * world = allocator_malloc(a, exd_world_t, 1);
	exd_world_init(world, a);

	exd_world_set_global_world_for_shorthand_access(world);

	exd_world_component_create_component_storage(world, position_t, COMP_POSITION);
	exd_world_component_create_component_storage(world, rotation_t, COMP_ROTATION);

	exd_entity_t saved = EXD_INVALID_ENTITY;

	for (size_t i = 0; i < 4000; ++i)
	{
		exd_entity_t entD = exd_ent_new();
		saved = entD;
		position_t * pos = exd_comp_set(COMP_POSITION, entD);
		pos->x = 9999;
		pos->y = 350280;

		if (i == 1000) 
		{
			rotation_t * rot = exd_comp_set(COMP_ROTATION, entD);
			rot->degrees = 33.023f;
		}

	}

	exd_query_t q = {0};
	// exd_query_init_from(&q, world, a);
	exd_query_init_fast(&q, a);
	{ 
		exd_query_include(&q, COMP_POSITION);
		exd_query_include(&q, COMP_ROTATION);
	}
	exd_query_iter_t it = exd_query_compile(&q);

	long double start_time = kinc_time();
	foreach_entity(ent, &it)
	{
		// position_t const * pos = exd_comp_get(0, entA);
		position_t const * posENT = exd_comp_get(COMP_POSITION, ent);
		rotation_t const * rotENT = exd_comp_get(COMP_ROTATION, ent);
		kinc_log(KINC_LOG_LEVEL_INFO, "X: %d, Y: %d, ROT: %f", posENT->x, posENT->y, rotENT->degrees);
	}
	double end_time = kinc_time() - start_time;
	kinc_log(KINC_LOG_LEVEL_INFO, "TIME TO DO THAT: %lf", end_time);

	exd_world_comp_get_result_t check_result = exd_comp_get_checked(COMP_ROTATION, saved);
	if (check_result.result == EXD_GET_COMP_RESULT_SUCCESS)
	{
		rotation_t const * checked = check_result.component;
		kinc_log(KINC_LOG_LEVEL_INFO, "Successful Ent Save: ROT %f", checked->degrees);
	}
	else if (check_result.result == EXD_GET_COMP_RESULT_MISSING_COMPONENT)
	{
		kinc_log(KINC_LOG_LEVEL_INFO, "Missing!");
	}

	kinc_set_update_callback(&tec_engine_main_loop);
	kinc_start();
}
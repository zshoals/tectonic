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

#define EXD_MAX_ENTITIES (1 << 13)

#include "tectonic/exd/entity_manifest.h"
#include "tectonic/exd/genarray.h"
#include "tectonic/exd/query.h"

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
	entity_manifest_t * world = allocator_malloc(a, entity_manifest_t, 1);
	genarray_t * positions = allocator_malloc(a, genarray_t, 1);
	genarray_t * rotations = allocator_malloc(a, genarray_t, 1);
	genarray_t * movables = allocator_malloc(a, genarray_t, 1);

	entity_manifest_init(world);
	genarray_init(positions, a, sizeof(position_t));
	genarray_init(rotations, a, sizeof(rotation_t));
	genarray_init(movables, a, 0);


	entity_t entA = entity_manifest_get_first_free(world);
	entity_t entB = entity_manifest_get_first_free(world);
	entity_t entC = entity_manifest_get_first_free(world);
	entity_t entD = entity_manifest_get_first_free(world);

	position_t * posA = genarray_set(positions, position_t, entA);
	rotation_t * rotA = genarray_set(rotations, rotation_t, entA);
	position_t * posB = genarray_set(positions, position_t, entB);
	rotation_t * rotB = genarray_set(rotations, rotation_t, entB);
	position_t * posC = genarray_set(positions, position_t, entC);
	rotation_t * rotC = genarray_set(rotations, rotation_t, entC);
	position_t * posD = genarray_set(positions, position_t, entD);
	rotation_t * rotD = genarray_set(rotations, rotation_t, entD);

	posA->x = 918;
	posA->y = 9355323;
	rotA->degrees = 350.04;

	query_build(q, world, i)
	{
		query_INCLUDE(q, positions, i);
	}

	entity_iter_t it = query_compile(q);


	u32 counter = 0;

	foreach_entities(ent, &it)
	{
		if (counter > 10000) ENSURE_UNREACHABLE("Infinite");
		position_t * pos_in_iter = genarray_get_mut(positions, position_t, ent);
		int x = pos_in_iter->x;
		int y = pos_in_iter->y;
		kinc_log(KINC_LOG_LEVEL_INFO, "ENTA POSITIONS: %d, %d", x, y);
		counter++;
	}

	kinc_set_update_callback(&tec_engine_main_loop);
	kinc_start();
}
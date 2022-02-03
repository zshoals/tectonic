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
#include "util/string.h"


#include "kinc/graphics4/vertexstructure.h"
#include "kinc/image.h"

#include "math/matrix.h"
#include "lib/HandmadeMath.h"
#include "math/random.h"
#include "io/assets.h"

#include "frequent.h"

#define TEC_LOG_MODULE_NAME "Engine"

static tec_engine_context_t engine_context;

static tec_assets_storage_t assets;


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

	tec_framestring_internal_memory_reset();
	//kinc_stop();

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

local_func void
default_asset_and_resource_initialization_routine(void)
{
	// tec_asset_manager_initialize(&assets);

	// //Load vertex and fragment shaders
	// tec_asset_manager_load_vertex(&assets, "textured-standard.vert");
	// tec_asset_manager_load_fragment(&assets, "textured-standard.frag");
	// //Make default pipelines and register them to resources
	// kinc_g4_vertex_structure_t vert_format;
	// kinc_g4_vertex_structure_init(&vert_format);
	// kinc_g4_vertex_structure_add(&vert_format, "vertexPosition", KINC_G4_VERTEX_DATA_FLOAT3);
	// kinc_g4_vertex_structure_add(&vert_format, "vertexColor", KINC_G4_VERTEX_DATA_FLOAT4);

	// //Fragment and vertex shaders need to be compiled and then actually assigned to the pipeline
	// //omegalul error.

	// // pipeline.name = "textured-normal";
	// // pipeline.pipeline = kpipe;
	// // pipeline.vertex_structure = vert_format;
	// // pipeline.pipeline.vertex_shader = &tec_asset_manager_find_vertex(&assets, "textured-standard.vert")->vert;
	// // pipeline.pipeline.fragment_shader = &tec_asset_manager_find_fragment(&assets, "textured-standard.frag")->frag;

	// // pipeline.pipeline.input_layout[0] = &pipeline.vertex_structure;
	// // pipeline.pipeline.input_layout[1] = NULL;

	// kinc_g4_pipeline_compile(&pipeline.pipeline);

	// tec_asset_manager_register_pipeline(&assets, pipeline);

	// //Load textures (1x white pixel for now)
	// tec_asset_manager_load_image_to_texture(&assets, "white1x1.png");
	// //construct the default materials with the linked uniforms,

	// tec_material_t mat_default;

	// //I HAVE TO FIX THIS DUMBASS INTERFACE
	// tec_material_initialize(&mat_default, "default-textured", &tec_asset_manager_find_pipeline(&assets, "textured-normal")->pipeline);

	// tec_material_assign_texture(&mat_default, "tex", &tec_asset_manager_find_texture(&assets, "white1x1.png")->texture, 0);

	// hmm_m4 matrix = HMM_Orthographic(0.0, 1.0, 1.0, 0.0, 5.0, 500.0); // ?????
	// kinc_matrix4x4_t out = tec_matrix_convert(matrix);
	// tec_material_uniform_data_u udata;
	// udata.mat4_value = out;
	// tec_material_assign_uniform(&mat_default, "projectionMatrix", udata, TEC_UNIFORM_TYPE_MAT4, 0);
	
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

	tec_timediff_init(&single_update_timediff);
	tec_timediff_init(&render_timediff);
	tec_timediff_init(&cycle_timediff);

	engine_loop_config = *loop_config;

	//tec_graphics_init_context(render_context);
	//tec_audio_init_context(audio_context);
	//tec_mouse_init_context(mouse_context);
	//etc.

	default_asset_and_resource_initialization_routine();

	kinc_set_update_callback(&tec_engine_main_loop);
	kinc_start();
}
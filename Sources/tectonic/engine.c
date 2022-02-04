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
#include "assets/assets.h"

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
	 tec_assets_initialize(&assets);

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



	tec_assets_load_vertex_shader(&assets, "textured-standard.vert");
	tec_assets_load_fragment_shader(&assets, "textured-standard.frag");
	tec_assref_vertex_shader_t vert = tec_assets_find_vertex_shader(&assets, "textured-standard.vert");
	tec_assref_fragment_shader_t frag = tec_assets_find_fragment_shader(&assets, "textured-standard.frag");
	kinc_g4_vertex_structure_t vs;
	kinc_g4_vertex_structure_init(&vs);
	kinc_g4_vertex_structure_add(&vs, "vertexPosition", KINC_G4_VERTEX_DATA_FLOAT3);
	kinc_g4_vertex_structure_add(&vs, "vertexColor", KINC_G4_VERTEX_DATA_FLOAT4);
	tec_assref_shader_program_t shader = tec_pipeline_create_program(&assets, "standard_texturizer", vert, frag, vs, TEC_BLENDING_NORMAL);
	tec_pipeline_compile_program(&assets, shader);

	tec_assref_material_t material = tec_material_create_material(&assets, "Normal draw w/ time uniform", shader);
	tec_assref_texture_t textureDummy = {.asset_location = 99999, .status = 0};
	tec_material_assign_texture(&assets, material, "texSampler", textureDummy, 0);
	tec_material_uniform_data_u udata = {.float_values[0] = 1337.0};
	tec_material_assign_uniform(&assets, material, "time", udata, TEC_UNIFORM_TYPE_FLOAT, 0);
	
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
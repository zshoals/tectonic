/*
	NOTE: THIS FILE IS AUTOGENERATED VIA KMAKE
	THIS FILE SHOULD NOT BE EDITED MANUALLY

	Autogenerated list of image resources within tectonic.
	Generated at: Wed Sep 28 2022
*/

#pragma once

typedef enum
{
	TEC_IMAGE_RESOURCE_WHITE1X1,
	TEC_IMAGE_RESOURCE_SUBDIR1_MISSING,
	TEC_IMAGE_RESOURCE_SUBDIR1_BOBS_PUNCH,

	TEC_IMAGE_RESOURCE_MAXIMUM_COUNT
}
tec_image_resource_e;

char const * tec_resource_get_image(tec_image_resource_e image_ref);
char const * tec_resource_get_image_enum_name(tec_image_resource_e image_ref);

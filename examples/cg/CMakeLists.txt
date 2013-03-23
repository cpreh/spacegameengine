find_package(
	Cg
	REQUIRED
)

add_sge_example(
	cg_parameters
	"sgecg;sgeimagecolor;sgeinput;sgerenderer;sgerenderercg;sgesystems;sgeviewport;sgewindow"
	"${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
	"${Cg_INCLUDE_DIRS}"
)

add_sge_example(
	cg_simple
	"sgecg;sgeimagecolor;sgeinput;sgerenderer;sgerenderercg;sgesystems;sgeviewport;sgewindow"
	"${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
	"${Cg_INCLUDE_DIRS}"
)

add_sge_example(
	cg_texture
	"sgecg;sgeconfig;sgeimagecolor;sgeinput;sgemedia;sgerenderer;sgerenderercg;sgesystems;sgeviewport;sgewindow"
	"${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
	"${Cg_INCLUDE_DIRS}"
)

add_sge_example(
	cg_pointsprites
	"sgecg;sgeconfig;sgeimagecolor;sgeinput;sgemedia;sgerenderer;sgerenderercg;sgesystems;sgeviewport;sgewindow"
	"${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
	"${Cg_INCLUDE_DIRS}"
)

message("Fix the cg blending example!")

#add_sge_example(
#	cg_blending
#	"sgeconfig;sgeimage2d;sgepostprocessing;sgerenderer;sgeshader;sgesystems;sgetexture;sgeviewport;sgewindow"
#	"${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
#	"${Cg_INCLUDE_DIRS}"
#)

find_package(
	Cg
	REQUIRED
)

include_directories(
	"${Cg_INCLUDE_DIRS}"
)

add_sge_example(
	cg_parameters
	"sgecg;sgeimage;sgeinput;sgerenderer;sgerenderercg;sgesystems;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Boost_FILESYSTEM_LIBRARIES}"
)

add_sge_example(
	cg_simple
	"sgecg;sgeimage;sgeinput;sgerenderer;sgerenderercg;sgesystems;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Boost_FILESYSTEM_LIBRARIES}"
)

add_sge_example(
	cg_texture
	"sgecg;sgeconfig;sgeimage;sgeinput;sgemedia;sgerenderer;sgerenderercg;sgesystems;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Boost_FILESYSTEM_LIBRARIES}"
)

add_sge_example(
	cg_pointsprites
	"sgecg;sgeconfig;sgeimage;sgeinput;sgemedia;sgerenderer;sgerenderercg;sgesystems;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Boost_FILESYSTEM_LIBRARIES}"
)

add_sge_example(
	cg_blending
	"sgeconfig;sgeimage2d;sgerenderer;sgesprite;sgesystems;sgetexture;sgeviewport;sgewindow;sgepostprocessing;sgeshader"
	"${Fcppt_core_LIBRARIES};${Boost_FILESYSTEM_LIBRARIES}"
)

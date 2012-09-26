find_package(
	Cg
	REQUIRED
)

add_sge_example(
	cg_parameters
	"sgecg;sgeimage;sgeinput;sgerenderer;sgerenderercg;sgesystems;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Boost_FILESYSTEM_LIBRARIES}"
	"${Cg_INCLUDE_DIRS}"
)

add_sge_example(
	cg_simple
	"sgecg;sgeimage;sgeinput;sgerenderer;sgerenderercg;sgesystems;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Boost_FILESYSTEM_LIBRARIES}"
	"${Cg_INCLUDE_DIRS}"
)

add_sge_example(
	cg_texture
	"sgecg;sgeconfig;sgeimage;sgeinput;sgemedia;sgerenderer;sgerenderercg;sgesystems;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Boost_FILESYSTEM_LIBRARIES}"
	"${Cg_INCLUDE_DIRS}"
)

add_sge_example(
	cg_pointsprites
	"sgecg;sgeconfig;sgeimage;sgeinput;sgemedia;sgerenderer;sgerenderercg;sgesystems;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Boost_FILESYSTEM_LIBRARIES}"
	"${Cg_INCLUDE_DIRS}"
)

add_sge_example(
	cg_blending
	"sgeconfig;sgeimage2d;sgepostprocessing;sgerenderer;sgeshader;sgesystems;sgetexture;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Boost_FILESYSTEM_LIBRARIES}"
	"${Cg_INCLUDE_DIRS}"
)

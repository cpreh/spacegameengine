add_sge_example(
	bvh_planar
	"sgeconfig;sgeimage;sgeimagecolor;sgeinput;sgerenderer;sgesprite;sgesystems;sgeviewport;sgewindow"
	"${fcppt_core_TARGET};${Boost_CHRONO_LIBRARIES}"
	""
)

add_sge_console_example(
	bvh_benchmark
	""
	"${fcppt_core_TARGET};${Boost_CHRONO_LIBRARIES}"
	""
)

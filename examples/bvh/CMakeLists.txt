add_sge_example(
	bvh_planar
	"sgeconfig;sgeimage;sgeinput;sgerenderer;sgesprite;sgesystems;sgeviewport;sgewindow"
	"${Fcppt_core_LIBRARIES};${Boost_CHRONO_LIBRARIES}"
	""
)

add_sge_console_example(
	bvh_benchmark
	""
	"${Fcppt_core_LIBRARIES};${Boost_CHRONO_LIBRARIES}"
	""
)

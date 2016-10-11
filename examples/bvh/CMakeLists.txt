add_sge_console_example(
	bvh/benchmark
	SGE_DEPS
		sgebvh_interface
	ADDITIONAL_DEPS
		${fcppt_core_TARGET}
)

# TODO: Why is image needed here?
add_sge_example(
	bvh/planar
	SGE_DEPS
		sgebvh_interface
		sgeimage
		sgeimagecolor
		sgeinput
		sgerenderer
		sgesprite
		sgesystems
		sgeviewport
		sgewindow
	ADDITIONAL_DEPS
		${fcppt_core_TARGET}
)

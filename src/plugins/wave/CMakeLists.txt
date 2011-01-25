SET(
	SGE_WAVE_FILES
	src/plugins/wave/file.hpp
	src/plugins/wave/loader.hpp
	src/plugins/wave/src/exports.cpp
	src/plugins/wave/src/file.cpp
	src/plugins/wave/src/loader.cpp
)

ADD_SGE_PLUGIN(
	wave
	""
)

set(
	SGE_WAVE_FILES
	src/plugins/wave/include/sge/wave/file.hpp
	src/plugins/wave/include/sge/wave/loader.hpp
	src/plugins/wave/include/sge/wave/stream_ptr.hpp
	src/plugins/wave/src/exports.cpp
	src/plugins/wave/src/file.cpp
	src/plugins/wave/src/loader.cpp
)

include_directories(
	"${CMAKE_CURRENT_SOURCE_DIR}/include"
)

add_sge_plugin(
	wave
	"sgeaudio"
	""
)

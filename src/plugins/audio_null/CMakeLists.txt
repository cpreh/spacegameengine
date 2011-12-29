set(
	SGE_AUDIO_NULL_FILES
	src/plugins/audio_null/include/sge/audio_null/buffer.hpp
	src/plugins/audio_null/include/sge/audio_null/listener.hpp
	src/plugins/audio_null/include/sge/audio_null/player.hpp
	src/plugins/audio_null/include/sge/audio_null/positional.hpp
	src/plugins/audio_null/src/buffer.cpp
	src/plugins/audio_null/src/exports.cpp
	src/plugins/audio_null/src/listener.cpp
	src/plugins/audio_null/src/player.cpp
	src/plugins/audio_null/src/positional.cpp
)

include_directories(
	"${CMAKE_CURRENT_SOURCE_DIR}/include"
)

add_sge_plugin(
	audio_null
	"sgeaudio"
	""
)

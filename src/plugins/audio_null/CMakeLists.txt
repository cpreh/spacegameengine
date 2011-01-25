SET(
	SGE_AUDIO_NULL_FILES
	src/plugins/audio_null/buffer.hpp
	src/plugins/audio_null/listener.hpp
	src/plugins/audio_null/player.hpp
	src/plugins/audio_null/positional.hpp
	src/plugins/audio_null/src/exports.cpp
	src/plugins/audio_null/src/listener.cpp
	src/plugins/audio_null/src/player.cpp
)

ADD_SGE_PLUGIN(
	audio_null
	""
)

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

APPEND_SOURCE_DIR_AND_MAKE_GROUPS(
	"${SGE_AUDIO_NULL_FILES}"
	SGE_AUDIO_NULL_FILES_ABS
)

ADD_LIBRARY (sgeaudionull SHARED ${SGE_AUDIO_NULL_FILES_ABS})

TARGET_LINK_LIBRARIES (sgeaudionull sgecore)

INSTALL (TARGETS sgeaudionull DESTINATION lib/sge)

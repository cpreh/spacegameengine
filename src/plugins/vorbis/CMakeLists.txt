FILE (GLOB sgevorbisfiles src/*.cpp)

ADD_LIBRARY (sgevorbis SHARED ${sgevorbisfiles})
TARGET_LINK_LIBRARIES (sgevorbis sgecore vorbisfile vorbis m ogg) #TODO: use pkg-config

INSTALL (TARGETS sgevorbis DESTINATION ${pluginpath})

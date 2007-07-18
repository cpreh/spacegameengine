FILE (GLOB sgevorbisfiles src/*.cpp)

INCLUDE (UsePkgConfig)

ADD_LIBRARY (sgevorbis SHARED ${sgevorbisfiles})
PKGCONFIG (vorbis vorbisincludedir vorbislibdir vorbislinkflags vorbiscflags)
TARGET_LINK_LIBRARIES (sgevorbis sgecore vorbisfile ${vorbislinkflags})

INSTALL (TARGETS sgevorbis DESTINATION ${pluginpath})

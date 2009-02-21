IF (WIN32)
	SET (LIBRARY_OUTPUT_PATH ${pluginpath})
ENDIF ()


FIND_PACKAGE(DevIL)


OPTION (ENABLE_BULLET "Build the bullet collision plugin" OFF)

IF(DevIL_FOUND)
	OPTION (ENABLE_DEVIL "Build the devil image loader plugin" ON)
ELSE (DevIL_FOUND)
	OPTION (ENABLE_DEVIL "Build the devil image loader plugin" OFF)
ENDIF(DevIL_FOUND)

OPTION (ENABLE_DINPUT "Build the Direct Input plugin" OFF)
OPTION (ENABLE_FREETYPE "Build the freetype font plugin" OFF)
OPTION (ENABLE_MAD "Build the mad mp3 loader plugin" OFF)
OPTION (ENABLE_OPENAL "Build the openal audio plugin" OFF)
OPTION (ENABLE_OPENGL "Build the opengl render plugin" OFF)
OPTION (ENABLE_VORBIS "Build the vorbis loader plugin" OFF)
OPTION (ENABLE_WAVE "Build the wave loader plugin" OFF)
OPTION (ENABLE_X11INPUT "Build the x11 input plugin" OFF)

IF(ENABLE_BULLET)
	ADD_SUBDIRECTORY (bullet)
ENDIF ()

IF(ENABLE_D3D9)
	ADD_SUBDIRECTORY (d3d9)
ENDIF ()

IF (ENABLE_DEVIL)
	ADD_SUBDIRECTORY (devil)
ENDIF ()

IF (ENABLE_DINPUT)
	ADD_SUBDIRECTORY (dinput)
ENDIF ()

IF (ENABLE_FREETYPE)
	ADD_SUBDIRECTORY (freetype)
ENDIF ()

IF (ENABLE_MAD)
	ADD_SUBDIRECTORY (mad)
ENDIF ()

IF (ENABLE_OPENAL)
	ADD_SUBDIRECTORY (openal)
ENDIF ()

IF (ENABLE_OPENGL)
	ADD_SUBDIRECTORY (opengl)
ENDIF ()

IF (ENABLE_VORBIS)
	ADD_SUBDIRECTORY (vorbis)
ENDIF ()

IF (ENABLE_WAVE)
	ADD_SUBDIRECTORY (wave)
ENDIF ()

IF (ENABLE_X11INPUT)
	ADD_SUBDIRECTORY (x11input)
ENDIF ()

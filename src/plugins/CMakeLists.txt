IF (WIN32)
	SET (LIBRARY_OUTPUT_PATH ${pluginpath})
ENDIF ()


FIND_PACKAGE(DevIL)
FIND_PACKAGE(Freetype)
FIND_PACKAGE(GLEW)
FIND_PACKAGE(ODE)
FIND_PACKAGE(OpenGL)
FIND_PACKAGE(OpenAL)
FIND_PACKAGE(Vorbis)

OPTION (ENABLE_AUDIO_NULL "Build the null audio player plugin" OFF)
OPTION (ENABLE_BULLET "Build the bullet collision plugin" OFF)
OPTION (ENABLE_CELL "Build the cell collision plugin" ON)
OPTION (ENABLE_DINPUT "Build the Direct Input plugin" OFF)
OPTION (ENABLE_MD3 "Build the md3 model loader plugin" ON)
OPTION (ENABLE_WAVE "Build the wave loader plugin" ON)

IF(ODE_FOUND)
	OPTION (ENABLE_ODE "Build the ode collision plugin" ON)
ELSE()
	OPTION (ENABLE_ODE "Build the ode collision plugin" OFF)
ENDIF()

IF(DevIL_FOUND)
	OPTION (ENABLE_DEVIL "Build the devil image loader plugin" ON)
ELSE ()
	OPTION (ENABLE_DEVIL "Build the devil image loader plugin" OFF)
ENDIF()


IF(FREETYPE_FOUND)
	OPTION (ENABLE_FREETYPE "Build the freetype font plugin" ON)
ELSE()
	OPTION (ENABLE_FREETYPE "Build the freetype font plugin" OFF)
ENDIF()


IF(OPENAL_FOUND)
	OPTION (ENABLE_OPENAL "Build the openal audio plugin" ON)
ELSE()
	OPTION (ENABLE_OPENAL "Build the openal audio plugin" OFF)
ENDIF()


IF(OPENGL_FOUND)
	OPTION (ENABLE_OPENGL "Build the opengl render plugin" ON)
ELSE()
	OPTION (ENABLE_OPENGL "Build the opengl render plugin" OFF)
ENDIF()


IF(VORBIS_FOUND)
	OPTION (ENABLE_VORBIS "Build the vorbis loader plugin" ON)
ELSE()	
	OPTION (ENABLE_VORBIS "Build the vorbis loader plugin" OFF)
ENDIF()


IF(X11_Xinput_FOUND)
	OPTION (ENABLE_X11INPUT "Build the x11 input plugin" ON)
ELSE()
	OPTION (ENABLE_X11INPUT "Build the x11 input plugin" OFF)
ENDIF()

IF(ENABLE_AUDIO_NULL)
	ADD_SUBDIRECTORY (audio_null)
ENDIF ()

IF(ENABLE_BULLET)
	ADD_SUBDIRECTORY (bullet)
ENDIF ()

IF(ENABLE_CELL)
	ADD_SUBDIRECTORY (cell)
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

IF (ENABLE_MD3)
	ADD_SUBDIRECTORY (md3)
ENDIF ()

IF(ENABLE_ODE)
	ADD_SUBDIRECTORY (ode)
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

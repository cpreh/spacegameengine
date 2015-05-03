find_package(D3D9)
find_package(DInput)
find_package(EVDEV)
find_package(GLEW)
find_package(OpenGL)
find_package(OpenAL)
find_package(Pango)
find_package(PNG 1.4.1)
find_package(Vorbis)

# These plugins have no dependencies
OPTION (ENABLE_AUDIO_NULL "Build the null audio player plugin" OFF)

OPTION (ENABLE_WAVE "Build the wave loader plugin" ON)

# These plugins have dependencies
OPTION (ENABLE_D3D9 "Build the d3d9 render plugin" ${D3D9_FOUND})

OPTION (ENABLE_DINPUT "Build the direct input 8 plugin" ${DINPUT_FOUND})

OPTION (ENABLE_EVDEV "Build the evdev input plugin" ${EVDEV_FOUND})

OPTION (ENABLE_GDIFONT "Build the gdi font plugin" ${WIN32})

OPTION (ENABLE_OPENAL "Build the openal audio plugin" ${OPENAL_FOUND})

if(
	OPENGL_FOUND AND GLEW_FOUND
)
	set(
		OPENGL_AVAILABLE
		TRUE
	)
else()
	set(
		OPENGL_AVAILABLE
		FALSE
	)
endif()

OPTION (ENABLE_OPENGL "Build the opengl render plugin" ${OPENGL_AVAILABLE})

OPTION (ENABLE_PANGO "Build the pango font plugin" ${PANGO_FOUND})

OPTION (ENABLE_PNG "Build the libpng plugin" ${PNG_FOUND})

OPTION (ENABLE_VORBIS "Build the vorbis loader plugin" ${VORBIS_FOUND})

OPTION (ENABLE_X11INPUT "Build the x11 input plugin" ${X11_Xinput_FOUND})

IF(ENABLE_AUDIO_NULL)
	ADD_SUBDIRECTORY (audio_null)
ENDIF ()

IF(ENABLE_D3D9)
	ADD_SUBDIRECTORY (d3d9)
ENDIF ()

IF (ENABLE_DINPUT)
	ADD_SUBDIRECTORY (dinput)
ENDIF ()

IF (ENABLE_EVDEV)
	ADD_SUBDIRECTORY (evdev)
ENDIF ()

IF (ENABLE_GDIFONT)
	ADD_SUBDIRECTORY (gdifont)
ENDIF ()

IF (ENABLE_OPENAL)
	ADD_SUBDIRECTORY (openal)
ENDIF ()

IF (ENABLE_OPENGL)
	ADD_SUBDIRECTORY (opengl)
ENDIF ()

IF (ENABLE_PANGO)
	ADD_SUBDIRECTORY (pango)
ENDIF ()

IF (ENABLE_PNG)
	ADD_SUBDIRECTORY (libpng)
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

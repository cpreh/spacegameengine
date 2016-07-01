find_package(
	Cg
)

find_package(
	D3D9
)

find_package(
	DInput
)

find_package(
	EVDEV
)

find_package(
	OpenGL
)

find_package(
	OpenAL
)

find_package(
	Pango
)

find_package(
	PNG
	1.4.1
)

find_package(
	Vorbis
)

find_package(
	Wayland
	QUIET
)

find_package(
	Xkbcommon
)

find_package(
	X11
)

option(
	ENABLE_X11
	"Enable X11 in plugins"
	${X11_FOUND}
)

option(
	ENABLE_WAYLAND
	"Enable Wayland in plugins"
	OFF
)
#${WAYLAND_CLIENT_FOUND}

add_sge_lib(
	audio_null
	"Build the null audio player plugin"
	OFF
)

add_sge_lib(
	d3d9
	"Build the d3d9 render plugin"
	${D3D9_FOUND}
)

add_sge_lib(
	dinput
	"Build the direct input 8 plugin"
	${DINPUT_FOUND}
)

add_sge_lib(
	evdev
	"Build the evdev input plugin"
	${EVDEV_FOUND}
)

add_sge_lib(
	gdifont
	"Build the gdi font plugin"
	"${WIN32}"
)

add_sge_lib(
	openal
	"Build the openal audio plugin"
	${OPENAL_FOUND}
)

add_sge_lib(
	opengl
	"Build the opengl render plugin"
	${OPENGL_FOUND}
)

add_sge_lib(
	pango
	"Build the pango font plugin"
	"${PANGO_FOUND}"
)

add_sge_lib(
	libpng
	"Build the libpng plugin"
	${PNG_FOUND}
)

add_sge_lib(
	vorbis
	"Build the vorbis loader plugin"
	${VORBIS_FOUND}
)

add_sge_lib(
	wave
	"Build the wave loader plugin"
	ON
)

add_sge_lib(
	wininput
	"Build the WinAPI input plugin"
	"${WIN32}"
)

if(
	WAYLAND_CLIENT_FOUND
	AND
	XKB_COMMON_FOUND
	AND
	ENABLE_WAYLAND
)
	set(
		WLINPUT_DEFAULT
		TRUE
	)
else()
	set(
		WLINPUT_DEFAULT
		FALSE
	)
endif()

add_sge_lib(
	wlinput
	"Build the Wayland input plugin"
	"${WLINPUT_DEFAULT}"
)

if(
	ENABLE_X11
	AND
	${X11_Xinput_FOUND}
)
	set(
		X11INPUT_DEFAULT
		TRUE
	)
else()
	set(
		X11INPUT_DEFAULT
		FALSE
	)
endif()

add_sge_lib(
	x11input
	"Build the X11 input plugin"
	"${X11INPUT_DEFAULT}"
)

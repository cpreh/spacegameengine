include(
	FindPkgConfig
)

include(
	PkgConfigSGE
)

find_package(
	Cg
)

find_package(
	D3D9
)

find_package(
	DINPUT
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

pkg_check_modules_sge(
	PANGO
	pango
	pangoft2
	fontconfig
)

find_package(
	PNG
	1.4.1
)

pkg_check_modules(
	VORBIS
	IMPORTED_TARGET
	ogg
	vorbis
	vorbisfile
)

pkg_check_modules(
	WAYLAND_INPUT
	IMPORTED_TARGET
	wayland-client
	xkbcommon
)

pkg_check_modules(
	XINPUT
	IMPORTED_TARGET
	xi
	x11
)

if(
	NOT DEFINED ENABLE_SDL
)
	find_package(
		SDL2
	)
endif()

option(
	ENABLE_SDL
	"Enable SDL support in plugins"
	${SDL2_FOUND}
)

if(
	ENABLE_SDL
)
	find_package(
		SDL2
		REQUIRED
	)
endif()

add_sge_lib(
	audio_null
	"Build the null audio player plugin"
	OFF
)

add_sge_lib(
	d3d9
	"Build the d3d9 render plugin"
	"${D3D9_FOUND}"
)

add_sge_lib(
	dinput
	"Build the direct input 8 plugin"
	"${DINPUT_FOUND}"
)

add_sge_lib(
	evdev
	"Build the evdev input plugin"
	"${EVDEV_FOUND}"
)

add_sge_lib(
	gdifont
	"Build the gdi font plugin"
	"${WIN32}"
)

add_sge_lib(
	openal
	"Build the openal audio plugin"
	"${OPENAL_FOUND}"
)

add_sge_lib(
	opengl
	"Build the opengl render plugin"
	"${OPENGL_FOUND}"
)

add_sge_lib(
	pango
	"Build the pango font plugin"
	"${PANGO_FOUND}"
)

add_sge_lib(
	libpng
	"Build the libpng plugin"
	"${PNG_FOUND}"
)

add_sge_lib(
	sdlinput
	"Build the SDL2 input plugin"
	"${SDL2_FOUND}"
)

add_sge_lib(
	vorbis
	"Build the vorbis loader plugin"
	"${VORBIS_FOUND}"
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

add_sge_lib(
	wlinput
	"Build the Wayland input plugin"
	"${WAYLAND_INPUT}"
)

add_sge_lib(
	x11input
	"Build the X11 input plugin"
	"${XINPUT_FOUND}"
)

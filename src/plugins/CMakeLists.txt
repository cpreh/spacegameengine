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
	X11
)

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

add_sge_lib(
	x11input
	"Build the x11 input plugin"
	"${X11_Xinput_FOUND}"
)

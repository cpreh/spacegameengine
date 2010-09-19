find_package(OpenGL)

INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})

FILE(
	GLOB sgeopenglfiles
	src/*.cpp
	context/src/*.cpp
	convert/src/*.cpp
	glew/src/*.cpp
	glsl/src/*.cpp
	glsl/arb/src/*.cpp
	glsl/native/src/*.cpp
	glsl/programfuncs/src/*.cpp
	glsl/shaderfuncs/src/*.cpp
	glsl/uniform/src/*.cpp
	texfuncs/src/*.cpp
	vf/src/*.cpp
)
	
IF (X11_FOUND)
	FILE (
		GLOB sgeopenglx11files
		glx/src/*.cpp
		x11/src/*.cpp
		x11/resolution/src/create.cpp
		x11/resolution/src/instance.cpp
	)

	SET (sgeopenglfiles ${sgeopenglfiles} ${sgeopenglx11files})

	IF(X11_xf86vmode_FOUND)
		FIND_LIBRARY(
			SGE_HAVE_XF86_VMODE
			"Xxf86vm"
		)

		INCLUDE_DIRECTORIES(${X11_xf86vmode_INCLUDE_PATH})

		FILE (GLOB sgeopenglxf86files
			xf86vmode/src/*.cpp
			x11/resolution/src/xf86_vmode.cpp)
		SET (sgeopenglfiles ${sgeopenglfiles} ${sgeopenglxf86files})
	ENDIF()

	IF(X11_Xrandr_FOUND)
		FIND_LIBRARY(
			SGE_HAVE_XRANDR
			"Xrandr"
		)

		INCLUDE_DIRECTORIES(${X11_Xrandr_INCLUDE_PATH})

		FILE (GLOB sgeopenglxrandrfiles
			xrandr/src/*.cpp
			x11/resolution/src/xrandr_mode.cpp)
		SET (sgeopenglfiles ${sgeopenglfiles} ${sgeopenglxrandrfiles})
	ENDIF()
ELSEIF (WIN32)
	FILE (
		GLOB sgeopenglwglfiles
		wgl/src/*.cpp
		windows/src/*.cpp
	)
	SET (sgeopenglfiles ${sgeopenglfiles} ${sgeopenglwglfiles})
ENDIF ()

INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})

INCLUDE_DIRECTORIES(${GLEW_INCLUDE_PATH})

ADD_LIBRARY (sgeopengl SHARED ${sgeopenglfiles})

TARGET_LINK_LIBRARIES (sgeopengl sgecore ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})

IF (UNIX)
	TARGET_LINK_LIBRARIES (sgeopengl ${X11_LIBRARIES})

	IF(X11_xf86vmode_FOUND)
		TARGET_LINK_LIBRARIES(sgeopengl ${SGE_HAVE_XF86_VMODE})
	ENDIF()

	IF(X11_Xrandr_FOUND)
		TARGET_LINK_LIBRARIES(sgeopengl ${SGE_HAVE_XRANDR})
	ENDIF()
ENDIF ()

INSTALL (TARGETS sgeopengl DESTINATION lib/sge)

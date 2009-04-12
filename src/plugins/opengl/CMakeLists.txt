find_package(OpenGL)

IF(NOT OPENGL_FOUND)
	message(STATUS "OpenGL libraries not found, skipping module sgeopengl")
	return()
ENDIF()

INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})

FILE (GLOB sgeopenglfiles
	src/*.cpp
	glsl/src/*.cpp
	glsl/attribute/src/*.cpp
	glsl/uniform/src/*.cpp
	vf/src/*.cpp)
	
IF (X11_FOUND)
	FILE (GLOB sgeopenglx11files
		glx/src/*.cpp
		x11/src/*.cpp
		x11/resolution/src/create.cpp
		x11/resolution/src/instance.cpp)
	SET (sgeopenglfiles ${sgeopenglfiles} ${sgeopenglx11files})

	IF(X11_xf86vmode_FOUND)
		FIND_LIBRARY(
			SGE_HAVE_XF86_VMODE
			"Xxf86vm")

		INCLUDE_DIRECTORIES(${X11_xf86vmode_INCLUDE_PATH})

		FILE (GLOB sgeopenglxf86files
			xf86vmode/src/*.cpp
			x11/resolution/src/xf86_vmode.cpp)
		SET (sgeopenglfiles ${sgeopenglfiles} ${sgeopenglxf86files})
	ENDIF()

	IF(X11_Xrandr_FOUND)
		FIND_LIBRARY(
			SGE_HAVE_XRANDR
			"Xrandr")

		INCLUDE_DIRECTORIES(${X11_Xrandr_INCLUDE_PATH})

		FILE (GLOB sgeopenglxrandrfiles
			xrandr/src/*.cpp
			x11/resolution/src/xrandr_mode.cpp)
		SET (sgeopenglfiles ${sgeopenglfiles} ${sgeopenglxrandrfiles})
	ENDIF()
ELSEIF (WIN32)
	FILE (GLOB sgeopenglwglfiles
		wgl/src/*.cpp
		windows/src/*.cpp)
	SET (sgeopenglfiles ${sgeopenglfiles} ${sgeopenglwglfiles})
ENDIF ()

IF (MSVC)
	INCLUDE_DIRECTORIES (${WININCLUDES}/glew/include)
	LINK_DIRECTORIES (${CMAKE_SOURCE_DIR}/${WINLIBS}/glew/lib)
ELSE ()
	INCLUDE_DIRECTORIES(${GLEW_INCLUDE_PATH})
ENDIF ()

ADD_LIBRARY (sgeopengl SHARED ${sgeopenglfiles})
TARGET_LINK_LIBRARIES (sgeopengl sgecore ${OPENGL_LIBRARIES})

IF (UNIX)
	TARGET_LINK_LIBRARIES (sgeopengl ${GLEW_LIBRARY} ${X11_LIBRARIES})
	IF(X11_xf86vmode_FOUND)
		TARGET_LINK_LIBRARIES(sgeopengl Xxf86vm)
	ENDIF()
	IF(X11_Xrandr_FOUND)
		TARGET_LINK_LIBRARIES(sgeopengl Xrandr)
	ENDIF()
ELSEIF (WIN32)
	TARGET_LINK_LIBRARIES (sgeopengl glew32)
ENDIF ()

INSTALL (TARGETS sgeopengl DESTINATION ${pluginpath})

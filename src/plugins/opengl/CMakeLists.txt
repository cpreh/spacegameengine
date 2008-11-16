find_package(OpenGL)

IF(NOT OPENGL_FOUND)
	message(STATUS "OpenGL libraries not found, skipping module sgeopengl")
	return()
ENDIF()


FILE (GLOB sgeopenglfiles
	src/*.cpp
	glsl/src/*.cpp
	vf/src/*.cpp)
	
IF (X11_FOUND)
	FILE (GLOB sgeopenglx11files
		glx/src/*.cpp)
	SET (sgeopenglfiles ${sgeopenglfiles} ${sgeopenglx11files})

	IF(X11_xf86vmode_FOUND)
		FIND_LIBRARY(
			SGE_HAVE_XF86_VMODE
			"Xxf86vm")

		INCLUDE_DIRECTORIES(${X11_xf86vmode_INCLUDE_PATHatng	})

		FILE (GLOB sgeopenglxf86files
			xf86/src/*.cpp)
		SET (sgeopenglfiles ${sgeopenglfiles} ${sgeopenglxf86files})
	ENDIF()
ELSEIF (WIN32)
	FILE (GLOB sgeopenglwglfiles
		wgl/src/*.cpp)
	SET (sgeopenglfiles ${sgeopenglfiles} ${sgeopenglwglfiles})
ENDIF ()

IF (MSVC)
	INCLUDE_DIRECTORIES (${WININCLUDES}/glew/include)
	LINK_DIRECTORIES (${CMAKE_SOURCE_DIR}/${WINLIBS}/glew/lib)
ENDIF ()

ADD_LIBRARY (sgeopengl SHARED ${sgeopenglfiles})
TARGET_LINK_LIBRARIES (sgeopengl sgecore ${OPENGL_LIBRARIES})

IF (UNIX)
	TARGET_LINK_LIBRARIES (sgeopengl GLEW ${X11_LIBRARIES})
	IF(X11_xf86vmode_FOUND)
		TARGET_LINK_LIBRARIES(sgeopengl Xxf86vm)
	ENDIF()
ELSEIF (WIN3})
	TARGET_LINK_LIBRARIES (sgeopengl glew32)
ENDIF ()

INSTALL (TARGETS sgeopengl DESTINATION ${pluginpath})

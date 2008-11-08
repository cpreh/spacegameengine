FILE (GLOB sgeopenglfiles
	src/*.cpp
	glsl/src/*.cpp
	vf/src/*.cpp)
	
IF (${SGE_HAVE_X11})
	FILE (GLOB sgeopenglx11files
		glx/src/*.cpp)
	SET (sgeopenglfiles ${sgeopenglfiles} ${sgeopenglx11files})

	CHECK_CXX_SOURCE_COMPILES("
		#include <X11/Xlib.h>
		#include <X11/extensions/xf86vmode.h>
		int main() {}"
		SGE_HAVE_XF86_VMODE_H)
	
	IF(SGE_HAVE_XF86_VMODE_H)
		FIND_LIBRARY(
			SGE_HAVE_XF86_VMODE
			"Xxf86vm")

		FILE (GLOB sgeopenglxf86files
			xf86/src/*.cpp)
		SET (sgeopenglfiles ${sgeopenglfiles} ${sgeopenglxf86files})
	ENDIF()
ELSEIF (${WIN32})
	FILE (GLOB sgeopenglwglfiles
		wgl/src/*.cpp)
	SET (sgeopenglfiles ${sgeopenglfiles} ${sgeopenglwglfiles})
ENDIF ()

IF (MSVC)
	INCLUDE_DIRECTORIES (${WININCLUDES}/glew/include)
	LINK_DIRECTORIES (${CMAKE_SOURCE_DIR}/${WINLIBS}/glew/lib)
ENDIF ()

ADD_LIBRARY (sgeopengl SHARED ${sgeopenglfiles})
TARGET_LINK_LIBRARIES (sgeopengl sgecore)

IF (${UNIX})
	TARGET_LINK_LIBRARIES (sgeopengl GL GLEW X11)
	IF(SGE_HAVE_XF86_VMODE)
		TARGET_LINK_LIBRARIES(sgeopengl Xxf86vm)
	ENDIF()
ELSEIF (${WIN32})
	TARGET_LINK_LIBRARIES (sgeopengl opengl32 glu32 glew32)
ENDIF ()

INSTALL (TARGETS sgeopengl DESTINATION ${pluginpath})

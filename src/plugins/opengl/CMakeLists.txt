FILE (GLOB sgeopenglfiles
	src/*.cpp
	glsl/src/*.cpp
	vf/src/*.cpp)
	
IF (${SGE_HAVE_X11})
	FILE (GLOB sgeopenglx11files
		glx/src/*.cpp)
	SET (sgeopenglfiles ${sgeopenglfiles} ${sgeopenglx11files})
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
ELSEIF (${WIN32})
	TARGET_LINK_LIBRARIES (sgeopengl opengl32 glu32 glew32)
ENDIF ()

INSTALL (TARGETS sgeopengl DESTINATION ${pluginpath})

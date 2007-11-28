FILE (GLOB sgeopenglfiles src/*.cpp)

ADD_DEFINITIONS (-DSGE_OGL_VERTEX_BUFFER_OBJECT_ARB=1)

ADD_LIBRARY (sgeopengl SHARED ${sgeopenglfiles})
TARGET_LINK_LIBRARIES (sgeopengl sgecore GLEW)

IF (${UNIX})
	TARGET_LINK_LIBRARIES (sgeopengl GL X11 Xxf86vm)
ELSEIF (${WIN32})
	INCLUDE_DIRECTORIES (${WINLIBS}/glew/include)
	LINK_DIRECTORIES (${WINLIBS}/glew/lib)
	TARGET_LINK_LIBRARIES (sgeopengl opengl32)
ENDIF ()

INSTALL (TARGETS sgeopengl DESTINATION ${pluginpath})

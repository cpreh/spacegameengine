FILE (GLOB sgeopenglfiles src/*.cpp)

ADD_DEFINITIONS (-DSGE_OGL_VERTEX_BUFFER_OBJECT_ARB=1)

ADD_LIBRARY (sgeopengl SHARED ${sgeopenglfiles})
TARGET_LINK_LIBRARIES (sgeopengl sgecore GL X11 GLEW Xxf86vm)

INSTALL (TARGETS sgeopengl DESTINATION ${pluginpath})

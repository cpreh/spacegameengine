FILE (GLOB sgeopenglfiles src/*.cpp)

ADD_LIBRARY (sgeopengl SHARED ${sgeopenglfiles})
TARGET_LINK_LIBRARIES (sgeopengl sgecore GL X11 GLEW Xxf86vm)

INSTALL (TARGETS sgeopengl DESTINATION ${pluginpath})

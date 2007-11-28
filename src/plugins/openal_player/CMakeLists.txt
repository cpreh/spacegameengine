FILE (GLOB sgeopenalfiles src/*.cpp)

ADD_LIBRARY (sgeopenal SHARED ${sgeopenalfiles})
TARGET_LINK_LIBRARIES (sgeopenal sgecore openal)

INSTALL (TARGETS sgeopenal DESTINATION ${pluginpath})

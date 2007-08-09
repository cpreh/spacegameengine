FILE (GLOB sgezlibfiles src/*.cpp)

ADD_LIBRARY (sgezlib SHARED ${sgezlibfiles})
TARGET_LINK_LIBRARIES (sgezlib sgecore miniunzip)

INSTALL (TARGETS sgezlib DESTINATION ${pluginpath})

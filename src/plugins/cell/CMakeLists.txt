FILE (GLOB sgecellfiles src/*.cpp)

ADD_LIBRARY (sgecell SHARED ${sgecellfiles})

TARGET_LINK_LIBRARIES (sgecell sgecore)

INSTALL (TARGETS sgecell DESTINATION ${pluginpath})

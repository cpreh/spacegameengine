FILE (GLOB sgefreetypefiles src/*.cpp)

ADD_LIBRARY (sgefreetype SHARED ${sgefreetypefiles})
TARGET_LINK_LIBRARIES (sgefreetype sgecore freetype)
INCLUDE_DIRECTORIES (sgefreetype /usr/include/freetype2)

INSTALL (TARGETS sgefreetype DESTINATION ${pluginpath})

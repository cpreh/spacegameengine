FILE (GLOB sgewavefiles src/*.cpp)

ADD_LIBRARY (sgewave SHARED ${sgewavefiles})
TARGET_LINK_LIBRARIES (sgewave sgecore)

INSTALL (TARGETS sgewave DESTINATION ${pluginpath})

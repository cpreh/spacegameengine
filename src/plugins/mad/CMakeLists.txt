FILE (GLOB sgemadfiles src/*.cpp)

ADD_LIBRARY (sgemad SHARED ${sgemadfiles})

TARGET_LINK_LIBRARIES (sgemad sgecore mad)

INSTALL (TARGETS sgemad DESTINATION ${pluginpath})

FILE (GLOB sgemd3files src/*.cpp)

ADD_LIBRARY (sgemd3 SHARED ${sgemd3files})

TARGET_LINK_LIBRARIES (sgemd3 sgecore)

INSTALL (TARGETS sgemd3 DESTINATION ${pluginpath})

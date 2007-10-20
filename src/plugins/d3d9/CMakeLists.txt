FILE (GLOB sged3d9files src/*.cpp)

ADD_LIBRARY (sged3d9 SHARED ${sged3d9files})
TARGET_LINK_LIBRARIES (sged3d9 sgecore D3D9)

INSTALL (TARGETS sged3d9 DESTINATION ${pluginpath})

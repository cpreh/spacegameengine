FILE (GLOB sgedevilfiles src/*.cpp)

ADD_LIBRARY (sgedevil SHARED ${sgedevilfiles})
TARGET_LINK_LIBRARIES (sgedevil sgecore IL ILU)

INSTALL (TARGETS sgedevil DESTINATION ${pluginpath})

FILE (GLOB sgeaudionullfiles src/*.cpp)

ADD_LIBRARY (sgeaudionull SHARED ${sgeaudionullfiles})

TARGET_LINK_LIBRARIES (sgeaudionull sgecore)

INSTALL (TARGETS sgeaudionull DESTINATION ${pluginpath})

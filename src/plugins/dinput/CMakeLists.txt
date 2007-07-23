FILE (GLOB sgedinputfiles src/*.cpp)

ADD_LIBRARY (sgedinput SHARED ${sgedinputfiles})
TARGET_LINK_LIBRARIES (sgedinput dinput8 boost_signals dxguid sgecore)

INSTALL (TARGETS sgedinput DESTINATION ${pluginpath})

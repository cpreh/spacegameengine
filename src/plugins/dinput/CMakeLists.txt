FILE (GLOB sgedinputfiles src/*.cpp)

ADD_LIBRARY (sgedinput SHARED ${sgedinputfiles})
TARGET_LINK_LIBRARIES (sgedinput dinput8 dxguid sgecore)

IF (NOT ${MSVC})
	TARGET_LINK_LIBRARIES (sgedinput boost_signals)
ENDIF ()

INSTALL (TARGETS sgedinput DESTINATION ${pluginpath})

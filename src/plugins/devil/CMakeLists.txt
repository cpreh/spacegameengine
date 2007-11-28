FILE (GLOB sgedevilfiles src/*.cpp)

ADD_LIBRARY (sgedevil SHARED ${sgedevilfiles})

IF (${UNIX})
	TARGET_LINK_LIBRARIES (sgedevil sgecore IL ILU)
ELSEIF (${WIN32})
	TARGET_LINK_LIBRARIES (sgedevil sgecore DevIL ILU)
	INCLUDE_DIRECTORIES (${WINLIBS}/DevIL/include)
	LINK_DIRECTORIES (${WINLIBS}/DevIL/lib)
ENDIF ()

INSTALL (TARGETS sgedevil DESTINATION ${pluginpath})

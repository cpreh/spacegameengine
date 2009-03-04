FILE (GLOB sgeodefiles src/*.cpp src/objects/*.cpp)

IF (MSVC)
	INCLUDE_DIRECTORIES (${WININCLUDES}/libode/include)
	LINK_DIRECTORIES (${CMAKE_SOURCE_DIR}/${WINLIBS}/libode/lib)
ELSE ()
	INCLUDE_DIRECTORIES(${ODE_INCLUDE_DIR})
ENDIF ()

ADD_LIBRARY (sgeode SHARED ${sgeodefiles})

TARGET_LINK_LIBRARIES (sgeode sgecore ${ODE_LIBRARY})

INSTALL (TARGETS sgeode DESTINATION ${pluginpath})

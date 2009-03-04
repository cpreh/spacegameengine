FILE (GLOB sgeodefiles src/*.cpp src/objects/*.cpp)

IF (MSVC)
	INCLUDE_DIRECTORIES (${WININCLUDES}/libode/include)
	LINK_DIRECTORIES (${CMAKE_SOURCE_DIR}/${WINLIBS}/libode/lib)
ELSE ()
	FIND_PACKAGE(ODE ode)
	INCLUDE_DIRECTORIES(${ODE_INCLUDE_DIRS})
ENDIF ()

ADD_LIBRARY (sgeode SHARED ${sgeodefiles})

TARGET_LINK_LIBRARIES (sgeode sgecore ${ODE_LDFLAGS})

INSTALL (TARGETS sgeode DESTINATION ${pluginpath})

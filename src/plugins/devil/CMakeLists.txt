FILE (GLOB_RECURSE sgedevilfiles src/*.cpp)

IF (MSVC)
	INCLUDE_DIRECTORIES (${WININCLUDES}/devil/include)
	LINK_DIRECTORIES (${CMAKE_SOURCE_DIR}/${WINLIBS}/devil/lib)
ENDIF ()

ADD_LIBRARY (sgedevil SHARED ${sgedevilfiles})

IF (${UNIX})
	TARGET_LINK_LIBRARIES (sgedevil sgecore IL ILU)
ELSEIF (${WIN32})
	TARGET_LINK_LIBRARIES (sgedevil sgecore DevIL ILU)
ENDIF ()

INSTALL (TARGETS sgedevil DESTINATION lib/sge)

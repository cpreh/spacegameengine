FILE (GLOB miniunzipfiles miniunz.c unzip.c ioapi.c)

IF (MSVC)
	INCLUDE_DIRECTORIES (${WININCLUDES}/zlib/include)
	LINK_DIRECTORIES (${CMAKE_SOURCE_DIR}/${WINLIBS}/zlib/lib)
ENDIF ()

ADD_LIBRARY (miniunzip SHARED ${miniunzipfiles})
IF (MSVC)
	TARGET_LINK_LIBRARIES (miniunzip zdll.lib)
ELSE ()
	TARGET_LINK_LIBRARIES (miniunzip z)
ENDIF ()

INSTALL (TARGETS miniunzip DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

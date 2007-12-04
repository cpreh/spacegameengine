FILE (GLOB miniunzipfiles miniunz.c unzip.c ioapi.c)

IF (MSVC)
	INCLUDE_DIRECTORIES (${WININCLUDES}/zlib/include)
	LINK_DIRECTORIES (${CMAKE_SOURCE_DIR}/${WINLIBS}/zlib/lib)
ENDIF ()

ADD_LIBRARY (miniunzip SHARED ${miniunzipfiles})
TARGET_LINK_LIBRARIES (miniunzip z)
INSTALL (TARGETS miniunzip DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

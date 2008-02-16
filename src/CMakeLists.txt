FILE (GLOB sgecorefiles 
	src/*.cpp
	archive/src/*.cpp
	audio/src/*.cpp
	audio/audio_loader/src/*.cpp
	audio/audio_player/src/*.cpp
	console/src/*.cpp
	detail/src/*.cpp
	font/src/*.cpp
	image/src/*.cpp
	input/src/*.cpp
	model/src/*.cpp
	renderer/src/*.cpp
	sprite/src/*.cpp
	texture/src/*.cpp)

ADD_DEFINITIONS (-DPLUGIN_PATH="\\\"${pluginpath}\\\"" -DMEDIA_PATH="\\\"${media_dest}\\\"" -DSGE_NARROW_STRING)

IF (MSVC)
	INCLUDE_DIRECTORIES (${WININCLUDES}/libiconv/include)
	LINK_DIRECTORIES (${CMAKE_SOURCE_DIR}/${WINLIBS}/libiconv/lib)
ENDIF ()

ADD_LIBRARY (sgecore SHARED ${sgecorefiles})

SET_TARGET_PROPERTIES (sgecore PROPERTIES DEFINE_SYMBOL SGE_EXPORTS)

IF (NOT MSVC)
	TARGET_LINK_LIBRARIES (sgecore boost_filesystem boost_signals boost_regex)
ENDIF ()

IF (${UNIX})
	TARGET_LINK_LIBRARIES (sgecore X11 dl)
ELSEIF (${WIN32})
	TARGET_LINK_LIBRARIES (sgecore gdi32 kernel32 user32 iconv)
ENDIF ()

INSTALL (TARGETS sgecore DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

MACRO (INSTALL_HEADERS subpath)
	FILE (GLOB sgeheaders ${subpath}/*.hpp)
	INSTALL (FILES ${sgeheaders} DESTINATION ${include_dest}${subpath})
ENDMACRO ()

INSTALL_HEADERS (./)
INSTALL_HEADERS (archive)
INSTALL_HEADERS (audio)
INSTALL_HEADERS (audio/audio_loader)
INSTALL_HEADERS (audio/audio_player)
INSTALL_HEADERS (console)
INSTALL_HEADERS (detail)
INSTALL_HEADERS (font)
INSTALL_HEADERS (image)
INSTALL_HEADERS (input)
INSTALL_HEADERS (math)
INSTALL_HEADERS (renderer)
INSTALL_HEADERS (sprite)
INSTALL_HEADERS (texture)

IF (${ENABLE_GUI})
	ADD_SUBDIRECTORY (gui)
	INSTALL_HEADERS (gui)
ENDIF ()

ADD_SUBDIRECTORY (plugins)

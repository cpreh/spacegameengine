FILE (GLOB sgecorefiles src/*.cpp console/src/*.cpp detail/src/*.cpp
	image/src/*.cpp input/src/*.cpp renderer/src/*.cpp sprite/src/*.cpp
	texture/src/*.cpp model/src/*.cpp)
ADD_DEFINITIONS (-DPLUGIN_PATH="\\\"${pluginpath}\\\"" -DMEDIA_PATH="\\\"${media_dest}\\\"")

ADD_LIBRARY (sgecore SHARED ${sgecorefiles})
IF (NOT ${MSVC})
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

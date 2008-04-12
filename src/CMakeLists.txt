FILE (GLOB sgecorefiles 
	*.cpp
	archive/*.cpp
	audio/*.cpp
	audio/audio_loader/*.cpp
	audio/audio_player/*.cpp
	console/*.cpp
	font/*.cpp
	image/*.cpp
	input/*.cpp
	math/*.cpp
	model/*.cpp
	renderer/*.cpp
	sprite/*.cpp
	texture/*.cpp)

ADD_DEFINITIONS (-DPLUGIN_PATH="\\\"${pluginpath}\\\"" -DMEDIA_PATH="\\\"${media_dest}\\\"")

ADD_LIBRARY (sgecore SHARED ${sgecorefiles})

SET_TARGET_PROPERTIES (sgecore PROPERTIES DEFINE_SYMBOL SGE_EXPORTS)

IF (NOT MSVC)
	TARGET_LINK_LIBRARIES (sgecore boost_filesystem boost_signals boost_regex)
ENDIF ()

IF (${UNIX})
	TARGET_LINK_LIBRARIES (sgecore X11 dl)
ELSEIF (${WIN32})
	TARGET_LINK_LIBRARIES (sgecore gdi32 kernel32 user32)
ENDIF ()

INSTALL (TARGETS sgecore DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

MACRO (INSTALL_HEADERS subpath)
	FILE (GLOB sgeheaders ${subpath}/*.h*)
	INSTALL (FILES ${sgeheaders} DESTINATION ${include_dest}${subpath})
ENDMACRO ()

IF (${ENABLE_GUI})
	ADD_SUBDIRECTORY (gui)
	INSTALL_HEADERS (gui)
ENDIF ()

ADD_SUBDIRECTORY (plugins)

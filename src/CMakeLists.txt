FILE (GLOB sgecorefiles 
	*.cpp
	archive/*.cpp
	audio/*.cpp
	console/*.cpp
	font/*.cpp
	image/*.cpp
	input/*.cpp
	log/*.cpp
	log/format/*.cpp
	math/*.cpp
	model/*.cpp
	plugin/*.cpp
	renderer/*.cpp
	renderer/glsl/*.cpp
	renderer/state/*.cpp
	renderer/vf/*.cpp
	sprite/*.cpp
	systems/*.cpp
	texture/*.cpp
	time/*.cpp)

IF (${SGE_HAVE_X11})
	FILE (GLOB sgecorex11files
		x11/*.cpp)
	SET (sgecorefiles ${sgecorefiles} ${sgecorex11files})
ELSEIF (${WIN32})
	FILE (GLOB sgecorewindowsfiles
		windows/*.cpp)
	SET (sgecorefiles ${sgecorefiles} ${sgecorewindowsfiles})
ENDIF ()

ADD_DEFINITIONS (-DPLUGIN_PATH="\\\"${pluginpath}\\\"" -DMEDIA_PATH="\\\"${media_dest}\\\"")

ADD_LIBRARY (sgecore SHARED ${sgecorefiles})

SET_TARGET_PROPERTIES (sgecore PROPERTIES DEFINE_SYMBOL SGE_EXPORTS)

IF (NOT MSVC)
	TARGET_LINK_LIBRARIES (sgecore boost_filesystem boost_signals boost_regex
  boost_iostreams boost_system)
ENDIF ()

IF (${UNIX})
	TARGET_LINK_LIBRARIES (sgecore X11 Xxf86vm dl rt)
ELSEIF (${WIN32})
	TARGET_LINK_LIBRARIES (sgecore gdi32 kernel32 user32)
ENDIF ()

INSTALL (TARGETS sgecore DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

IF (${ENABLE_GUI})
	ADD_SUBDIRECTORY (gui)
ENDIF ()

ADD_SUBDIRECTORY (plugins)

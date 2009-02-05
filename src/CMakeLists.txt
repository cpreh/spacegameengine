FILE (GLOB sgecorefiles 
	*.cpp
	archive/*.cpp
	audio/*.cpp
	console/*.cpp
	console/detail/*.cpp
	collision/*.cpp
	collision/objects/*.cpp
	container/*.cpp
	filesystem/*.cpp
	font/*.cpp
	image/*.cpp
	input/*.cpp
	input/modifier/*.cpp
	library/*.cpp
	log/*.cpp
	log/format/*.cpp
	mainloop/*.cpp
	model/*.cpp
	plugin/*.cpp
	plugin/detail/*.cpp
	random/*.cpp
	renderer/*.cpp
	renderer/glsl/*.cpp
	renderer/glsl/uniform/*.cpp
	renderer/state/*.cpp
	renderer/vf/*.cpp
	signals/*.cpp
	sprite/*.cpp
	sprite/detail/*.cpp
	systems/*.cpp
	texture/*.cpp
	texture/detail/*.cpp
	time/*.cpp
	window/*.cpp)

IF (X11_FOUND)
	FILE (GLOB sgecorex11files
		x11/*.cpp)
	SET (sgecorefiles ${sgecorefiles} ${sgecorex11files})
ELSEIF (WIN32)
	FILE (GLOB sgecorewindowsfiles
		windows/*.cpp)
	SET (sgecorefiles ${sgecorefiles} ${sgecorewindowsfiles})
ENDIF ()

IF (HAVE_LESS_THAN_CMAKE_2_6)
	ADD_DEFINITIONS (-DPLUGIN_PATH="\\\"${pluginpath}\\\"" -DMEDIA_PATH="\\\"${media_dest}\\\"")
ELSE ()
	ADD_DEFINITIONS (-DPLUGIN_PATH="${pluginpath}" -DMEDIA_PATH="${media_dest}")
ENDIF ()

ADD_LIBRARY (sgecore SHARED ${sgecorefiles})

SET_TARGET_PROPERTIES (sgecore PROPERTIES DEFINE_SYMBOL SGE_EXPORTS)

IF (NOT MSVC)
	TARGET_LINK_LIBRARIES (
		sgecore
		${Boost_LIBRARIES}
	)
ENDIF ()

IF (UNIX)
	TARGET_LINK_LIBRARIES (sgecore ${X11_LIBRARIES} dl rt)

#also link sgecore against Xxf86dga
#otherwise XCloseDisplay will segfault on shutdown
#if the plugin using Xxf86dga has been unloaded already
	IF(ENABLE_DGA AND HAVE_XF86_DGA)
		TARGET_LINK_LIBRARIES (sgecore Xxf86dga)
	ENDIF()
ELSEIF (WIN32)
	TARGET_LINK_LIBRARIES (sgecore gdi32 kernel32 user32)
ENDIF ()

INSTALL (TARGETS sgecore DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

OPTION (ENABLE_GUI "Build the gui" OFF)

IF (ENABLE_GUI)
	ADD_SUBDIRECTORY (gui)
ENDIF ()

ADD_SUBDIRECTORY (plugins)

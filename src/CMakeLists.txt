FILE (GLOB sgecorefiles 
	*.cpp
	algorithm/*.cpp
	audio/*.cpp
	config/*.cpp
	console/*.cpp
	console/detail/*.cpp
	collision/*.cpp
	collision/objects/*.cpp
	config/detail/*.cpp
	container/*.cpp
	endianness/*.cpp
	filesystem/*.cpp
	font/*.cpp
	image/*.cpp
	input/*.cpp
	input/modifier/*.cpp
	io/*.cpp
	library/*.cpp
	log/*.cpp
	log/format/*.cpp
	mainloop/*.cpp
	model/*.cpp
	parse/ini/*.cpp
	parse/json/*.cpp
	plugin/*.cpp
	plugin/detail/*.cpp
	random/*.cpp
	renderer/*.cpp
	renderer/detail/*.cpp
	renderer/filter/*.cpp
	renderer/index/*.cpp
	renderer/glsl/*.cpp
	renderer/glsl/attribute/*.cpp
	renderer/glsl/uniform/*.cpp
	renderer/state/*.cpp
	renderer/vf/*.cpp
	signal/*.cpp
	signal/detail/*.cpp
	sprite/*.cpp
	sprite/detail/*.cpp
	sprite/intrusive/*.cpp
	sprite/intrusive/detail/*.cpp
	systems/*.cpp
	texture/*.cpp
	texture/detail/*.cpp
	time/*.cpp
	utf8/*.cpp
	variant/*.cpp
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

set_source_files_properties(
	config/plugin_path.cpp
	PROPERTIES
	COMPILE_FLAGS
	-DPLUGIN_PATH="\\\"${pluginpath}\\\"")
set_source_files_properties(
	config/media_path.cpp
	PROPERTIES
	COMPILE_FLAGS
	-DMEDIA_PATH="\\\"${media_dest}\\\"")

ADD_LIBRARY (sgecore SHARED ${sgecorefiles})

IF (NOT MSVC)
	TARGET_LINK_LIBRARIES (
		sgecore
		${Boost_LIBRARIES}
	)
ENDIF ()

IF (UNIX)
	TARGET_LINK_LIBRARIES (sgecore ${X11_LIBRARIES} dl)

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

OPTION (ENABLE_GUI "Build the gui" ON)

IF (ENABLE_GUI)
	ADD_SUBDIRECTORY (gui)
ENDIF ()

ADD_SUBDIRECTORY (plugins)

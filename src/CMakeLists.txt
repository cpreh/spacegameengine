FILE (GLOB sgecorefiles 
	*.cpp
	algorithm/*.cpp
	audio/*.cpp
	chrono/*.cpp
	config/*.cpp
	console/*.cpp
	collision/*.cpp
	collision/shapes/*.cpp
	config/detail/*.cpp
	container/*.cpp
	endianness/*.cpp
	error/*.cpp
	filesystem/*.cpp
	font/*.cpp
	image/*.cpp
	image/algorithm/*.cpp
	image/color/*.cpp
	image/color/any/*.cpp
	image/view/*.cpp
	input/*.cpp
	input/modifier/*.cpp
	library/*.cpp
	log/*.cpp
	log/detail/*.cpp
	log/format/*.cpp
	log/parameters/*.cpp
	mainloop/*.cpp
	mainloop/asio/*.cpp
	math/*.cpp
	model/*.cpp
	mpl/*.cpp
	parse/*.cpp
	parse/output/*.cpp
	parse/ini/*.cpp
	parse/ini/output/*.cpp
	parse/json/*.cpp
	parse/json/output/*.cpp
	plugin/*.cpp
	plugin/detail/*.cpp
	random/*.cpp
	random/actor/*.cpp
	renderer/*.cpp
	renderer/detail/*.cpp
	renderer/filter/*.cpp
	renderer/index/*.cpp
	renderer/index/dynamic/*.cpp
	renderer/glsl/*.cpp
	renderer/glsl/attribute/*.cpp
	renderer/glsl/uniform/*.cpp
	renderer/state/*.cpp
	renderer/vf/dynamic/*.cpp
	signal/*.cpp
	signal/detail/*.cpp
	sprite/*.cpp
	sprite/animation/*.cpp
	sprite/detail/*.cpp
	systems/*.cpp
	texture/*.cpp
	texture/atlasing/*.cpp
	texture/detail/*.cpp
	thread/*.cpp
	thread/future/*.cpp
	thread/future/detail/*.cpp
	time/*.cpp
	utf8/*.cpp
	variant/*.cpp
	window/*.cpp
)

FILE (GLOB_RECURSE sgecoreheaders
	../include/*.hpp)

SET (sgecorefiles ${sgecorefiles} ${sgecoreheaders})

IF (X11_FOUND)
	FILE (GLOB sgecorex11files
		x11/*.cpp)
	SET (sgecorefiles ${sgecorefiles} ${sgecorex11files})
ELSEIF (WIN32)
	FILE (GLOB sgecorewindowsfiles
		windows/*.cpp
		windows/detail/*.cpp)
	SET (sgecorefiles ${sgecorefiles} ${sgecorewindowsfiles})
ENDIF ()

set_source_files_properties(
	config/plugin_path.cpp
	PROPERTIES
	COMPILE_FLAGS
	-DPLUGIN_PATH="\\\"${CMAKE_INSTALL_PREFIX}/lib/sge\\\"")
set_source_files_properties(
	config/media_path.cpp
	PROPERTIES
	COMPILE_FLAGS
	-DMEDIA_PATH="\\\"${CMAKE_INSTALL_PREFIX}/share/games/sge/media\\\"")

ADD_LIBRARY (sgecore SHARED ${sgecorefiles})

TARGET_LINK_LIBRARIES (sgecore fcppt)

IF (NOT MSVC)
	TARGET_LINK_LIBRARIES (
		sgecore
		${Boost_LIBRARIES}
	)
ENDIF ()

IF (UNIX)
	TARGET_LINK_LIBRARIES (sgecore ${X11_X11_LIB} dl)

	#also link sgecore against Xxf86dga
	#otherwise XCloseDisplay will segfault on shutdown
	#if the plugin using Xxf86dga has been unloaded already


	CHECK_CXX_SOURCE_COMPILES("
			#include <X11/Xlib.h>
			#include <X11/extensions/Xxf86dga.h>
			int main() {}"
			HAVE_XF86_DGA_H
		)
	
		IF (HAVE_XF86_DGA_H)
			FIND_LIBRARY(
				HAVE_XF86_DGA
				"Xxf86dga")
		ENDIF()

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

OPTION (ENABLE_XCB "Build the xcb bindings" ON)

# TODO: add a search script for xcb!

IF (ENABLE_XCB)
	ADD_SUBDIRECTORY (xcb)
ENDIF ()

FILE (
	GLOB SGECOREFILES 
	*.cpp
	audio/*.cpp
	audio/sound/*.cpp
	collision/*.cpp
	collision/shapes/*.cpp
	config/*.cpp
	config/detail/*.cpp
	console/*.cpp
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
	mainloop/*.cpp
	mainloop/asio/*.cpp
	model/*.cpp
	parse/*.cpp
	parse/output/*.cpp
	parse/ini/*.cpp
	parse/ini/output/*.cpp
	parse/json/*.cpp
	parse/json/output/*.cpp
	plugin/*.cpp
	plugin/detail/*.cpp
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
	sprite/*.cpp
	sprite/animation/*.cpp
	sprite/detail/*.cpp
	systems/*.cpp
	texture/*.cpp
	texture/atlasing/*.cpp
	texture/detail/*.cpp
	time/*.cpp
	window/*.cpp
)

FILE (
	GLOB_RECURSE sgecoreheaders
	../include/*.hpp
)

SET (SGECOREFILES ${SGECOREFILES} ${sgecoreheaders})

IF (X11_FOUND)
	FILE (
		GLOB sgecorex11files
		x11/*.cpp
	)

	SET (SGECOREFILES ${SGECOREFILES} ${sgecorex11files})
ELSEIF (WIN32)
	FILE (
		GLOB sgecorewindowsfiles
		windows/*.cpp
		windows/detail/*.cpp
	)

	SET (SGECOREFILES ${SGECOREFILES} ${sgecorewindowsfiles})
ENDIF ()

set_source_files_properties(
	config/plugin_path.cpp
	PROPERTIES
	COMPILE_FLAGS
	-DPLUGIN_PATH="\\\"${CMAKE_INSTALL_PREFIX}/lib/sge\\\""
)

set_source_files_properties(
	config/media_path.cpp
	PROPERTIES
	COMPILE_FLAGS
	-DMEDIA_PATH="\\\"${CMAKE_INSTALL_PREFIX}/share/games/sge/media\\\""
)

ADD_LIBRARY (sgecore SHARED ${SGECOREFILES})

TARGET_LINK_LIBRARIES (sgecore ${FCPPT_LIBRARIES})

IF (NOT MSVC)
	TARGET_LINK_LIBRARIES (
		sgecore
		${Boost_LIBRARIES}
	)
ENDIF ()

IF (UNIX)
	TARGET_LINK_LIBRARIES (sgecore ${X11_X11_LIB} dl)
ELSEIF (WIN32)
	TARGET_LINK_LIBRARIES (sgecore gdi32 kernel32 user32)
ENDIF ()

INSTALL (TARGETS sgecore DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

OPTION (ENABLE_GUI "Build the gui" ON)

IF (ENABLE_GUI)
	ADD_SUBDIRECTORY (gui)
ENDIF ()

ADD_SUBDIRECTORY (plugins)

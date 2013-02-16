set(
	SGE_CORE_INCLUDE_FILES
	include/sge/class_symbol.hpp
	include/sge/error/check_state.hpp
	include/sge/exception.hpp
)

set(
	SGE_CORE_SRC_FILES
	src/exception.cpp
	src/include/sge/src/export_class_instantiation.hpp
	src/include/sge/src/export_function_instantiation.hpp
	src/include/sge/src/include_windows.hpp
)

foreach(
	CUR_FILE
	${SGE_CORE_INCLUDE_FILES}
)
	get_filename_component(
		REL_PATH
		${CUR_FILE}
		PATH
	)

	string(
		REPLACE
		"include/"
		""
		TRIMMED_PATH
		"${REL_PATH}"
	)

	install(
		FILES
		${CMAKE_SOURCE_DIR}/${CUR_FILE}
		DESTINATION
		${INSTALL_INCLUDE_DIR}/${TRIMMED_PATH}
	)
endforeach()

install(
	DIRECTORY
	${CMAKE_SOURCE_DIR}/include/majutsu
	DESTINATION
	${INSTALL_INCLUDE_DIR}
)

install(
	FILES
	${CMAKE_BINARY_DIR}/include/sge/symbol.hpp
	DESTINATION
	${INSTALL_INCLUDE_DIR}/sge
)

# configure some resource paths
set(
	SGE_PLUGIN_BUILD_PATH
	"${LIBRARY_OUTPUT_PATH}/plugins"
)

set(
	SGE_PLUGIN_INSTALL_PATH
	"${PLUGIN_INSTALL_DIR}"
)

set(
	SGE_MEDIA_BUILD_PATH
	"${CMAKE_SOURCE_DIR}/media"
)

set(
	SGE_MEDIA_INSTALL_PATH
	"${MEDIA_INSTALL_DIR}"
)

include_directories(
	"${CMAKE_CURRENT_SOURCE_DIR}/include"
)

sge_generate_symbol_header(
	"sgecore"
	"SGE"
	"sge"
)


fcppt_utils_append_source_dir_and_make_groups(
	"${SGE_CORE_INCLUDE_FILES}"
	SGE_CORE_INCLUDE_FILES_ABS
)

fcppt_utils_append_source_dir_and_make_groups(
	"${SGE_CORE_SRC_FILES}"
	SGE_CORE_SRC_FILES_ABS
)

if(
	ENABLE_STATIC
)
	add_sge_core_lib(
		"STATIC"
	)
endif()

if(
	ENABLE_SHARED
)
	add_sge_core_lib(
		"SHARED"
	)
endif()

# core libraries
OPTION (ENABLE_AUDIO "Build the audio library" ON)
OPTION (ENABLE_CHARCONV "Build the charconv library" ON)
OPTION (ENABLE_FONT "Build the font library" ON)
OPTION (ENABLE_GRAPH "Build the graph library" ON)
OPTION (ENABLE_IMAGE "Build the image library" ON)
OPTION (ENABLE_IMAGE2D "Build the image2d library" ON)
OPTION (ENABLE_IMAGE3D "Build the image3d library" ON)
OPTION (ENABLE_IMAGECOLOR "Build the imagecolor library" ON)
OPTION (ENABLE_IMAGEDS "Build the image depth stencil library" ON)
OPTION (ENABLE_IMAGEDS2D "Build the image depth stencil 2d library" ON)
OPTION (ENABLE_INPUT "Build the input library" ON)
OPTION (ENABLE_LOG "Build the log base library" ON)
OPTION (ENABLE_MEDIA "Build the media base library" ON)
OPTION (ENABLE_MODELMD3 "Build the md3 model library" ON)
OPTION (ENABLE_MODELOBJ "Build the md3 model library" ON)
OPTION (ENABLE_PLUGIN "Build the plugin library" ON)
OPTION (ENABLE_RENDERER "Build the renderer library" ON)
OPTION (ENABLE_TIMER "Build the timer library" ON)
OPTION (ENABLE_WINDOW "Build the window library" ON)

# more advanced libraries
find_package(
	Bullet
)

find_package(
	CEGUI
)

find_package(
	OpenCL
)

find_package(
	Cg
)

OPTION (ENABLE_CAMERA "Build the camera" ON)
OPTION (ENABLE_CEGUI "Build the cegui subsystem" ${CEGUI_FOUND})
OPTION (ENABLE_CG "Build the Cg library" ${CG_FOUND})
OPTION (ENABLE_CONFIG "Build the config library" ON)
OPTION (ENABLE_CONSOLE "Build the console" ON)
OPTION (ENABLE_FONTBITMAP "Build the bitmap font library" ON)
OPTION (ENABLE_FONTDRAW "Build the font drawing library" ON)
OPTION (ENABLE_LINE_DRAWER "Build the line drawing library" ON)
OPTION (ENABLE_OPENCL "Build the opencl library" ${OPENCL_FOUND})
OPTION (ENABLE_PARSE "Build the parse library" ON)
OPTION (ENABLE_POSTPROCESSING "Build the postprocessing library" ON)
OPTION (ENABLE_PROJECTILE "Build the projectile library" ${BULLET_FOUND})
OPTION (ENABLE_RESOURCE_TREE "Build the resource tree library" ON)
OPTION (ENABLE_RUCKSACK "Build the rucksack library" ON)
OPTION (ENABLE_SCENIC "Build the scenic library" ON)
OPTION (ENABLE_SHADER "Build the shader wrapper library" ON)
OPTION (ENABLE_SPRITE "Build the sprite library" ON)
OPTION (ENABLE_SYSTEMS "Build the systems library" ON)
OPTION (ENABLE_TEXTURE "Build the texture helpers" ON)
OPTION (ENABLE_VIEWPORT "Build the viewport library" ON)

ADD_SUBDIRECTORY(bvh)

IF (ENABLE_AUDIO)
	ADD_SUBDIRECTORY(audio)
ENDIF ()

IF (ENABLE_CHARCONV)
	ADD_SUBDIRECTORY(charconv)
ENDIF ()

IF (ENABLE_FONT)
	ADD_SUBDIRECTORY(font)
ENDIF ()

IF (ENABLE_GRAPH)
	ADD_SUBDIRECTORY(graph)
ENDIF ()

IF (ENABLE_IMAGE)
	ADD_SUBDIRECTORY(image)
ENDIF ()

IF (ENABLE_IMAGE2D)
	ADD_SUBDIRECTORY(image2d)
ENDIF ()

IF (ENABLE_IMAGE3D)
	ADD_SUBDIRECTORY(image3d)
ENDIF ()

IF (ENABLE_IMAGECOLOR)
	ADD_SUBDIRECTORY(image/color)
ENDIF ()

IF (ENABLE_IMAGEDS)
	ADD_SUBDIRECTORY(image/ds)
ENDIF ()

IF (ENABLE_IMAGE2D)
	ADD_SUBDIRECTORY(imageds2d)
ENDIF ()

IF (ENABLE_INPUT)
	ADD_SUBDIRECTORY(input)
ENDIF ()

IF (ENABLE_LOG)
	ADD_SUBDIRECTORY(log)
ENDIF ()

IF (ENABLE_MEDIA)
	ADD_SUBDIRECTORY(media)
ENDIF ()

IF (ENABLE_MODELMD3)
	ADD_SUBDIRECTORY(model/md3)
ENDIF ()

IF (ENABLE_MODELOBJ)
	ADD_SUBDIRECTORY(model/obj)
ENDIF ()

IF (ENABLE_PLUGIN)
	ADD_SUBDIRECTORY(plugin)
ENDIF ()

IF (ENABLE_RENDERER)
	ADD_SUBDIRECTORY(renderer)
ENDIF ()

IF (ENABLE_RESOURCE_TREE)
	ADD_SUBDIRECTORY(resource_tree)
ENDIF ()

IF (ENABLE_RUCKSACK)
	ADD_SUBDIRECTORY(rucksack)
ENDIF ()


IF (ENABLE_TIMER)
	ADD_SUBDIRECTORY(timer)
ENDIF ()

IF (ENABLE_WINDOW)
	ADD_SUBDIRECTORY(window)
ENDIF ()

#enable advanced libraries

IF (ENABLE_CEGUI)
	ADD_SUBDIRECTORY(cegui)
ENDIF ()

IF (ENABLE_CAMERA)
	ADD_SUBDIRECTORY(camera)
ENDIF ()

IF (ENABLE_CG)
	ADD_SUBDIRECTORY(cg)
ENDIF ()

IF (ENABLE_CONFIG)
	ADD_SUBDIRECTORY (config)
ENDIF ()

IF (ENABLE_CONSOLE)
	ADD_SUBDIRECTORY (console)
ENDIF ()

IF(ENABLE_FONTBITMAP)
	ADD_SUBDIRECTORY (font/bitmap)
ENDIF()

IF(ENABLE_FONTDRAW)
	ADD_SUBDIRECTORY (font/draw)
ENDIF()

IF (ENABLE_LINE_DRAWER)
	ADD_SUBDIRECTORY(line_drawer)
ENDIF ()

IF (ENABLE_OPENCL)
	ADD_SUBDIRECTORY (opencl)
ENDIF ()

IF (ENABLE_PARSE)
	ADD_SUBDIRECTORY (parse)
ENDIF ()

IF (ENABLE_POSTPROCESSING)
	ADD_SUBDIRECTORY(postprocessing)
ENDIF ()

IF (ENABLE_PROJECTILE)
	ADD_SUBDIRECTORY (projectile)
ENDIF ()

IF (ENABLE_SCENIC)
	ADD_SUBDIRECTORY(scenic)
ENDIF ()

IF (ENABLE_SHADER)
	ADD_SUBDIRECTORY(shader)
ENDIF ()

IF (ENABLE_SPRITE)
	ADD_SUBDIRECTORY(sprite)
ENDIF ()

IF (ENABLE_SYSTEMS)
	ADD_SUBDIRECTORY(systems)
ENDIF ()

IF (ENABLE_TEXTURE)
	ADD_SUBDIRECTORY(texture)
ENDIF ()

IF (ENABLE_VIEWPORT)
	ADD_SUBDIRECTORY(viewport)
ENDIF ()

add_subdirectory (plugins)

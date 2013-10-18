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
		${FCPPT_UTILS_PROJECT_SOURCE_DIR}/${CUR_FILE}
		DESTINATION
		${INSTALL_INCLUDE_DIR}/${TRIMMED_PATH}
	)
endforeach()

install(
	FILES
	${FCPPT_UTILS_PROJECT_BINARY_DIR}/include/sge/symbol.hpp
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
	"${FCPPT_UTILS_PROJECT_SOURCE_DIR}/media"
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
OPTION (ENABLE_IMAGEDS "Build the image depth stencil library" ON)
OPTION (ENABLE_IMAGEDS2D "Build the image depth stencil 2d library" ON)
OPTION (ENABLE_INPUT "Build the input library" ON)
OPTION (ENABLE_MODELMD3 "Build the md3 model library" ON)
OPTION (ENABLE_MODELOBJ "Build the md3 model library" ON)
OPTION (ENABLE_TIMER "Build the timer library" ON)

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

macro(
	add_sge_lib
	LIBNAME
	DESCRIPTION
	DEFAULT
)
	string(
		TOUPPER
		"${LIBNAME}"
		UPPER_RESULT
	)

	set(
		ENABLE_VAR
		ENABLE_${UPPER_RESULT}
	)

	option(
		${ENABLE_VAR}
		"${DESCRIPTION}"
		${DEFAULT}
	)

	if(
		${ENABLE_VAR}
	)
		add_subdirectory(
			${LIBNAME}
		)
	endif()

	unset(
		UPPER_RESULT
	)

	unset(
		ENABLE_VAR
	)
endmacro()

add_sge_lib(
	log
	"Build the log base library"
	ON
)

add_sge_lib(
	media
	"Build the media base library"
	ON
)

add_sge_lib(
	plugin
	"Build the plugin library"
	ON
)

add_sge_lib(
	image
	"Build the image library"
	ON
)

# TODO: Fix the macro to include these!
option(
	ENABLE_IMAGECOLOR
	"Build the imagecolor library"
	ON
)

if(
	ENABLE_IMAGECOLOR
)
	add_subdirectory(
		image/color
	)
endif()

add_sge_lib(
	image2d
	"Build the image2d library"
	ON
)

add_sge_lib(
	image3d
	"Build the image3d library"
	ON
)

add_sge_lib(
	window
	"Build the window library"
	ON
)

add_sge_lib(
	cg
	"Build the Cg library"
	${CG_FOUND}
)

add_sge_lib(
	renderer
	"Build the renderer library"
	ON
)

add_sge_lib(
	texture
	"Build the texture helpers"
	ON
)

add_sge_lib(
	sprite
	"Build the sprite library"
	ON
)

add_sge_lib(
	viewport
	"Build the viewport library"
	ON
)

add_sge_lib(
	graph
	"Build the graph library"
	ON
)

add_sge_lib(
	parse
	"Build the parse library"
	ON
)

add_sge_lib(
	font
	"Build the font library"
	ON
)

option(
	ENABLE_FONTDRAW
	"Build the font drawing library"
	ON
)

if(
	ENABLE_FONTDRAW
)
	add_subdirectory(
		font/draw
	)
endif()

add_sge_lib(
	shader
	"Build the shader wrapper library"
	ON
)

# more advanced libraries
option(
	ENABLE_CAMERA
	"Build the camera"
	ON
)

OPTION (ENABLE_CEGUI "Build the cegui subsystem" ${CEGUI_FOUND})
OPTION (ENABLE_CONFIG "Build the config library" ON)
OPTION (ENABLE_CONSOLE "Build the console" ON)
OPTION (ENABLE_FONTBITMAP "Build the bitmap font library" ON)
OPTION (ENABLE_LINE_DRAWER "Build the line drawing library" ON)
OPTION (ENABLE_OPENCL "Build the opencl library" ${OPENCL_FOUND})
OPTION (ENABLE_POSTPROCESSING "Build the postprocessing library" ON)
OPTION (ENABLE_PROJECTILE "Build the projectile library" ${BULLET_FOUND})
OPTION (ENABLE_RESOURCE_TREE "Build the resource tree library" ON)
OPTION (ENABLE_RUCKSACK "Build the rucksack library" ON)
OPTION (ENABLE_SCENIC "Build the scenic library" ON)
OPTION (ENABLE_SYSTEMS "Build the systems library" ON)

add_subdirectory(
	bvh
)

IF (ENABLE_AUDIO)
	ADD_SUBDIRECTORY(audio)
ENDIF ()

IF (ENABLE_CHARCONV)
	ADD_SUBDIRECTORY(charconv)
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

IF (ENABLE_MODELMD3)
	ADD_SUBDIRECTORY(model/md3)
ENDIF ()

IF (ENABLE_MODELOBJ)
	ADD_SUBDIRECTORY(model/obj)
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

IF (ENABLE_CEGUI)
	ADD_SUBDIRECTORY(cegui)
ENDIF ()

IF (ENABLE_CAMERA)
	ADD_SUBDIRECTORY(camera)
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

IF (ENABLE_LINE_DRAWER)
	ADD_SUBDIRECTORY(line_drawer)
ENDIF ()

IF (ENABLE_OPENCL)
	ADD_SUBDIRECTORY (opencl)
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

IF (ENABLE_SYSTEMS)
	ADD_SUBDIRECTORY(systems)
ENDIF ()

add_subdirectory(
	plugins
)

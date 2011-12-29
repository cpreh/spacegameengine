set(
	SGE_CORE_INCLUDE_FILES
	include/sge/class_symbol.hpp
	include/sge/error/check_state.hpp
	include/sge/error/error.hpp
	include/sge/exception.hpp
	include/sge/log/declare_lib.hpp
	include/sge/log/declare_lib_base.hpp
	include/sge/log/declare_local.hpp
	include/sge/log/default_parameters.hpp
	include/sge/log/global.hpp
	include/sge/log/global_context.hpp
	include/sge/log/location.hpp
	include/sge/log/log.hpp
	include/sge/symbol.hpp
	include/sge/timer/basic.hpp
	include/sge/timer/basic_decl.hpp
	include/sge/timer/basic_fwd.hpp
	include/sge/timer/basic_impl.hpp
	include/sge/timer/clocks/adjustable.hpp
	include/sge/timer/clocks/adjustable_decl.hpp
	include/sge/timer/clocks/adjustable_fwd.hpp
	include/sge/timer/clocks/adjustable_impl.hpp
	include/sge/timer/clocks/clocks.hpp
	include/sge/timer/clocks/delta.hpp
	include/sge/timer/clocks/delta_decl.hpp
	include/sge/timer/clocks/delta_fwd.hpp
	include/sge/timer/clocks/delta_impl.hpp
	include/sge/timer/clocks/detail/stateful_base.hpp
	include/sge/timer/clocks/detail/stateless_base.hpp
	include/sge/timer/clocks/detail/wrapper.hpp
	include/sge/timer/clocks/is_stateful.hpp
	include/sge/timer/clocks/standard.hpp
	include/sge/timer/detail/parameters_base_decl.hpp
	include/sge/timer/detail/parameters_base_impl.hpp
	include/sge/timer/elapsed.hpp
	include/sge/timer/elapsed_and_reset.hpp
	include/sge/timer/elapsed_fractional.hpp
	include/sge/timer/elapsed_fractional_and_reset.hpp
	include/sge/timer/enable_ctor_stateful.hpp
	include/sge/timer/enable_ctor_stateless.hpp
	include/sge/timer/frames_counter.hpp
	include/sge/timer/parameters.hpp
	include/sge/timer/parameters_decl.hpp
	include/sge/timer/parameters_fwd.hpp
	include/sge/timer/parameters_impl.hpp
	include/sge/timer/remaining.hpp
	include/sge/timer/remaining_fractional.hpp
	include/sge/timer/reset_when_expired.hpp
	include/sge/timer/timer.hpp
)

set(
	SGE_CORE_SRC_FILES
	src/exception.cpp
	src/log/default_parameters.cpp
	src/log/global.cpp
	src/log/global_context.cpp
	src/log/location.cpp
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

function(
	check_library_deps
	LIB_NAME
	ADDITONAL_DEPS
)
	foreach(
		DEPENDENCY
		${ADDITONAL_DEPS}
	)
		string(
			REPLACE
			"sge"
			""
			SUFFIX
			${DEPENDENCY}
		)

		string(
			TOUPPER
			${SUFFIX}
			UPPER_SUFFIX
		)

		if(
			NOT ${UPPER_SUFFIX} STREQUAL "CORE"
			AND NOT ENABLE_${UPPER_SUFFIX}
		)
			message(
				FATAL_ERROR
				"For ${LIB_NAME} to work you need to -D ENABLE_${UPPER_SUFFIX}=ON!"
			)
		endif()
	endforeach()
endfunction()

macro(
	path_difference
	OUTPUT
	OUTER_PATH
	INNER_PATH
)
	unset(
		${OUTPUT}
	)

	if(
		${${PATH_DIFFERENCE}}
	)
		unset(
			${PATH_DIFFERENCE}
		)
	endif()

	set(
		TEMP_INNER_PATH
		${INNER_PATH}
	)

	while(
		NOT ${TEMP_INNER_PATH} STREQUAL ${OUTER_PATH}
	)
		get_filename_component(
			PATH_COMPONENT
			${TEMP_INNER_PATH}
			NAME
		)

		set(
			${OUTPUT}
			"${PATH_COMPONENT}/${${OUTPUT}}"
		)

		get_filename_component(
			TEMP_INNER_PATH
			${TEMP_INNER_PATH}
			PATH
		)
	endwhile()
endmacro()

function(
	add_sge_base_library_variant
	SGE_LIB_NAME
	SGE_LIB_FILES
	SGE_DEPS
	ADDITIONAL_DEPS
	VARIANT
)
	if(
		${VARIANT} STREQUAL "STATIC"
	)
		set(
			SGE_LIB_NAME
			"${SGE_LIB_NAME}_static"
		)
	endif()

	add_library(
		${SGE_LIB_NAME}
		${VARIANT}
		${SGE_LIB_FILES}
	)

	transform_sge_link_targets(
		"${SGE_DEPS}"
	)

	target_link_libraries(
		${SGE_LIB_NAME}
		${ADDITIONAL_DEPS}
		${SGELIBS_TARGETS_RESULT}
	)

	install(
		TARGETS
		${SGE_LIB_NAME}
		DESTINATION
		${INSTALL_LIBRARY_DIR}
	)
endfunction()

function(
	add_sge_base_library
	LIB_NAME
	SGE_DEPS
	ADDITIONAL_DEPS
)
	set(
		SGE_LIB_NAME
		sge${LIB_NAME}
	)

	string(
		TOUPPER
		${LIB_NAME}
		UPPER_LIB_NAME
	)

	FCPPT_UTILS_APPEND_SOURCE_DIR_AND_MAKE_GROUPS(
		"${SGE_${UPPER_LIB_NAME}_FILES}"
		SGE_${UPPER_LIB_NAME}_FILES_ABS
	)

	set(
		SGE_LIB_FILES
		${SGE_${UPPER_LIB_NAME}_FILES_ABS}
	)

	if(
		ENABLE_SHARED
	)
		add_sge_base_library_variant(
			${SGE_LIB_NAME}
			"${SGE_LIB_FILES}"
			"${SGE_DEPS}"
			"${ADDITIONAL_DEPS}"
			SHARED
		)
	endif()

	if(
		ENABLE_STATIC
	)
		add_sge_base_library_variant(
			${SGE_LIB_NAME}
			"${SGE_LIB_FILES}"
			"${SGE_DEPS}"
			"${ADDITIONAL_DEPS}"
			STATIC
		)
	endif()

	check_library_deps(
		"${LIB_NAME}"
		"${SGE_DEPS}"
	)

	path_difference(
		LIB_INCLUDE_PATH
		${CMAKE_SOURCE_DIR}/src
		${CMAKE_CURRENT_SOURCE_DIR}
	)

	install(
		DIRECTORY
		${CMAKE_SOURCE_DIR}/include/sge/${LIB_INCLUDE_PATH}
		DESTINATION
		${INSTALL_INCLUDE_DIR}/sge/${LIB_INCLUDE_PATH}
	)
endfunction()

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

function(
	add_sge_core_lib
	VARIANT
)
	set(
		SGE_CORE_FILES
		"${SGE_CORE_INCLUDE_FILES_ABS};${SGE_CORE_SRC_FILES_ABS}"
	)

	add_sge_base_library_variant(
		sgecore
		"${SGE_CORE_FILES}"
		""
		"${Fcppt_core_LIBRARIES}"
		${VARIANT}
	)
endfunction()

FCPPT_UTILS_APPEND_SOURCE_DIR_AND_MAKE_GROUPS(
	"${SGE_CORE_INCLUDE_FILES}"
	SGE_CORE_INCLUDE_FILES_ABS
)

FCPPT_UTILS_APPEND_SOURCE_DIR_AND_MAKE_GROUPS(
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
OPTION (ENABLE_IMAGE "Build the image library" ON)
OPTION (ENABLE_IMAGE2D "Build the image2d library" ON)
OPTION (ENABLE_IMAGE3D "Build the image3d library" ON)
OPTION (ENABLE_INPUT "Build the input library" ON)
OPTION (ENABLE_MEDIA "Build the media base library" ON)
OPTION (ENABLE_MODELMD3 "Build the md3 model library" ON)
OPTION (ENABLE_MODELOBJ "Build the md3 model library" ON)
OPTION (ENABLE_PLUGIN "Build the plugin library" ON)
OPTION (ENABLE_RENDERER "Build the renderer library" ON)
OPTION (ENABLE_WINDOW "Build the window library" ON)

IF (ENABLE_AUDIO)
	ADD_SUBDIRECTORY(audio)
ENDIF ()

IF (ENABLE_CHARCONV)
	ADD_SUBDIRECTORY(charconv)
ENDIF ()

IF (ENABLE_FONT)
	ADD_SUBDIRECTORY(font)
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

IF (ENABLE_INPUT)
	ADD_SUBDIRECTORY(input)
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

IF (ENABLE_WINDOW)
	ADD_SUBDIRECTORY(window)
ENDIF ()

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

OPTION (ENABLE_CAMERA "Build the camera" ON)
OPTION (ENABLE_CEGUI "Build the cegui subsystem" ${CEGUI_FOUND})
OPTION (ENABLE_CONFIG "Build the config library" ON)
OPTION (ENABLE_CONSOLE "Build the console" ON)
OPTION (ENABLE_FONTBITMAP "Build the bitmap font" ON)
OPTION (ENABLE_FONTTEXT "Build the font text library" ON)
OPTION (ENABLE_LINE_DRAWER "Build the line drawing library" ON)
OPTION (ENABLE_OPENCL "Build the opencl subsystem" ${OPENCL_FOUND})
OPTION (ENABLE_PARSE "Build the parse library" ON)
OPTION (ENABLE_PROJECTILE "Build the projectile subsystem" ${BULLET_FOUND})
OPTION (ENABLE_SHADER "Build the shader" ON)
OPTION (ENABLE_SPRITE "Build the sprite library" ON)
OPTION (ENABLE_SYSTEMS "Build the systems library" ON)
OPTION (ENABLE_TEXTURE "Build the texture helpers" ON)
OPTION (ENABLE_VIEWPORT "Build the viewport library" ON)

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

IF (ENABLE_FONTTEXT)
	ADD_SUBDIRECTORY (font/text)
ENDIF ()

IF (ENABLE_LINE_DRAWER)
	ADD_SUBDIRECTORY(line_drawer)
ENDIF ()

IF (ENABLE_OPENCL)
	ADD_SUBDIRECTORY (opencl)
ENDIF ()

IF (ENABLE_PARSE)
	ADD_SUBDIRECTORY (parse)
ENDIF ()

IF (ENABLE_PROJECTILE)
	ADD_SUBDIRECTORY (projectile)
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

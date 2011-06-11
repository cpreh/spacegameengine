SET(
	SGE_CORE_INCLUDE_FILES
	include/sge/all_extensions.hpp
	include/sge/class_symbol.hpp
	include/sge/const_raw_pointer.hpp
	include/sge/const_raw_range.hpp
	include/sge/error/check_state.hpp
	include/sge/error/error.hpp
	include/sge/exception.hpp
	include/sge/extension.hpp
	include/sge/extension_set.hpp
	include/sge/instantiate_symbol.hpp
	include/sge/loaders_exhausted.hpp
	include/sge/log/global.hpp
	include/sge/log/global_context.hpp
	include/sge/log/log.hpp
	include/sge/multi_loader.hpp
	include/sge/multi_loader_fwd.hpp
	include/sge/optional_extension.hpp
	include/sge/symbol.hpp
)

SET(
	SGE_CORE_SRC_FILES
	src/all_extensions.cpp
	src/exception.cpp
	src/instantiate_multi_loader.hpp
	src/loaders_exhausted.cpp
	src/log/global.cpp
	src/log/global_context.cpp
	src/multi_loader_impl.hpp
)

APPEND_SOURCE_DIR_AND_MAKE_GROUPS(
	"${SGE_CORE_INCLUDE_FILES}"
	SGE_CORE_INCLUDE_FILES_ABS
)

APPEND_SOURCE_DIR_AND_MAKE_GROUPS(
	"${SGE_CORE_SRC_FILES}"
	SGE_CORE_SRC_FILES_ABS
)

FOREACH(
	CUR_FILE
	${SGE_CORE_INCLUDE_FILES}
)
	GET_FILENAME_COMPONENT(
		REL_PATH
		${CUR_FILE}
		PATH
	)

	STRING(
		REPLACE
		"include/"
		""
		TRIMMED_PATH
		"${REL_PATH}"
	)

	INSTALL(
		FILES
		${CMAKE_SOURCE_DIR}/${CUR_FILE}
		DESTINATION
		${INSTALL_INCLUDE_DIR}/${TRIMMED_PATH}
	)
ENDFOREACH()

INSTALL(
	DIRECTORY
	${CMAKE_SOURCE_DIR}/include/majutsu
	DESTINATION
	${INSTALL_INCLUDE_DIR}
)

MACRO(
	CHECK_LIBRARY_DEPS
	LIB_NAME
	ADDITONAL_DEPS
)
	FOREACH(
		DEPENDENCY
		${ADDITONAL_DEPS}
	)
		STRING(
			SUBSTRING
			${DEPENDENCY}
			0
			3
			PREFIX
		)

		IF(
			PREFIX STREQUAL "sge"
		)
			STRING(
				REPLACE
				"sge"
				""
				SUFFIX
				${DEPENDENCY}
			)

			STRING(
				TOUPPER
				${SUFFIX}
				UPPER_SUFFIX
			)

			IF(NOT ENABLE_${UPPER_SUFFIX})
				MESSAGE(
					FATAL_ERROR
					"For ${LIB_NAME} to work you need to -D ENABLE_${UPPER_SUFFIX}=ON!"
				)
			ENDIF()
		ENDIF()
	ENDFOREACH()
ENDMACRO()

MACRO(
	PATH_DIFFERENCE
	OUTPUT
	OUTER_PATH
	INNER_PATH
)
	IF(
		${${PATH_DIFFERENCE}}
	)
		UNSET(${PATH_DIFFERENCE})
	ENDIF()

	SET(
		TEMP_INNER_PATH
		${INNER_PATH}
	)

	WHILE(
		NOT ${TEMP_INNER_PATH} STREQUAL ${OUTER_PATH}
	)
		GET_FILENAME_COMPONENT(
			PATH_COMPONENT
			${TEMP_INNER_PATH}
			NAME
		)

		SET(
			${OUTPUT}
			"${PATH_COMPONENT}/${${OUTPUT}}"
		)

		GET_FILENAME_COMPONENT(
			TEMP_INNER_PATH
			${TEMP_INNER_PATH}
			PATH
		)
	ENDWHILE()
ENDMACRO()

MACRO(
	ADD_SGE_BASE_LIBRARY
	LIB_NAME
	ADDITONAL_DEPS
)
	SET(
		SGE_LIB_NAME
		sge${LIB_NAME}
	)

	STRING(
		TOUPPER
		${LIB_NAME}
		UPPER_LIB_NAME
	)

	APPEND_SOURCE_DIR_AND_MAKE_GROUPS(
		"${SGE_${UPPER_LIB_NAME}_FILES}"
		SGE_${UPPER_LIB_NAME}_FILES_ABS
	)

	ADD_LIBRARY(
		${SGE_LIB_NAME}
		SHARED
		${SGE_${UPPER_LIB_NAME}_FILES_ABS}
	)

	CHECK_LIBRARY_DEPS(
		"${LIB_NAME}"
		"${ADDITONAL_DEPS}"
	)

	TARGET_LINK_LIBRARIES(
		${SGE_LIB_NAME}
		sgecore
		${ADDITONAL_DEPS}
	)

	INSTALL(
		TARGETS
		${SGE_LIB_NAME}
		DESTINATION
		${INSTALL_LIBRARY_DIR}
	)

	PATH_DIFFERENCE(
		LIB_INCLUDE_PATH
		${CMAKE_SOURCE_DIR}/src
		${CMAKE_CURRENT_SOURCE_DIR}
	)

	INSTALL(
		DIRECTORY
		${CMAKE_SOURCE_DIR}/include/sge/${LIB_INCLUDE_PATH}
		DESTINATION
		${INSTALL_INCLUDE_DIR}/sge/${LIB_INCLUDE_PATH}
	)
ENDMACRO()

# configure some resource paths
SET(
	SGE_PLUGIN_BUILD_PATH
	"${LIBRARY_OUTPUT_PATH}/plugins"
)

SET(
	SGE_PLUGIN_INSTALL_PATH
	"${PLUGIN_INSTALL_DIR}"
)

SET(
	SGE_MEDIA_BUILD_PATH
	"${CMAKE_SOURCE_DIR}/media"
)

SET(
	SGE_MEDIA_INSTALL_PATH
	"${MEDIA_INSTALL_DIR}"
)

ADD_LIBRARY(
	sgecore
	SHARED
	${SGE_CORE_INCLUDE_FILES_ABS}
	${SGE_CORE_SRC_FILES_ABS}
)

TARGET_LINK_LIBRARIES(
	sgecore
	${Fcppt_LIBRARIES}
	${Awl_LIBRARIES}
)

IF (NOT MSVC)
	TARGET_LINK_LIBRARIES (
		sgecore
		${Boost_SYSTEM_LIBRARY}
		${Boost_FILESYSTEM_LIBRARY}
	)
ENDIF ()

IF (UNIX)
	TARGET_LINK_LIBRARIES (sgecore dl)
ELSEIF (WIN32)
	TARGET_LINK_LIBRARIES (sgecore gdi32 kernel32 user32)
ENDIF ()

INSTALL(
	TARGETS
	sgecore
	DESTINATION
	${INSTALL_LIBRARY_DIR}
)

FIND_PACKAGE(CEGUI)
FIND_PACKAGE(Bullet)

# core libraries
OPTION (ENABLE_AUDIO "Build the audio library" ON)
OPTION (ENABLE_CHARCONV "Build the charconv library" ON)
OPTION (ENABLE_FONT "Build the font library" ON)
OPTION (ENABLE_IMAGE "Build the image library" ON)
OPTION (ENABLE_IMAGE2D "Build the image2d library" ON)
OPTION (ENABLE_IMAGE3D "Build the image3d library" ON)
OPTION (ENABLE_INPUT "Build the input library" ON)
OPTION (ENABLE_MODEL "Build the model library" ON)
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

IF (ENABLE_MODEL)
	ADD_SUBDIRECTORY(model)
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
OPTION (ENABLE_CEGUI "Build the cegui subsystem" ${CEGUI_FOUND})
OPTION (ENABLE_CAMERA "Build the camera" ON)
OPTION (ENABLE_CONFIG "Build the config library" ON)
OPTION (ENABLE_CONSOLE "Build the console" ON)
OPTION (ENABLE_FONTBITMAP "Build the bitmap font" ON)
OPTION (ENABLE_FONTTEXT "Build the font text library" ON)
OPTION (ENABLE_LINE_DRAWER "Build the line drawing library" ON)
OPTION (ENABLE_PARSE "Build the parse library" ON)
OPTION (ENABLE_PROJECTILE "Build the projectile subsystem" ${BULLET_FOUND})
OPTION (ENABLE_SHADER "Build the shader" ON)
OPTION (ENABLE_SPRITE "Build the sprite library" ON)
OPTION (ENABLE_SYSTEMS "Build the systems library" ON)
OPTION (ENABLE_TEXTURE "Build the texture helpers" ON)
OPTION (ENABLE_TIME "Build the time library" ON)
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

IF (ENABLE_TIME)
	ADD_SUBDIRECTORY(time)
ENDIF ()

IF (ENABLE_VIEWPORT)
	ADD_SUBDIRECTORY(viewport)
ENDIF ()

ADD_SUBDIRECTORY (plugins)

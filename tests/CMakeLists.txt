function(
	add_sge_test
	PATH_NAME
)
	set(
		OPTION_ARGS
		NO_CODE
	)

	set(
		MULTI_ARGS
		SGE_DEPS
		ADDITIONAL_DEPS
		INCLUDE_DIRS
	)

	cmake_parse_arguments(
		""
		"${OPTION_ARGS}"
		""
		"${MULTI_ARGS}"
		${ARGN}
	)

	sge_check_optional_deps(
		"${PATH_NAME}"
		"${_SGE_DEPS}"
	)

	transform_sge_link_targets(
		"${_SGE_DEPS}"
		SGE_LIBRARIES_RESULT
	)

	if(
		_NO_CODE
	)
		set(
			NO_CODE
			"NO_CODE"
		)
	endif()

	fcppt_utils_add_test(
		${FCPPT_UTILS_PROJECT_SOURCE_DIR}/tests
		"${PATH_NAME}"
		${NO_CODE}
		LINK_LIBS
			${SGE_LIBRARIES_RESULT}
			${_ADDITIONAL_DEPS}
		INCLUDE_DIRS
			${_INCLUDE_DIRS}
	)
endfunction()

set(
	SGE_TESTS_CHARCONV_TEST_DATA
	"${CMAKE_CURRENT_SOURCE_DIR}/charconv/test_data"
)

configure_file(
	charconv/test_data.hpp.in
	"${CMAKE_CURRENT_BINARY_DIR}/include/sge/tests/charconv/test_data.hpp"
)

add_sge_test(
	bresenham/main
	SGE_DEPS
		sgebresenham_interface
	ADDITIONAL_DEPS
		fcppt_core_interface
)

add_sge_test(
	charconv/main
	SGE_DEPS
		sgecharconv
	ADDITIONAL_DEPS
		${fcppt_core_TARGET}
		${FCPPT_UTILS_FILESYSTEM_LIBRARIES}
	INCLUDE_DIRS
		"${CMAKE_CURRENT_BINARY_DIR}/include"
)

add_sge_test(
	charconv/flake_config
	SGE_DEPS
		sgecharconv
	ADDITIONAL_DEPS
		${fcppt_core_TARGET}
		${FCPPT_UTILS_FILESYSTEM_LIBRARIES}
	INCLUDE_DIRS
		"${CMAKE_CURRENT_BINARY_DIR}/include"
)

add_sge_test(
	charconv/various
	SGE_DEPS
		sgecharconv
	ADDITIONAL_DEPS
		${fcppt_core_TARGET}
)

add_sge_test(
	console/cursor
	SGE_DEPS
		sgeconsolegfx
)

add_sge_test(
	image/color/convert
	NO_CODE
	SGE_DEPS
		sgeimage
		sgeimagecolor
	ADDITIONAL_DEPS
		${fcppt_core_TARGET}
)

add_sge_test(
	image2d/copy_and_convert
	SGE_DEPS
		sgeimage2d
)

add_sge_test(
	image2d/save_load
	SGE_DEPS
		sgeconfig
		sgeimage2d
		sgelog
		sgeplugin
	ADDITIONAL_DEPS
		${fcppt_log_TARGET}
)

add_sge_test(
	projectile/triangulate_long
	SGE_DEPS
		sgeprojectile_interface
	ADDITIONAL_DEPS
		${fcppt_core_TARGET}
)

add_sge_test(
	parse/json
	SGE_DEPS
		sgeparse
		sgeparsejson
	ADDITIONAL_DEPS
		${fcppt_core_TARGET}
		fcppt_catch_interface
		fcppt_parse_interface
	COMPILE_DEFINITIONS
		CATCH_CONFIG_ENABLE_PAIR_STRINGMAKER
)

add_sge_test(
	parse/json/convert_from
	SGE_DEPS
		sgeparsejson
	ADDITIONAL_DEPS
		${fcppt_core_TARGET}
)

add_sge_test(
	parse/ini
	SGE_DEPS
		sgeparse
		sgeparseini
	ADDITIONAL_DEPS
		${fcppt_core_TARGET}
		fcppt_catch_interface
		fcppt_parse_interface
	COMPILE_DEFINITIONS
		CATCH_CONFIG_ENABLE_TUPLE_STRINGMAKER
)

add_sge_test(
	sprite/types
	SGE_DEPS
		sgeimage
		sgeimagecolor
		sgesprite
		sgetexture
	ADDITIONAL_DEPS
		fcppt_core_interface
	NO_CODE
)

add_sge_test(
	rucksack/box
	SGE_DEPS
		sgerucksack
	ADDITIONAL_DEPS
		${fcppt_core_TARGET}
)

add_sge_test(
	timer/main
	SGE_DEPS
		sgetimer_interface
	ADDITIONAL_DEPS
		${fcppt_core_TARGET}
)

function(
	add_sge_test
	PATHNAME
)
	set(
		MULTI_ARGS
		SGE_DEPS
		ADDITIONAL_DEPS
		INCLUDE_DIRS
	)

	cmake_parse_arguments(
		""
		""
		""
		"${MULTI_ARGS}"
		${ARGN}
	)

	sge_check_optional_deps(
		"${PATHNAME}"
		"${_SGE_DEPS}"
	)

	transform_sge_link_targets(
		"${_SGE_DEPS}"
		SGE_LIBRARIES_RESULT
	)

	fcppt_utils_add_test(
		"${PATHNAME}"
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
	charconv/main
	SGE_DEPS
		sgecharconv
	ADDITIONAL_DEPS
		${fcppt_core_TARGET}
		${Boost_FILESYSTEM_LIBRARIES}
	INCLUDE_DIRS
		"${CMAKE_CURRENT_BINARY_DIR}/include"
)

add_sge_test(
	charconv/flake_config
	SGE_DEPS
		sgecharconv
	ADDITIONAL_DEPS
		${fcppt_core_TARGET}
		${Boost_FILESYSTEM_LIBRARIES}
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
	SGE_DEPS
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
		sgeplugin
)

add_sge_test(
	projectile/triangulate_long
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
	ADDITIONAL_DEPS
		${fcppt_core_TARGET}
)

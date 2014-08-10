function(
	ADD_SGE_TEST
	PATHNAME
	SGE_LIBRARIES
	ADDITIONAL_LIBRARIES
	INCLUDE_DIRS
)
	sge_check_optional_deps(
		"${PATHNAME}"
		"${SGE_LIBRARIES}"
	)

	transform_sge_link_targets(
		"${SGE_LIBRARIES}"
		SGE_LIBRARIES_RESULT
	)

	fcppt_utils_add_test(
		"${PATHNAME}"
		"${SGE_LIBRARIES_RESULT};${ADDITIONAL_LIBRARIES}"
		"${INCLUDE_DIRS}"
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
	"sgecharconv"
	"${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
	"${CMAKE_CURRENT_BINARY_DIR}/include"
)

add_sge_test(
	charconv/flake_config
	"sgecharconv"
	"${fcppt_core_TARGET};${Boost_FILESYSTEM_LIBRARIES}"
	"${CMAKE_CURRENT_BINARY_DIR}/include"
)

add_sge_test(
	charconv/various
	"sgecharconv"
	"${fcppt_core_TARGET}"
	""
)

add_sge_test(
	console/cursor
	"sgeconsolegfx"
	""
	""
)

add_sge_test(
	image2d/copy_and_convert
	"sgeimage2d"
	""
	""
)

add_sge_test(
	image2d/save_load
	"sgeconfig;sgeimage2d;sgeplugin"
	""
	""
)

add_sge_test(
	projectile/triangulate_long
	""
	"${fcppt_core_TARGET}"
	""
)

add_sge_test(
	parse/json
	"sgeparse;sgeparsejson"
	"${fcppt_core_TARGET}"
	""
)

add_sge_test(
	parse/ini
	"sgeparse;sgeparseini"
	"${fcppt_core_TARGET}"
	""
)

add_sge_test(
	timer/main
	""
	"${fcppt_core_TARGET}"
	""
)

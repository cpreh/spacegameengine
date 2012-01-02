find_package(
	Boost 1.45.0 REQUIRED COMPONENTS
	unit_test_framework
)

function(
	ADD_SGE_TEST
	PATHNAME
	SGE_LIBRARIES
	ADDITIONAL_LIBRARIES
)
	sge_check_optional_deps(
		"${PATHNAME}"
		"${SGE_LIBRARIES}"
	)

	string(
		REPLACE
		"/"
		"_"
		TESTNAME
		${PATHNAME}
	)

	set(
		TESTNAME
		test_${TESTNAME}
	)

	add_executable(
		${TESTNAME}
		${PATHNAME}.cpp
	)

	if(
		Boost_USE_STATIC_LIBS
	)
		set_property(
			TARGET ${TESTNAME}
			PROPERTY COMPILE_FLAGS
			"-DBOOST_TEST_NO_LIB -DBOOST_TEST_MODULE=${TESTNAME}"
		)
	else()
		set_property(
			TARGET ${TESTNAME}
			PROPERTY COMPILE_FLAGS
			"-DBOOST_TEST_DYN_LINK -DBOOST_TEST_MODULE=${TESTNAME}"
		)
	endif()

	transform_sge_link_targets(
		"${SGE_LIBRARIES}"
	)

	if(
		SGE_DEFAULT_LINK_STATIC
	)
		sge_set_static_flags(
			${TESTNAME}
		)
	endif()

	target_link_libraries(
		${TESTNAME}
		${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
		${SGELIBS_TARGETS_RESULT}
		${ADDITIONAL_LIBRARIES}
	)

	add_test(
		NAME
		${TESTNAME}
		COMMAND
		${TESTNAME}
	)
endfunction()

add_sge_test(
	charconv/main
	"sgecharconv;sgeconfig;sgeplugin"
	""
)

add_sge_test(
	console/cursor
	"sgeconsole"
	""
)

add_sge_test(
	image2d/copy_and_convert
	"sgeimage2d"
	""
)

add_sge_test(
	parse/json
	"sgeparse"
	"${Fcppt_core_LIBRARIES}"
)

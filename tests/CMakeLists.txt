find_package(
	Boost 1.45.0 REQUIRED COMPONENTS
	unit_test_framework
)

function(
	ADD_SGE_TEST
	PATHNAME
	SGELIBS
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
		"${SGELIBS}"
	)

	target_link_libraries(
		${TESTNAME}
		${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
		${SGELIBS_TARGETS_RESULT}
	)

	add_test(
		NAME
		${TESTNAME}
		COMMAND
		${TESTNAME}
	)
endfunction()

if(ENABLE_CONFIG)
	ADD_SGE_TEST(charconv/main "sgecharconv;sgeconfig")
endif()

if(ENABLE_CONSOLE)
	ADD_SGE_TEST(console/cursor "sgeconsole")
endif()

if(ENABLE_IMAGE2D)
	ADD_SGE_TEST(image2d/copy_and_convert "sgeimage2d")
endif()

if(ENABLE_PARSE)
	ADD_SGE_TEST(parse/json "sgeparse")
endif()

function(
	ADD_ALDA_TEST
	TESTNAME_ARG
	ADDITIONAL_LIBRARIES
)
	set(
		TESTNAME
		"test_alda_${TESTNAME_ARG}"
	)

	add_executable(
		${TESTNAME}
		${TESTNAME_ARG}.cpp
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

	alda_set_static_flags(
		"${TESTNAME}"
	)

	target_link_libraries(
		${TESTNAME}
		${ALDA_DEFAULT_LINK_TARGET}
		${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
		${ADDITIONAL_LIBRARIES}
	)

	add_test(
		NAME
		${TESTNAME}
		COMMAND
		${TESTNAME}
	)
endfunction()

add_alda_test(
	float
	""
)

add_alda_test(
	length_stream
	"${fcppt_core_TARGET}"
)

add_alda_test(
	signed
	"${fcppt_core_TARGET}"
)

add_alda_test(
	simple
	"${fcppt_core_TARGET}"
)

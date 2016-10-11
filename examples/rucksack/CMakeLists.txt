option(
	ENABLE_RUCKSACKTESTBED
	"Build rucksack testbed library"
	ON
)

add_subdirectory(
	testbed
)

function(
	add_sge_rucksack_example
	EXAMPLE_NAME
)
	set(
		MULTI_ARGS
		SGE_DEPS
		ADDITIONAL_DEPS
	)

	cmake_parse_arguments(
		""
		""
		""
		"${MULTI_ARGS}"
		${ARGN}
	)

	add_sge_example(
		"rucksack/${EXAMPLE_NAME}"
		SGE_DEPS
			sgerucksacktestbed
			${_SGE_DEPS}
		ADDITIONAL_DEPS
			${_ADDITIONAL_DEPS}
	)
endfunction()

add_sge_rucksack_example(
	box
	SGE_DEPS
		sgeimagecolor
		sgerucksack
		sgerucksackviewport
		sgesystems
	ADDITIONAL_DEPS
		${fcppt_core_TARGET}
)

add_sge_rucksack_example(
	enumeration
	SGE_DEPS
		sgeimagecolor
		sgerucksack
		sgerucksackviewport
		sgesystems
	ADDITIONAL_DEPS
		${fcppt_core_TARGET}
)

add_sge_rucksack_example(
	master_and_slaves
	SGE_DEPS
		sgeimagecolor
		sgerucksack
		sgerucksackviewport
		sgesystems
	ADDITIONAL_DEPS
		${fcppt_core_TARGET}
)

option(
	ENABLE_RUCKSACKTESTBED "Build rucksack testbed library" ON
)

add_subdirectory(
	testbed
)

macro(
	add_sge_rucksack_example
	EXAMPLE_NAME
	SGE_DEPS
	ADDITIONAL_DEPS
)
	list(
		APPEND
		SGE_DEPS
		"rucksack_testbed"
	)

	add_sge_example(
		"rucksack_${EXAMPLE_NAME}"
		"sgerucksacktestbed;${SGE_DEPS}"
		"${ADDITIONAL_DEPS}"
		"${CMAKE_CURRENT_SOURCE_DIR}/testbed/include"
	)
endmacro()

add_sge_rucksack_example(
	box
	"sgeimagecolor;sgerucksack;sgesystems"
	""
)

add_sge_rucksack_example(
	enumeration
	"sgeimagecolor;sgerucksack;sgesystems"
	""
)

add_sge_rucksack_example(
	master_and_slaves
	"sgeimagecolor;sgerucksack;sgesystems"
	""
)

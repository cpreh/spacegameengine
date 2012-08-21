set(
	SGE_RUCKSACKTESTBED_FILES
	examples/rucksack/testbed/include/sge/rucksack/testbed/object.hpp
	examples/rucksack/testbed/include/sge/rucksack/testbed/object_impl_fwd.hpp
	examples/rucksack/testbed/src/include/sge/src/rucksack/testbed/object_impl.hpp
	examples/rucksack/testbed/src/object.cpp
	examples/rucksack/testbed/src/object_impl.cpp
)

add_sge_example_library(
	"rucksack/testbed"
	"sgelog;sgerenderer;sgerucksack;sgesprite;sgesystems;sgeviewport;sgewindow"
	""
	""
	""
	"${CMAKE_CURRENT_SOURCE_DIR}/include;${CMAKE_CURRENT_SOURCE_DIR}/src/include"
)

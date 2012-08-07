# TODO
add_library(
	rucksack_testbed
	STATIC
	testbed.cpp
	testbed_impl.cpp)


ADD_RUCKSACK_EXAMPLE(box "")
ADD_RUCKSACK_EXAMPLE(enumeration "${Boost_CHRONO_LIBRARIES}")
ADD_RUCKSACK_EXAMPLE(master_and_slaves "${Boost_CHRONO_LIBRARIES}")

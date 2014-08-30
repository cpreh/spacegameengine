set(
	SGE_RUCKSACKVIEWPORT_FILES
	include/sge/rucksack/viewport/adaptor.hpp
	include/sge/rucksack/viewport/adaptor_fwd.hpp
	src/rucksack/viewport/adaptor.cpp
)

add_sge_base_library(
	"rucksack/viewport"
	"sgerenderer;sgerucksack;sgeviewport"
	"${fcppt_core_TARGET}"
	""
	""
	""
	""
)

set(
	SGE_CG_FILES
	include/sge/cg/context.hpp
	include/sge/cg/context_fwd.hpp
	include/sge/cg/exception.hpp
	include/sge/cg/vertex_profile.hpp
	include/sge/cg/vertex_profile_fwd.hpp
	include/sge/cg/vertex_profile_unique_ptr.hpp
	src/cg/context.cpp
	src/cg/exception.cpp
	src/cg/vertex_profile.cpp
)

include_directories(
	${Cg_INCLUDE_DIRS}
)

add_sge_base_library(
	cg
	"sgecore"
	"${Cg_LIBRARIES}"
	""
	"sgecore"
)

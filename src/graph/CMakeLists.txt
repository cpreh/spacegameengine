set(
	SGE_GRAPH_FILES
	include/sge/graph/object.hpp
	include/sge/graph/object_decl.hpp
	include/sge/graph/object_fwd.hpp
	include/sge/graph/scalar.hpp
	src/graph/object.cpp
)

include_directories(
	${FCPPT_UTILS_INCLUDE_SYSTEM}
)

add_sge_base_library(
	"graph"
	"sgerenderer;sgeimage;sgeimage2d;sgesprite;sgetexture"
	"${Fcppt_filesystem_LIBRARIES}"
	""
	""
)

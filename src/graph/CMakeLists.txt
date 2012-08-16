set(
	SGE_GRAPH_FILES
	include/sge/graph/axis_constraint.hpp
	include/sge/graph/axis_constraint_fwd.hpp
	include/sge/graph/background_alt_color.hpp
	include/sge/graph/background_color.hpp
	include/sge/graph/baseline.hpp
	include/sge/graph/baseline_color.hpp
	include/sge/graph/color_scheme.hpp
	include/sge/graph/color_schemes.hpp
	include/sge/graph/foreground_alt_color.hpp
	include/sge/graph/foreground_color.hpp
	include/sge/graph/object.hpp
	include/sge/graph/optional_axis_constraint.hpp
	include/sge/graph/parameters.hpp
	include/sge/graph/position.hpp
	include/sge/graph/scalar.hpp
	src/graph/axis_constraint.cpp
	src/graph/color_scheme.cpp
	src/graph/color_schemes.cpp
	src/graph/object.cpp
)

include_directories(
	${FCPPT_UTILS_INCLUDE_SYSTEM}
)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_sge_base_library(
	"graph"
	"sgerenderer;sgeimage;sgeimage2d;sgesprite;sgetexture"
	"${Fcppt_filesystem_LIBRARIES}"
	""
	""
)

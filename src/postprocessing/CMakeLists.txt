set(
	SGE_POSTPROCESSING_FILES
	include/sge/postprocessing/context.hpp
	include/sge/postprocessing/context_fwd.hpp
	include/sge/postprocessing/fullscreen_quad.hpp
	include/sge/postprocessing/fullscreen_quad_fwd.hpp
	include/sge/postprocessing/vf/format.hpp
	include/sge/postprocessing/vf/format_part.hpp
	include/sge/postprocessing/vf/position.hpp
	include/sge/postprocessing/vf/texcoord.hpp
	src/postprocessing/context.cpp
	src/postprocessing/fullscreen_quad.cpp
)

include_directories(
	${FCPPT_UTILS_INCLUDE_SYSTEM}
	${Cg_INCLUDE_DIRS}
)

add_sge_base_library(
	"postprocessing"
	"sgecg;sgerenderer;sgerenderercg;sgeviewport;sgeconfig;sgeshader"
	"${Fcppt_filesystem_LIBRARIES}"
	""
	""
)

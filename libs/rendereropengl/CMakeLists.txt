remove_definitions(
	"-D SGE_PLUGIN_INSTANTIATE_EXPORTS"
)

set(
	SGE_RENDEREROPENGL_FILES
	libs/rendereropengl/include/sge/renderer/opengl/buffer/base.hpp
	libs/rendereropengl/include/sge/renderer/opengl/buffer/base_fwd.hpp
	libs/rendereropengl/include/sge/renderer/opengl/buffer/id.hpp
	libs/rendereropengl/include/sge/renderer/opengl/glinclude.hpp
	libs/rendereropengl/include/sge/renderer/opengl/texture/base.hpp
	libs/rendereropengl/include/sge/renderer/opengl/texture/base_fwd.hpp
	libs/rendereropengl/include/sge/renderer/opengl/texture/id.hpp
	libs/rendereropengl/include/sge/renderer/opengl/texture/type.hpp
	libs/rendereropengl/src/renderer/opengl/buffer/base.cpp
	libs/rendereropengl/src/renderer/opengl/texture/base.cpp
)

add_sge_base_library(
	"renderer/opengl"
	ADDITIONAL_DEPS
		sgecore_interface
		"${OPENGL_gl_LIBRARY}"
		fcppt_core_interface
	TRANSITIVE_ADDITIONAL_DEPS
		sgecore_interface
		fcppt_core_interface
	INCLUDE_DIRS
		${OPENGL_INCLUDE_DIR}
	TRANSITIVE_INCLUDE_DIRS
		${OPENGL_INCLUDE_DIR}
)

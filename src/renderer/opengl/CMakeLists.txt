remove_definitions(
	"-D SGE_PLUGIN_INSTANTIATE_EXPORTS"
)

include_directories(
	${OPENGL_INCLUDE_DIR}
)

set(
	SGE_RENDEREROPENGL_FILES
	include/sge/renderer/opengl/buffer/base.hpp
	include/sge/renderer/opengl/buffer/base_fwd.hpp
	include/sge/renderer/opengl/buffer/base_ptr.hpp
	include/sge/renderer/opengl/buffer/buffer.hpp
	include/sge/renderer/opengl/buffer/id.hpp
	include/sge/renderer/opengl/glinclude.hpp
	include/sge/renderer/opengl/opengl.hpp
	include/sge/renderer/opengl/symbol.hpp
	include/sge/renderer/opengl/texture/base.hpp
	include/sge/renderer/opengl/texture/base_fwd.hpp
	include/sge/renderer/opengl/texture/base_ptr.hpp
	include/sge/renderer/opengl/texture/id.hpp
	include/sge/renderer/opengl/texture/texture.hpp
	include/sge/renderer/opengl/texture/type.hpp
	src/renderer/opengl/buffer/base.cpp
	src/renderer/opengl/texture/base.cpp
)

add_sge_base_library(
	rendereropengl
	""
	"${OPENGL_gl_LIBRARY}"
	""
	""
)

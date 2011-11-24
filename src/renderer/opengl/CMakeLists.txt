REMOVE_DEFINITIONS(
	"-D SGE_PLUGIN_INSTANTIATE_EXPORTS"
)

INCLUDE_DIRECTORIES(
	${OPENGL_INCLUDE_DIR}
)

SET(
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
	src/renderer/opengl/buffer/base.cpp
	src/renderer/opengl/texture/base.cpp
)

ADD_SGE_BASE_LIBRARY(
	rendereropengl
	""
)

TARGET_LINK_LIBRARIES(
	sgerendereropengl
	${OPENGL_gl_LIBRARY}
)

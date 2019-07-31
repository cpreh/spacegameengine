//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/vf/attribute_config_fwd.hpp>
#include <sge/opengl/vf/attribute_context.hpp>
#include <sge/opengl/vf/get_attribute_config.hpp>
#include <sge/renderer/unsupported.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/to_exception.hpp>


sge::opengl::vf::attribute_config const &
sge::opengl::vf::get_attribute_config(
	sge::opengl::vf::attribute_context const &_context
)
{
	return
		fcppt::optional::to_exception(
			_context.config(),
			[]{
				return
					sge::renderer::unsupported(
						FCPPT_TEXT("glVertexAttribPointer"),
						FCPPT_TEXT("GL_VERSION_2_0"),
						FCPPT_TEXT("GL_ARB_vertex_shader")
					);
			}
		);
}

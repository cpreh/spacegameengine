//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/common.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/texture/basic_parameters.hpp>
#include <sge/opengl/texture/depth_stencil.hpp>
#include <sge/opengl/texture/depth_stencil_basic.hpp>
#include <sge/opengl/texture/surface_context.hpp>
#include <sge/opengl/texture/convert/make_type.hpp>
#include <sge/renderer/texture/depth_stencil.hpp>
#include <sge/renderer/texture/depth_stencil_parameters_fwd.hpp>


sge::opengl::texture::depth_stencil::depth_stencil(
	sge::opengl::texture::basic_parameters const &_basic_parameters,
	sge::renderer::texture::depth_stencil_parameters const &_parameters
)
:
	sge::opengl::texture::depth_stencil_basic(
		_basic_parameters,
		sge::opengl::texture::convert::make_type(
			GL_TEXTURE_2D
		),
		_parameters,
		sge::opengl::context::use<
			sge::opengl::texture::surface_context
		>(
			_basic_parameters.context()
		).config()
	)
{
}

sge::opengl::texture::depth_stencil::~depth_stencil()
{
}

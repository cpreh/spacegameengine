//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_DEPTH_STENCIL_TYPES_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_DEPTH_STENCIL_TYPES_HPP_INCLUDED

#include <sge/opengl/texture/depth_stencil_surface_types_fwd.hpp>
#include <sge/opengl/texture/depth_stencil_types_fwd.hpp>
#include <sge/renderer/texture/depth_stencil_fwd.hpp>
#include <sge/renderer/texture/depth_stencil_parameters_fwd.hpp>
#include <fcppt/string.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

struct depth_stencil_types
{
	typedef
	sge::renderer::texture::depth_stencil
	base;

	typedef
	sge::renderer::texture::depth_stencil_parameters
	parameters;

	typedef
	sge::opengl::texture::depth_stencil_surface_types
	buffer_types;

	static
	fcppt::string
	name();
};

}
}
}

#endif

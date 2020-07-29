//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_CUBE_TYPES_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_CUBE_TYPES_HPP_INCLUDED

#include <sge/opengl/texture/color_surface_types_fwd.hpp>
#include <sge/opengl/texture/cube_types_fwd.hpp>
#include <sge/renderer/texture/cube_fwd.hpp>
#include <sge/renderer/texture/cube_parameters_fwd.hpp>
#include <fcppt/string.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

struct cube_types
{
	using
	base
	=
	sge::renderer::texture::cube;

	using
	parameters
	=
	sge::renderer::texture::cube_parameters;

	using
	buffer_types
	=
	sge::opengl::texture::color_surface_types;

	[[nodiscard]]
	static
	fcppt::string
	name();
};

}
}
}

#endif

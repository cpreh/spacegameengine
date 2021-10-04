//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_PLANAR_TYPES_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_PLANAR_TYPES_HPP_INCLUDED

#include <sge/opengl/texture/color_surface_types_fwd.hpp>
#include <sge/opengl/texture/planar_types_fwd.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/renderer/texture/planar_parameters_fwd.hpp>
#include <fcppt/string.hpp>


namespace sge::opengl::texture
{

struct planar_types
{
	using
	base
	=
	sge::renderer::texture::planar;

	using
	parameters
	=
	sge::renderer::texture::planar_parameters;

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

#endif

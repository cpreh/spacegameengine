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


namespace sge
{
namespace opengl
{
namespace texture
{

struct planar_types
{
	typedef sge::renderer::texture::planar base;

	typedef sge::renderer::texture::planar_parameters parameters;

	typedef sge::opengl::texture::color_surface_types buffer_types;

	static
	fcppt::string
	name();
};

}
}
}

#endif

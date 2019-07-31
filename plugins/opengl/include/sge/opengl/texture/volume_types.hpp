//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_VOLUME_TYPES_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_VOLUME_TYPES_HPP_INCLUDED

#include <sge/opengl/texture/color_volume_types_fwd.hpp>
#include <sge/opengl/texture/volume_types_fwd.hpp>
#include <sge/renderer/texture/volume_fwd.hpp>
#include <sge/renderer/texture/volume_parameters_fwd.hpp>
#include <fcppt/string.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

struct volume_types
{
	typedef
	sge::renderer::texture::volume
	base;

	typedef
	sge::renderer::texture::volume_parameters
	parameters;

	typedef
	sge::opengl::texture::color_volume_types
	buffer_types;

	static
	fcppt::string
	name();
};

}
}
}

#endif

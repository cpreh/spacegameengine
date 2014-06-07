/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_OPENGL_TEXTURE_BUFFER_SURFACE_TYPES_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BUFFER_SURFACE_TYPES_HPP_INCLUDED

#include <sge/opengl/texture/buffer_surface_types_fwd.hpp>
#include <sge/opengl/texture/init_function.hpp>
#include <sge/opengl/texture/sub_function.hpp>
#include <sge/renderer/size_type.hpp>
#include <fcppt/math/size_type.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

struct buffer_surface_types
{
	static
	sge::renderer::size_type
	min_size();

	static fcppt::math::size_type const num_dims = 2;

	typedef sge::opengl::texture::init_function<
		num_dims
	>::type init_function_type;

	static
	init_function_type
	init_function();

	typedef sge::opengl::texture::sub_function<
		num_dims
	>::type sub_function_type;

	static
	sub_function_type
	sub_function();
};

}
}
}

#endif

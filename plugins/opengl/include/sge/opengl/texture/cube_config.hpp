/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_OPENGL_TEXTURE_CUBE_CONFIG_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_CUBE_CONFIG_HPP_INCLUDED

#include <sge/opengl/texture/cube_config_fwd.hpp>
#include <sge/opengl/texture/cube_side_array.hpp>
#include <sge/opengl/texture/type.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

class cube_config
{
public:
	cube_config(
		sge::opengl::texture::type,
		sge::opengl::texture::cube_side_array const &
	);

	sge::opengl::texture::type
	cube_texture_type() const;

	sge::opengl::texture::cube_side_array const &
	cube_sides() const;
private:
	sge::opengl::texture::type cube_texture_type_;

	sge::opengl::texture::cube_side_array cube_sides_;
};

}
}
}

#endif

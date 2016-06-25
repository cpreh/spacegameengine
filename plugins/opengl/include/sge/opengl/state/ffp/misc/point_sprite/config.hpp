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


#ifndef SGE_OPENGL_STATE_FFP_MISC_POINT_SPRITE_CONFIG_HPP_INCLUDED
#define SGE_OPENGL_STATE_FFP_MISC_POINT_SPRITE_CONFIG_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/state/ffp/misc/point_sprite/config_fwd.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sge
{
namespace opengl
{
namespace state
{
namespace ffp
{
namespace misc
{
namespace point_sprite
{

class config
{
	FCPPT_NONASSIGNABLE(
		config
	);
public:
	FCPPT_MAKE_STRONG_TYPEDEF(
		GLenum,
		point_sprite_flag_type
	);

	FCPPT_MAKE_STRONG_TYPEDEF(
		GLenum,
		vertex_shader_size_flag_type
	);

	FCPPT_MAKE_STRONG_TYPEDEF(
		GLenum,
		coord_replace_flag_type
	);

	config(
		point_sprite_flag_type,
		vertex_shader_size_flag_type,
		coord_replace_flag_type
	);

	point_sprite_flag_type
	point_sprite_flag() const;

	vertex_shader_size_flag_type
	vertex_shader_size_flag() const;

	coord_replace_flag_type
	coord_replace_flag() const;
private:
	point_sprite_flag_type const point_sprite_flag_;

	vertex_shader_size_flag_type const vertex_shader_size_flag_;

	coord_replace_flag_type const coord_replace_flag_;
};

}
}
}
}
}
}

#endif

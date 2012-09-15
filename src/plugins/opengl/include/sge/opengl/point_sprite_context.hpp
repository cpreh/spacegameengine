/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_POINT_SPRITE_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_POINT_SPRITE_CONTEXT_HPP_INCLUDED

#include <sge/opengl/optional_enum.hpp>
#include <sge/opengl/point_sprite_context_fwd.hpp>
#include <sge/opengl/context/system/base.hpp>
#include <sge/opengl/context/system/id.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{

class point_sprite_context
:
	public sge::opengl::context::system::base
{
	FCPPT_NONCOPYABLE(
		point_sprite_context
	);
public:
	point_sprite_context();

	~point_sprite_context();

	bool
	is_supported() const;

	sge::opengl::optional_enum const
	point_sprite_flag() const;

	sge::opengl::optional_enum const
	vertex_shader_size_flag() const;

	sge::opengl::optional_enum const
	coord_replace_flag() const;

	typedef void parameter;

	static
	sge::opengl::context::system::id const
	static_id;
private:
	bool const
		is_native_,
		is_arb_;

	sge::opengl::optional_enum const
		point_sprite_flag_,
		vertex_shader_size_flag_,
		coord_replace_flag_;
};

}
}

#endif

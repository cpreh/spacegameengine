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


#ifndef SGE_OPENGL_TEXTURE_CUBE_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_CUBE_CONTEXT_HPP_INCLUDED

#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/texture/bind_type.hpp>
#include <sge/opengl/texture/cube_side_array.hpp>
#include <sge/opengl/texture/optional_bind_type.hpp>
#include <sge/opengl/texture/optional_type.hpp>
#include <sge/opengl/texture/type.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

class cube_context
:
	public sge::opengl::context::base
{
	FCPPT_NONCOPYABLE(
		cube_context
	);
public:
	cube_context();

	~cube_context();

	bool
	have_cube_texture() const;

	sge::opengl::texture::type const
	cube_texture_type() const;

	sge::opengl::texture::bind_type const
	cube_texture_bind_type() const;

	sge::opengl::texture::cube_side_array const &
	cube_sides() const;

	typedef void needs_before;

	static sge::opengl::context::id const static_id;
private:
	bool const
		cube_texture_normal_,
		cube_texture_arb_;

	sge::opengl::texture::optional_type const cube_texture_type_;

	sge::opengl::texture::optional_bind_type const cube_texture_bind_type_;

	typedef fcppt::optional<
		sge::opengl::texture::cube_side_array
	> optional_cube_side_array;

	optional_cube_side_array const cube_sides_;
};

}
}
}

#endif

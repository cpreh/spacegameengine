/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_CUBE_TEXTURE_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_CUBE_TEXTURE_CONTEXT_HPP_INCLUDED

#include "context/base.hpp"
#include "context/id.hpp"
#include "common.hpp"
#include "cube_side_array.hpp"
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opengl
{

class cube_texture_context
:
	public context::base
{
	FCPPT_NONCOPYABLE(cube_texture_context)
public:
	cube_texture_context();

	~cube_texture_context();
	
	bool
	have_cube_texture() const;

	GLenum
	cube_texture_type() const;

	cube_side_array const &
	cube_sides() const;

	typedef void needs_before;

	static context::id const static_id;
private:
	bool const
		cube_texture_normal_,
		cube_texture_arb_;

	GLenum const cube_texture_type_;

	cube_side_array const cube_sides_;
};

}
}

#endif

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


#include <sge/cg/profile/shader_type.hpp>
#include <sge/opengl/cg/profile/convert_shader_type.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cgGL.h>
#include <fcppt/config/external_end.hpp>


CGGLenum
sge::opengl::cg::profile::convert_shader_type(
	sge::cg::profile::shader_type const _shader_type
)
{
	switch(
		_shader_type
	)
	{
	case sge::cg::profile::shader_type::vertex:
		return CG_GL_VERTEX;
	case sge::cg::profile::shader_type::pixel:
		return CG_GL_FRAGMENT;
	case sge::cg::profile::shader_type::geometry:
		return CG_GL_GEOMETRY;
	}

	FCPPT_ASSERT_UNREACHABLE;
}

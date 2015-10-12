/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/glx/visual/rgb_triple.hpp>


sge::opengl::glx::visual::rgb_triple::rgb_triple(
	sge::opengl::glx::visual::rgb_triple::red_bits const _red,
	sge::opengl::glx::visual::rgb_triple::green_bits const _green,
	sge::opengl::glx::visual::rgb_triple::blue_bits const _blue
)
:
	red_(
		_red
	),
	green_(
		_green
	),
	blue_(
		_blue
	)
{
}

sge::opengl::glx::visual::rgb_triple::red_bits
sge::opengl::glx::visual::rgb_triple::red() const
{
	return
		red_;
}

sge::opengl::glx::visual::rgb_triple::green_bits
sge::opengl::glx::visual::rgb_triple::green() const
{
	return
		green_;
}

sge::opengl::glx::visual::rgb_triple::blue_bits
sge::opengl::glx::visual::rgb_triple::blue() const
{
	return
		blue_;
}

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


#include <sge/opengl/xrandr/mode.hpp>
#include <sge/opengl/xrandr/mode_index.hpp>
#include <sge/opengl/xrandr/refresh_rate.hpp>
#include <sge/opengl/xrandr/rotation.hpp>


sge::opengl::xrandr::mode::mode(
	sge::opengl::xrandr::mode_index const _index,
	sge::opengl::xrandr::rotation const _rotation,
	sge::opengl::xrandr::refresh_rate const _rate
)
:
	index_{
		_index
	},
	rotation_{
		_rotation
	},
	rate_{
		_rate
	}
{
}

sge::opengl::xrandr::mode_index
sge::opengl::xrandr::mode::index() const
{
	return
		index_;
}

sge::opengl::xrandr::rotation
sge::opengl::xrandr::mode::rotation() const
{
	return
		rotation_;
}

sge::opengl::xrandr::refresh_rate
sge::opengl::xrandr::mode::rate() const
{
	return
		rate_;
}

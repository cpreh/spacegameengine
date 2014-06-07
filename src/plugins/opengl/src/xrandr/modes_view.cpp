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


#include <sge/opengl/xrandr/modes_view.hpp>
#include <sge/opengl/xrandr/screen_resources.hpp>


sge::opengl::xrandr::modes_view::modes_view(
	sge::opengl::xrandr::screen_resources const &_resources
)
:
	resources_(
		_resources
	)
{
}

sge::opengl::xrandr::modes_view::const_iterator
sge::opengl::xrandr::modes_view::begin() const
{
	return
		resources_.get_ref().modes;
}

sge::opengl::xrandr::modes_view::const_iterator
sge::opengl::xrandr::modes_view::end() const
{
	return
		this->begin()
		+
		resources_.get_ref().nmode;
}

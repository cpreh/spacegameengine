/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/color_surface.hpp>
#include <sge/renderer/const_scoped_color_surface_lock.hpp>


sge::renderer::const_scoped_color_surface_lock::const_scoped_color_surface_lock(
	renderer::color_surface const &_color_surface
)
:
	color_surface_(_color_surface),
	view_(
		color_surface_.lock()
	)
{
}

sge::renderer::const_scoped_color_surface_lock::const_scoped_color_surface_lock(
	renderer::color_surface const &_color_surface,
	renderer::lock_rect const &_rect
)
:
	color_surface_(_color_surface),
	view_(
		color_surface_.lock(
			_rect
		)
	)
{
}

sge::image2d::view::const_object const
sge::renderer::const_scoped_color_surface_lock::value() const
{
	return view_;
}

sge::renderer::const_scoped_color_surface_lock::~const_scoped_color_surface_lock()
{
	color_surface_.unlock();
}

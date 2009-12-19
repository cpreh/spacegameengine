/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../viewport_pos.hpp"
#include "../center_coordinate.hpp"
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <sge/exception.hpp>
#include <fcppt/text.hpp>

sge::renderer::pixel_pos const
sge::opengl::viewport_pos(
	sge::renderer::pixel_pos const &pos,
	sge::window::dim_type const &d,
	sge::renderer::screen_size const &screen_size,
	sge::renderer::viewport_mode::type const m)
{
	switch(m) {
	case renderer::viewport_mode::centered_screen_size:
		return pos + renderer::pixel_pos(
			center_coordinate(
				d.w(),
				screen_size.w()
			),
			center_coordinate(
				d.h(),
				screen_size.h()
			)
		);
	case renderer::viewport_mode::whole_window:
		return pos;
	default:
		throw exception(
			FCPPT_TEXT("Invalid viewport_mode!")
		);
	}
}

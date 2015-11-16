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


#include <sge/opengl/common.hpp>
#include <sge/opengl/target/area_function.hpp>
#include <sge/opengl/target/set_flipped_area.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/pixel_unit.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>


void
sge::opengl::target::set_flipped_area(
	sge::opengl::target::area_function _function,
	sge::renderer::pixel_rect const &_area,
	sge::renderer::screen_unit const _height
)
{
	_function(
		fcppt::cast::size<
			GLint
		>(
			_area.pos().x()
		),
		fcppt::cast::size<
			GLint
		>(
			fcppt::cast::to_signed(
				_height
			)
			-
			_area.size().h()
			-
			_area.pos().y()
		),
		fcppt::cast::size<
			GLsizei
		>(
			_area.size().w()
		),
		fcppt::cast::size<
			GLsizei
		>(
			_area.size().h()
		)
	);

	// checking is done in the calling function
}

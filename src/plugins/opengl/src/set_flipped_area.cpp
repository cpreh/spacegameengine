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


#include "../set_flipped_area.hpp"
#include "../common.hpp"
#include <sge/renderer/exception.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/pixel_unit.hpp>
#include <sge/renderer/viewport.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/text.hpp>

void
sge::opengl::set_flipped_area(
	opengl::area_function const _function,
	renderer::pixel_rect const &_area,
	renderer::screen_unit const _height
)
{
	_function(
		static_cast<
			GLint
		>(
			_area.pos().x()
		),
		static_cast<
			GLint
		>(
			static_cast<
				renderer::pixel_unit
			>(
				_height
			)
			- _area.size().h()
			- _area.pos().y()
		),
		static_cast<
			GLsizei
		>(
			_area.size().w()
		),
		static_cast<
			GLsizei
		>(
			_area.size().h()
		)
	);

	// checking is done in the calling function
}

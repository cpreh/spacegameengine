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


#include <sge/renderer/screen_unit.hpp>
#include <sge/renderer/display_mode/dpi.hpp>
#include <sge/renderer/display_mode/dpi_unit.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/to_dpi.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/arithmetic.hpp>


sge::renderer::display_mode::dpi const
sge::renderer::display_mode::to_dpi(
	sge::renderer::display_mode::optional_object const &_mode
)
{
	return
		_mode
		&&
		_mode->dimensions()
		?
			fcppt::math::dim::structure_cast<
				sge::renderer::display_mode::dpi
			>(
				_mode->pixel_size().get()
			)
			/
			fcppt::math::dim::structure_cast<
				sge::renderer::display_mode::dpi
			>(
				_mode->dimensions()->get()
			)
			*
			fcppt::literal<
				sge::renderer::display_mode::dpi_unit
			>(
				25.4
			)
		:
			sge::renderer::display_mode::dpi(
				fcppt::literal<
					sge::renderer::display_mode::dpi_unit
				>(
					96.f
				),
				fcppt::literal<
					sge::renderer::display_mode::dpi_unit
				>(
					96.f
				)
			)
		;
}

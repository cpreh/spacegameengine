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


#include <sge/renderer/screen_unit.hpp>
#include <sge/renderer/display_mode/dimensions.hpp>
#include <sge/renderer/display_mode/dpi.hpp>
#include <sge/renderer/display_mode/dpi_unit.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/to_dpi.hpp>
#include <fcppt/from_optional.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/optional_bind.hpp>
#include <fcppt/optional_bind_construct.hpp>
#include <fcppt/cast/int_to_float_fun.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/dim/structure_cast.hpp>


sge::renderer::display_mode::dpi const
sge::renderer::display_mode::to_dpi(
	sge::renderer::display_mode::optional_object const &_opt_mode
)
{
	return
		fcppt::from_optional(
			fcppt::optional_bind(
				_opt_mode,
				[](
					sge::renderer::display_mode::object const &_mode
				)
				{
					return
						fcppt::optional_bind_construct(
							_mode.dimensions(),
							[
								&_mode
							](
								sge::renderer::display_mode::dimensions const &_dim
							)
							{
								return
									_mode.pixel_size().get()
									/
									fcppt::math::dim::structure_cast<
										sge::renderer::display_mode::dpi,
										fcppt::cast::int_to_float_fun
									>(
										_dim.get()
									)
									*
									fcppt::literal<
										sge::renderer::display_mode::dpi_unit
									>(
										25.4
									);
							}
						);
				}
			),
			[]{
				return
					fcppt::math::dim::fill<
						sge::renderer::display_mode::dpi
					>(
						fcppt::literal<
							sge::renderer::display_mode::dpi_unit
						>(
							96.f
						)
					);
			}
		);
}

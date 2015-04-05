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


#include <sge/renderer/display_mode/desired_fps.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/refresh_rate_value.hpp>
#include <fcppt/const.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/optional_bind.hpp>


sge::renderer::display_mode::refresh_rate_value
sge::renderer::display_mode::desired_fps(
	sge::renderer::display_mode::optional_object const &_opt_display_mode
)
{
	return
		fcppt::maybe(
			fcppt::optional_bind(
				_opt_display_mode,
				[](
					sge::renderer::display_mode::object const &_display_mode
				)
				{
					return
						_display_mode.refresh_rate();
				}
			),
			fcppt::const_(
				fcppt::literal<
					sge::renderer::display_mode::refresh_rate_value
				>(
					60
				)
			),
			[](
				sge::renderer::display_mode::refresh_rate const _rate
			)
			{
				return
					_rate.get();
			}
		);
}

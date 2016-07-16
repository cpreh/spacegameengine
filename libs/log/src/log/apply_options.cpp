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


#include <sge/log/apply_options.hpp>
#include <sge/log/option.hpp>
#include <sge/log/option_container.hpp>
#include <fcppt/log/context.hpp>
#include <fcppt/log/enabled_levels.hpp>
#include <fcppt/log/location_setting.hpp>
#include <fcppt/log/setting.hpp>


void
sge::log::apply_options(
	fcppt::log::context &_context,
	sge::log::option_container const &_options
)
{
	for(
		sge::log::option const &option
		:
		_options
	)
		_context.set(
			fcppt::log::location_setting{
				option.location(),
				fcppt::log::setting{
					fcppt::log::enabled_levels(
						option.level()
					)
				}
			}
		);
}

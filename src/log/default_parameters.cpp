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


#include <sge/log/default_parameters.hpp>
#include <sge/log/stream.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/location_fwd.hpp>
#include <fcppt/log/parameters.hpp>


fcppt::log::parameters
sge::log::default_parameters(
	fcppt::log::context &_context,
	fcppt::log::location const &_location
)
{
	return
		fcppt::log::parameters(
			sge::log::stream(),
			fcppt::log::level::info
		)
		.context_location(
			_context,
			_location
		)
		.enabled(
			true
		);
}

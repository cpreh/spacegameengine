/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/src/systems/make_any_key.hpp>
#include <sge/systems/detail/any_fwd.hpp>
#include <sge/systems/detail/any_map.hpp>
#include <sge/systems/detail/list.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::systems::detail::list::list()
:
	states_()
{
}

void
sge::systems::detail::list::insert(
	sge::systems::detail::any const &_any
)
{
	FCPPT_ASSERT_ERROR(
		states_.insert(
			std::make_pair(
				sge::systems::make_any_key(
					_any
				),
				_any
			)
		).second == 1u
	);
}

sge::systems::detail::any_map const &
sge::systems::detail::list::get() const
{
	return states_;
}

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


#include <sge/systems/detail/any.hpp>
#include <sge/systems/detail/any_list.hpp>
#include <sge/systems/detail/any_map.hpp>
#include <sge/systems/detail/list.hpp>
#include <sge/systems/impl/make_any_key.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::systems::detail::list::list(
	sge::systems::detail::any_list const &_elements
)
:
	states_(
		fcppt::algorithm::map<
			sge::systems::detail::any_map
		>(
			_elements,
			[](
				sge::systems::detail::any const &_any
			)
			{
				return
					std::make_pair(
						sge::systems::impl::make_any_key(
							_any
						),
						_any
					);
			}
		)
	)
{
	FCPPT_ASSERT_ERROR(
		_elements.size()
		==
		states_.size()
	);
}

sge::systems::detail::any_map const &
sge::systems::detail::list::get() const
{
	return
		states_;
}

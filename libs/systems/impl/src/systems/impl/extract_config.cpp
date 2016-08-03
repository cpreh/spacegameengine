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


#include <sge/systems/config.hpp>
#include <sge/systems/detail/any.hpp>
#include <sge/systems/detail/any_key.hpp>
#include <sge/systems/detail/any_map.hpp>
#include <sge/systems/impl/extract_config.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/variant/get_exn.hpp>


sge::systems::config
sge::systems::impl::extract_config(
	sge::systems::detail::any_map const &_map
)
{
	return
		fcppt::optional::maybe(
			fcppt::container::find_opt_mapped(
				_map,
				sge::systems::detail::any_key::config
			),
			[]{
				return
					sge::systems::config();
			},
			[](
				fcppt::reference<
					sge::systems::detail::any const
				> const _config
			)
			{
				return
					fcppt::variant::get_exn<
						sge::systems::config
					>(
						_config.get()
					);
			}

		);
}

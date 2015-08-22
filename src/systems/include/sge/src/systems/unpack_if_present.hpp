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


#ifndef SGE_SRC_SYSTEMS_UNPACK_IF_PRESENT_HPP_INCLUDED
#define SGE_SRC_SYSTEMS_UNPACK_IF_PRESENT_HPP_INCLUDED

#include <sge/systems/detail/any.hpp>
#include <sge/systems/detail/any_key.hpp>
#include <sge/systems/detail/any_map.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/variant/get_exn.hpp>


namespace sge
{
namespace systems
{

template<
	typename Parameter,
	typename Function
>
void
unpack_if_present(
	sge::systems::detail::any_map const &_map,
	sge::systems::detail::any_key const _key,
	Function const _function
)
{
	fcppt::maybe_void(
		fcppt::container::find_opt_mapped(
			_map,
			_key
		),
		[
			_function
		](
			sge::systems::detail::any const &_element
		)
		{
			_function(
				fcppt::variant::get_exn<
					Parameter
				>(
					_element
				)
			);
		}
	);
}

}
}

#endif

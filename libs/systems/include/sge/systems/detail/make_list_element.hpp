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


#ifndef SGE_SYSTEMS_DETAIL_MAKE_LIST_ELEMENT_HPP_INCLUDED
#define SGE_SYSTEMS_DETAIL_MAKE_LIST_ELEMENT_HPP_INCLUDED

#include <sge/systems/config_fwd.hpp>
#include <sge/systems/detail/any.hpp>
#include <sge/systems/detail/extract_parameter_type.hpp>
#include <sge/systems/detail/make_list_element_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/algorithms/find.hpp>
#include <brigand/functions/lambda/apply.hpp>
#include <brigand/functions/lambda/bind.hpp>
#include <brigand/types/args.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace systems
{
namespace detail
{

template<
	typename Choices,
	typename Type
>
inline
sge::systems::detail::any
make_list_element(
	Type const &_type
)
{
	// Check that the given parameter is actually part of the
	// static subsystems
	static_assert(
		std::is_same<
			Type,
			sge::systems::config
		>::value
		||
		brigand::found<
			Choices,
			brigand::bind<
				std::is_same,
				brigand::pin<
					Type
				>,
				brigand::bind<
					sge::systems::detail::extract_parameter_type,
					brigand::_1
				>
			>
		>::value,
		"Parameter given to sge::systems::list is not part of the system choices"
	);

	return
		sge::systems::detail::make_list_element_impl<
			Choices
		>(
			_type
		);
}

}
}
}

#endif

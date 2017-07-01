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


#ifndef SGE_RUCKSACK_ACCESS_AXIS_HPP_INCLUDED
#define SGE_RUCKSACK_ACCESS_AXIS_HPP_INCLUDED

#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/axis_to_index.hpp>
#include <fcppt/enum/size.hpp>


namespace sge
{
namespace rucksack
{

template<
	typename Value
>
typename
Value::value_type
access_axis(
	Value const &_value,
	sge::rucksack::axis const _axis
)
{
	static_assert(
		Value::static_size::value
		==
		fcppt::enum_::size<
			sge::rucksack::axis
		>::value,
		""
	);

	return
		_value.get_unsafe(
			sge::rucksack::axis_to_index(
				_axis
			)
		);
}

}
}

#endif

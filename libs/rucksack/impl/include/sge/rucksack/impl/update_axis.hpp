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


#ifndef SGE_RUCKSACK_IMPL_UPDATE_AXIS_HPP_INCLUDED
#define SGE_RUCKSACK_IMPL_UPDATE_AXIS_HPP_INCLUDED

#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/axis_to_index.hpp>
#include <sge/rucksack/scalar.hpp>
#include <fcppt/enum/size.hpp>


namespace sge
{
namespace rucksack
{
namespace impl
{

template<
	typename Ret
>
[[nodiscard]]
Ret
update_axis(
	Ret _result,
	sge::rucksack::axis const _axis,
	sge::rucksack::scalar const _scalar
)
{
	static_assert(
		Ret::static_size::value
		==
		fcppt::enum_::size<
			sge::rucksack::axis
		>::value,
		""
	);

	_result.get_unsafe(
		sge::rucksack::axis_to_index(
			_axis
		)
	) =
		_scalar;

	return
		_result;
}

}
}
}

#endif

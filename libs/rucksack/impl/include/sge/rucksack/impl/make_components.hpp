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


#ifndef SGE_RUCKSACK_IMPL_MAKE_COMPONENTS_HPP_INCLUDED
#define SGE_RUCKSACK_IMPL_MAKE_COMPONENTS_HPP_INCLUDED

#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/axis_to_index.hpp>
#include <sge/rucksack/scalar.hpp>
#include <fcppt/no_init.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace rucksack
{
namespace impl
{

template<
	typename Ret
>
Ret
make_components(
	std::pair<
		sge::rucksack::axis,
		sge::rucksack::scalar
	> const _pair1,
	std::pair<
		sge::rucksack::axis,
		sge::rucksack::scalar
	> const _pair2
)
{
	Ret ret{
		fcppt::no_init()
	};

	auto const assign(
		[
			&ret
		](
			std::pair<
				sge::rucksack::axis,
				sge::rucksack::scalar
			> const _pair
		)
		{
			ret[
				sge::rucksack::axis_to_index(
					_pair.first
				)
			] =
				_pair.second;
		}
	);

	assign(
		_pair1
	);

	assign(
		_pair2
	);

	return
		ret;
}

}
}
}

#endif

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


#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/minimum_size.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/impl/extract_size.hpp>
#include <fcppt/variant/match.hpp>


sge::rucksack::scalar
sge::rucksack::impl::extract_size(
	sge::rucksack::axis_policy const &_policy
)
{
	return
		fcppt::variant::match(
			_policy,
			[](
				sge::rucksack::minimum_size const _pol
			)
			{
				return
					_pol.get();
			},
			[](
				sge::rucksack::preferred_size const _pol
			)
			{
				return
					_pol.get();
			}
		);
}

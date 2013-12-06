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


#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/is_expanding.hpp>
#include <sge/rucksack/minimum_size.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/optional_scalar.hpp>
#include <sge/rucksack/scalar.hpp>


sge::rucksack::axis_policy::axis_policy(
	sge::rucksack::minimum_size const &_minimum_size,
	sge::rucksack::preferred_size const &_preferred_size,
	sge::rucksack::is_expanding const &_is_expanding
)
:
	minimum_size_(
		_minimum_size.get()
	),
	preferred_size_(
		_preferred_size.get()
	),
	is_expanding_(
		_is_expanding.get()
	)
{
}

sge::rucksack::scalar
sge::rucksack::axis_policy::minimum_size() const
{
	return minimum_size_;
}

sge::rucksack::optional_scalar
sge::rucksack::axis_policy::preferred_size() const
{
	return preferred_size_;
}

bool
sge::rucksack::axis_policy::is_expanding() const
{
	return is_expanding_;
}

/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/window/size_hints.hpp>

sge::window::size_hints::size_hints()
:
	exact_size_hint_(),
	minimum_size_hint_(),
	maximum_size_hint_()
{
}

sge::window::size_hints &
sge::window::size_hints::exact_size_hint(
	window::dim const &_exact_size_hint
)
{
	exact_size_hint_ = _exact_size_hint;

	return *this;
}

sge::window::size_hints &
sge::window::size_hints::minimum_size_hint(
	window::dim const &_minimum_size_hint
)
{
	minimum_size_hint_ = _minimum_size_hint;

	return *this;
}

sge::window::size_hints &
sge::window::size_hints::maximum_size_hint(
	window::dim const &_maximum_size_hint
)
{
	maximum_size_hint_ = _maximum_size_hint;

	return *this;
}

sge::window::optional_dim const &
sge::window::size_hints::exact_size_hint() const
{
	return exact_size_hint_;
}

sge::window::optional_dim const &
sge::window::size_hints::minimum_size_hint() const
{
	return minimum_size_hint_;
}

sge::window::optional_dim const &
sge::window::size_hints::maximum_size_hint() const
{
	return maximum_size_hint_;
}

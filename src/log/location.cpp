/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/log/location.hpp>

sge::log::location::location(
	string const &initial_
)
:
	entries_(
		1,
		initial_
	)
{}

sge::log::location &
sge::log::location::operator +=(
	string const &nstring_
)
{
	entries_.push_back(
		nstring_
	);

	return *this;
}

sge::log::location::const_iterator
sge::log::location::begin() const
{
	return entries_.begin();
}
	
sge::log::location::const_iterator
sge::log::location::end() const
{
	return entries_.end();
}

sge::log::location const
sge::log::operator +(
	location location_,
	string const &nstring_
)
{
	return location_ += nstring_;
}

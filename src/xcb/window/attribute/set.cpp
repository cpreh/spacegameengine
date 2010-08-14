/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/xcb/window/attribute/set.hpp>

sge::xcb::window::attribute::set::set()
:
	map_()
{}

sge::xcb::window::attribute::set::set(
	attribute::value_map const &_map
)
:
	map_(_map)
{}

sge::xcb::window::attribute::set::~set()
{}

bool
sge::xcb::window::attribute::set::add(
	enum_::type const what_,
	value const value_
)
{
	return
		map_.insert(
			std::make_pair(
				what_,
				value_
			)
		).second;
}

bool
sge::xcb::window::attribute::set::remove(
	enum_::type const what_
)
{
	return
		map_.erase(
			what_
		) > 0;
}

sge::xcb::window::attribute::value_map &
sge::xcb::window::attribute::set::value_map()
{
	return map_;
}

sge::xcb::window::attribute::value_map const &
sge::xcb::window::attribute::set::value_map() const
{
	return map_;
}

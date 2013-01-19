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


#include <sge/parse/json/array.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/start.hpp>
#include <sge/parse/json/start_variant.hpp>


sge::parse::json::start::start()
:
	// Just put something here because spirit needs default initialized
	// objects
	variant(
		sge::parse::json::array()
	)
{
}

sge::parse::json::start::start(
	sge::parse::json::start_variant const &_variant
)
:
	variant(
		_variant
	)
{
}

sge::parse::json::array &
sge::parse::json::start::array()
{
	return
		variant.get<
			sge::parse::json::array
		>();
}

sge::parse::json::array const &
sge::parse::json::start::array() const
{
	return
		variant.get<
			sge::parse::json::array
		>();
}

sge::parse::json::object &
sge::parse::json::start::object()
{
	return
		variant.get<
			sge::parse::json::object
		>();
}

sge::parse::json::object const &
sge::parse::json::start::object() const
{
	return
		variant.get<
			sge::parse::json::object
		>();
}

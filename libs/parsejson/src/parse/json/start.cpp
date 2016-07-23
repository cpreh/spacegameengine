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


#include <sge/parse/json/array.hpp>
#include <sge/parse/json/array_or_object.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/start.hpp>
#include <fcppt/variant/get_exn.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


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
	sge::parse::json::array_or_object const &_variant
)
:
	variant(
		_variant
	)
{
}

sge::parse::json::start::start(
	sge::parse::json::array_or_object &&_variant
)
:
	variant(
		std::move(
			_variant
		)
	)
{
}

sge::parse::json::array &
sge::parse::json::start::array()
{
	return
		fcppt::variant::get_exn<
			sge::parse::json::array
		>(
			variant
		);
}

sge::parse::json::array const &
sge::parse::json::start::array() const
{
	return
		fcppt::variant::get_exn<
			sge::parse::json::array
		>(
			variant
		);
}

sge::parse::json::object &
sge::parse::json::start::object()
{
	return
		fcppt::variant::get_exn<
			sge::parse::json::object
		>(
			variant
		);
}

sge::parse::json::object const &
sge::parse::json::start::object() const
{
	return
		fcppt::variant::get_exn<
			sge::parse::json::object
		>(
			variant
		);
}

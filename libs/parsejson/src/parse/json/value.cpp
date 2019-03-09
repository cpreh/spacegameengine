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


#include <sge/parse/json/value.hpp>
#include <sge/parse/json/value_variant.hpp>
#include <fcppt/variant/comparison.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::parse::json::value::value(
	sge::parse::json::value_variant &&_impl
)
:
	impl{
		std::move(
			_impl
		)
	}
{
}

sge::parse::json::value_variant const &
sge::parse::json::value::get() const
{
	return
		impl;
}

sge::parse::json::value_variant &
sge::parse::json::value::get()
{
	return
		impl;
}

bool
sge::parse::json::operator==(
	sge::parse::json::value const &_left,
	sge::parse::json::value const &_right
)
{
	return
		_left.get()
		==
		_right.get();
}

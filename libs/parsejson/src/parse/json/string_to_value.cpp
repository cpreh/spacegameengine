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


#include <sge/parse/exception.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/find_member_value_exn.hpp>
#include <sge/parse/json/parse_string.hpp>
#include <sge/parse/json/string_to_value.hpp>
#include <sge/parse/json/value.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/either/to_exception.hpp>
#include <fcppt/parse/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::parse::json::value
sge::parse::json::string_to_value(
	std::string &&_string
)
{
	return
		sge::parse::json::find_member_value_exn(
			fcppt::either::to_exception(
				sge::parse::json::parse_string(
					"{ \"value\" : "
					+
					std::move(
						_string
					)
					+
					" }"
				),
				[](
					fcppt::parse::error<
						char
					> &&_error
				)
				{
					return
						sge::parse::exception{
							fcppt::from_std_string(
								std::move(
									_error.get()
								)
							)
						};
				}
			).object().members,
			"value"
		);
}

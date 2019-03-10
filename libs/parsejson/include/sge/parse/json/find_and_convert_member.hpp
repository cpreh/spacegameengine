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


#ifndef SGE_PARSE_JSON_FIND_AND_CONVERT_MEMBER_HPP_INCLUDED
#define SGE_PARSE_JSON_FIND_AND_CONVERT_MEMBER_HPP_INCLUDED

#include <sge/charconv/utf8_string.hpp>
#include <sge/parse/exception.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/convert_from.hpp>
#include <sge/parse/json/find_object_exn.hpp>
#include <sge/parse/json/invalid_get.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/path.hpp>
#include <sge/parse/json/path_to_string.hpp>
#include <sge/parse/json/value.hpp>
#include <sge/parse/json/detail/to_fcppt_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iterator>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace parse
{
namespace json
{

template<
	typename T
>
std::conditional_t<
	// TODO: This check is broken
	std::is_same<
		std::remove_const_t<
			T
		>,
		sge::parse::json::value
	>::value
	||
	std::is_same<
		std::remove_const_t<
			T
		>,
		sge::parse::json::object
	>::value
	||
	std::is_same<
		std::remove_const<
			T
		>,
		sge::parse::json::array
	>::value,
	T const &,
	T
>
find_and_convert_member(
	sge::parse::json::object const &_object,
	sge::parse::json::path const &_input_path
)
{
	// TODO: path split
	FCPPT_ASSERT_PRE(
		!_input_path.get().empty()
	);

	sge::parse::json::path const shortened_path{
		sge::parse::json::path::sequence_type{
			_input_path.get().begin(),
			std::prev(
				_input_path.get().end()
			)
		}
	};

	sge::parse::json::object const &found_object{
		sge::parse::json::find_object_exn(
			_object,
			shortened_path
		)
	};

	sge::charconv::utf8_string const &path_back(
		_input_path.get().back()
	);

	try
	{
		return
			sge::parse::json::convert_from<
				T
			>(
				fcppt::optional::to_exception(
					fcppt::container::find_opt_mapped(
						found_object.members,
						path_back
					),
					[
						&shortened_path,
						&path_back
					]{
						return
							sge::parse::exception(
								FCPPT_TEXT("Couldn't find member \"")
								+
								sge::parse::json::detail::to_fcppt_string(
									path_back
								)
								+
								FCPPT_TEXT("\" in the object \"")
								+
								sge::parse::json::detail::to_fcppt_string(
									sge::parse::json::path_to_string(
										shortened_path
									)
								)
								+
								FCPPT_TEXT("\"")
							);
					}
				).get().get()
			);
	}
	catch(
		sge::parse::json::invalid_get const &_error
	)
	{
		throw
			sge::parse::exception(
				FCPPT_TEXT("Unable to parse member \"")
				+
				sge::parse::json::detail::to_fcppt_string(
					path_back
				)
				+
				FCPPT_TEXT("\" of object \"")
				+
				sge::parse::json::detail::to_fcppt_string(
					sge::parse::json::path_to_string(
						shortened_path
					)
				)
				+
				FCPPT_TEXT("\": ")
				+
				_error.string()
			);
	}
}

}
}
}

#endif

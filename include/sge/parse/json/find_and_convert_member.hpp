/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include <sge/parse/json/path.hpp>
#include <sge/parse/json/convert_from.hpp>
#include <sge/parse/json/is_null.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/path_to_string.hpp>
#include <sge/parse/json/find_object_exn.hpp>
#include <sge/parse/json/exception.hpp>
#include <sge/parse/json/member_name_equal.hpp>
#include <sge/parse/json/invalid_get.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert.hpp>
#include <boost/range/algorithm/find_if.hpp>

namespace sge
{
namespace parse
{
namespace json
{
template<typename T>
T const
find_and_convert_member(
	sge::parse::json::object const &o,
	json::path const &input_path)
{
	FCPPT_ASSERT(
		!input_path.empty());

	json::path const shortened_path =
		json::path(
			input_path.begin(),
			--input_path.end());

	sge::parse::json::object const &found_object =
		json::find_object_exn(
			o,
			shortened_path);

	sge::parse::json::member_vector::const_iterator it =
		boost::find_if(
			found_object.members,
			sge::parse::json::member_name_equal(
				input_path.back()));

	if (it == found_object.members.end())
		throw
			sge::parse::json::exception(
				FCPPT_TEXT("Couldn't find member \"")+
				input_path.back()+
				FCPPT_TEXT("\" in the object \"")+
				json::path_to_string(
					shortened_path)+
				FCPPT_TEXT("\""));

	if(
		json::is_null(
			it->value))
		throw
			sge::parse::json::exception(
				FCPPT_TEXT("The member \"")+
				it->name+
				FCPPT_TEXT("\" of object \"")+
				json::path_to_string(
					shortened_path)+
				FCPPT_TEXT("\" is null. Don't know what to return here..."));

	try
	{
		return
			json::convert_from<T>(
				it->value);
	}
	catch (sge::parse::json::invalid_get const &e)
	{
		throw
			sge::parse::json::exception(
				FCPPT_TEXT("Unable to parse member \"")+
				it->name+
				FCPPT_TEXT(" of object \"")+
				json::path_to_string(
					shortened_path)+
				FCPPT_TEXT("\": ")+
				e.string());
	}
}
}
}
}

#endif

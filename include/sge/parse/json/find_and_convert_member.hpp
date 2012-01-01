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


#ifndef SGE_PARSE_JSON_FIND_AND_CONVERT_MEMBER_HPP_INCLUDED
#define SGE_PARSE_JSON_FIND_AND_CONVERT_MEMBER_HPP_INCLUDED

#include <sge/parse/json/convert_from.hpp>
#include <sge/parse/json/exception.hpp>
#include <sge/parse/json/find_object_exn.hpp>
#include <sge/parse/json/invalid_get.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/path.hpp>
#include <sge/parse/json/path_to_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/next_prior.hpp>
#include <boost/range/algorithm/find_if.hpp>
#include <fcppt/config/external_end.hpp>


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
	FCPPT_ASSERT_PRE(
		!input_path.empty());

	json::path const shortened_path =
		json::path(
			input_path.begin(),
			boost::prior(
				input_path.end()));

	sge::parse::json::object const &found_object =
		json::find_object_exn(
			o,
			shortened_path);

	sge::parse::json::member_map::const_iterator it(
		found_object.members.find(
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

	try
	{
		return
			json::convert_from<T>(
				it->second);
	}
	catch (sge::parse::json::invalid_get const &e)
	{
		throw
			sge::parse::json::exception(
				FCPPT_TEXT("Unable to parse member \"")+
				it->first+
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

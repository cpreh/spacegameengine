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


#include <sge/parse/json/make_recursive_objects.hpp>
#include <sge/parse/json/path_to_string.hpp>
#include <sge/parse/json/path.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/member_vector.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/member_name_equal.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/type_name.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <numeric>
#include <fcppt/config/external_end.hpp>

namespace
{
sge::parse::json::object *
create_or_navigate_path(
	sge::parse::json::path const &input_path,
	sge::parse::json::object * const old,
	fcppt::string const &new_member)
{
	FCPPT_ASSERT_PRE(
		old);

	sge::parse::json::member_vector::iterator it =
		std::find_if(
			old->members.begin(),
			old->members.end(),
			sge::parse::json::member_name_equal(
				new_member));

	if(it == old->members.end())
	{
		old->members.push_back(
			sge::parse::json::member(
				new_member,
				sge::parse::json::object()));

		return &sge::parse::json::get<sge::parse::json::object>(old->members.back().value);
	}

	if(it->value.type() != typeid(sge::parse::json::object))
		throw
			sge::parse::json::exception(
				FCPPT_TEXT("Couldn't navigate to (make_recursive) \"")+
				sge::parse::json::path_to_string(
					input_path)+
				FCPPT_TEXT("\", stopped at \"")+
				new_member+
				FCPPT_TEXT("\" because this member has type \"")+
				fcppt::type_name(
					it->value.type())+
				FCPPT_TEXT("\" instead of type sge::parse::json::object!"));

	return
		&sge::parse::json::get<sge::parse::json::object>(
			it->value);
}
}

sge::parse::json::object &
sge::parse::json::make_recursive_objects(
	sge::parse::json::object &input_object,
	json::path const &input_path)
{
	return
		*std::accumulate(
			input_path.begin(),
			input_path.end(),
			&input_object,
			std::tr1::bind(
				&create_or_navigate_path,
				input_path,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2));
}

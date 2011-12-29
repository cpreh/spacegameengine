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


#include <sge/parse/json/array.hpp>
#include <sge/parse/json/exception.hpp>
#include <sge/parse/json/find_member_value.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/make_recursive_objects.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/path.hpp>
#include <sge/parse/json/path_to_string.hpp>
#include <sge/parse/json/value.hpp>
#include <fcppt/optional.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_name.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/variant/holds_type.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <numeric>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

sge::parse::json::object *
create_or_navigate_path(
	sge::parse::json::path const &_input_path,
	sge::parse::json::object *const _old,
	fcppt::string const &_new_member)
{
	typedef fcppt::optional<
		sge::parse::json::value &
	> optional_value;

	optional_value const ref(
		sge::parse::json::find_member_value(
			_old->members,
			_new_member));

	if(!ref)
	{
		typedef std::pair<
			sge::parse::json::member_map::iterator,
			bool
		> insert_pair;

		insert_pair const insert_ret(
			_old->members.insert(
				sge::parse::json::member(
					_new_member,
					sge::parse::json::object())));

		FCPPT_ASSERT_ERROR(
			insert_ret.second
		);

		return
			&sge::parse::json::get<
				sge::parse::json::object
			>(
				insert_ret.first->second
			);
	}

	if(
		!fcppt::variant::holds_type<
			sge::parse::json::object
		>(
			*ref
		)
	)
		throw
			sge::parse::json::exception(
				FCPPT_TEXT("Couldn't navigate to (make_recursive) \"")+
				sge::parse::json::path_to_string(
					_input_path)+
				FCPPT_TEXT("\", stopped at \"")+
				_new_member+
				FCPPT_TEXT("\" because this member has type \"")+
				fcppt::type_name(
					ref->type())+
				FCPPT_TEXT("\" instead of type sge::parse::json::object!"));

	return
		&sge::parse::json::get<sge::parse::json::object>(
			*ref);
}
}

sge::parse::json::object &
sge::parse::json::make_recursive_objects(
	sge::parse::json::object &_input_object,
	json::path const &_input_path)
{
	return
		*std::accumulate(
			_input_path.begin(),
			_input_path.end(),
			&_input_object,
			std::tr1::bind(
				&create_or_navigate_path,
				_input_path,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2));
}

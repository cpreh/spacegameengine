/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/parse/json/find_member_value.hpp>
#include <sge/parse/json/get_exn.hpp>
#include <sge/parse/json/get_exn_message.hpp>
#include <sge/parse/json/make_recursive_objects.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/path.hpp>
#include <sge/parse/json/path_to_string.hpp>
#include <sge/parse/json/value.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_wrapper_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/variant/type_info.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <numeric>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef
fcppt::reference_wrapper<
	sge::parse::json::object
>
object_reference;

object_reference const
create_or_navigate_path(
	sge::parse::json::path const &_input_path,
	object_reference const _old,
	fcppt::string const &_new_member
)
{
	return
		fcppt::maybe(
			sge::parse::json::find_member_value(
				_old.get().members,
				_new_member
			),
			[
				&_old,
				&_new_member
			]{
				typedef std::pair<
					sge::parse::json::member_map::iterator,
					bool
				> insert_pair;

				insert_pair const insert_ret(
					_old.get().members.insert(
						sge::parse::json::member(
							_new_member,
							sge::parse::json::value(
								sge::parse::json::object()
							)
						)
					)
				);

				FCPPT_ASSERT_ERROR(
					insert_ret.second
				);

				return
					fcppt::make_ref(
						sge::parse::json::get_exn<
							sge::parse::json::object
						>(
							insert_ret.first->second
						)
					);
			},
			[
				&_input_path,
				&_new_member
			](
				sge::parse::json::value &_value
			)
			{
				return
					fcppt::make_ref(
						sge::parse::json::get_exn_message<
							sge::parse::json::object
						>(
							_value,
							[
								&_input_path,
								&_new_member
							]{
								return
									FCPPT_TEXT("Couldn't navigate to (make_recursive) \"")
									+
									sge::parse::json::path_to_string(
										_input_path
									)
									+
									FCPPT_TEXT("\", stopped at \"")
									+
									_new_member;
							}
						)
					);
			}
		);
}
}

sge::parse::json::object &
sge::parse::json::make_recursive_objects(
	sge::parse::json::object &_input_object,
	sge::parse::json::path const &_input_path
)
{
	return
		std::accumulate(
			_input_path.begin(),
			_input_path.end(),
			fcppt::make_ref(
				_input_object
			),
			std::bind(
				&create_or_navigate_path,
				_input_path,
				std::placeholders::_1,
				std::placeholders::_2
			)
		).get();
}
